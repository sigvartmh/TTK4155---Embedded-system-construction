#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "uart.h"
#include "can.h"
#include "pwm.h"
#include "adc.h"
#include "control_driver.h"
#include "shooter.h"

int main(void) {
	/*-----Define pins-----*/
	DDRB |= (1 << PINB5);		//Set B5(OC1A) as output
	DDRF &= ~(1 << PINF0);		//Set F0(ADC0) as input
	
	/*-----Define variables-----*/
	CAN_message_t can_msg_send;
	CAN_message_t can_msg_receive;
	
	unsigned int servo_angle = 1500;
	unsigned int adc_value = 0;
	
	uint8_t adc_sample = 0;
	uint8_t ball_counter = 3; 
	uint8_t sliderpos = 0;
	
	int16_t encoder_maxvalue;
	int16_t enc_value;
	int precent;
	
	//Variables for Uart reading
	char str[4];
	char rxData=0;
	int j = 0;
	int rxInt = 0;
	
	
	//Flags for input and score timer
	int uart_flag = 1; //set uart_flag to 0 
	int joystick_flag = 0;
	int timer = 0;
	/*-----End variable define----*/
		
	/*-----Initialize UART-----*/
	UART_init(MYUBRR);
	printf("----UART working----\n\r");

	/*-----Initialize CAN-----*/
	if (CAN_init() == 0) {
		printf("----CAN working----\n\r");
		can_msg_send.id = 2;
		can_msg_send.length = 2;
	} else {
		printf("----CAN error!!----\n\r");
	}
	
	/*-----Initialize PWM-----*/
	if (PWM_init() == 0) {
		printf("----PWM working----\n\r");
	} else {
		printf("----PWM error!!----\n\r");
	}
	
	/*-----Initialize ADC-----*/
	if (ADC_init() == 0) {
		printf("----ADC working----\n\r");
	} else {
		printf("----ADC error!!----\n\r");
	}
	
	//Initiate shooter
	shooter_init();
	
	//Enable global interrupts
	control_init();
	sei();
	
	//Initiate motor control
	control_encoder_calibrate();
	encoder_maxvalue =  get_maxvalue();
	
	//Enable interupt timer for regulator
	inti_clock();
	
	control_set_reference(50);
	
	while(1) {

		//Receive data from node 1
		timer = 0;
		can_msg_receive = CAN_data_receive();
		if (can_msg_receive.id == 1 && can_msg_receive.length == 6) {
			
			//Check if game is on
			if (can_msg_receive.data[3] == 1) {
				uart_flag = !can_msg_receive.data[4];
				joystick_flag = can_msg_receive.data[5];
				
				if (joystick_flag) {
					control_set_joystick_flag(joystick_flag);
				} else {
					control_set_joystick_flag(joystick_flag);
				}
				
				//Turn on the ADC
				ADC_start();
				control_set_timer_flag(1);
				
				if (uart_flag) {
					//Calculate servo position
					servo_angle = (can_msg_receive.data[0] * (-6.2) + 1551);
					PWM_set_pulse(servo_angle);
					
					if (joystick_flag) {
						control_speed_reg(can_msg_receive.data[0]);
					} else {
						//Calculate slider position
						sliderpos = can_msg_receive.data[1];
					
						//Set a reference value
						control_set_reference(sliderpos);
					}
					
					//Check for button click
					//printf("Can message button: %i\n\r", can_msg_receive.data[2]);
					if (can_msg_receive.data[2]==1) {
						shooter_shoot();
					}
					enc_value = read_encoder();
					precent = enc_value / (encoder_maxvalue/100);
					printf("Encoder: %i\n", precent); //neded for webinterface
						
				} else {
					rxData = UART_recchar();
					if (rxData =='p') {
						while(rxData != 'q'){
							rxData = UART_recchar();
							str[j] = rxData;
							j++;
						}
						str[j] = '\0';
						rxInt = atoi(str);
						control_set_reference(rxInt);
						printf("Reference: %i\n\r",rxInt);
						rxData = 0;
						j=0;
					} else if(rxData == 's'){
						shooter_shoot();
						rxData=0;
					}
				}
				
				timer = get_timer_value();
				can_msg_send.data[1] = timer;
				printf("Score: %i\n", timer);
				
				//Read IR
				adc_value += ADCH;
				adc_sample++;
				
				//Filter the signal
				if (adc_sample == 5) {
					adc_value = adc_value / adc_sample;
					
					//Check for the ball
					if (adc_value < 100) {
						ball_counter--;
						control_set_timer_flag(0);
						
						//Send the score to node 1
						can_msg_send.data[0] = ball_counter;
						CAN_message_send(&can_msg_send);
						
						//Wait until the ball is removed
						while (adc_value < 100) {
							adc_value = ADCH;
							_delay_ms(100);
						}
					}
					
					adc_value = 0;
					adc_sample = 0;
				}
			} else {
				//Reset the game
				ADC_stop();
				control_set_timer_flag(0);
				control_reset_integral();
				control_reset_timer();
				timer = 0;
				ball_counter = 3;

			}
		}
    }
}