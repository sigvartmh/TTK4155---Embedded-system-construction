#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "can.h"
#include "pwm.h"
#include "adc.h"

#include "control_driver.h"
#include "shooter.h"

int main(void) {
	/*-----Define pins-----*/
	//DDRD &= ~(1 << PIND0);	//Set D0(INT0) as input
	DDRB |= (1 << PINB5);		//Set B5(OC1A) as output
	DDRF &= ~(1 << PINF0);		//Set F0(ADC0) as input
	
	/*-----Define variables-----*/
	CAN_message_t can_msg_send;
	CAN_message_t can_msg_receive;
	unsigned int servo_angle = 1500;
	unsigned int adc_value = 0;
	uint8_t adc_sample = 0;
	uint8_t ball_counter = 0; 
		
	/*-----Interrupts-----*/
	//EIMSK |= (1 << INT0);		//Enable INT0
	//EICRA |= (1 << ISC01);	//Trigger on falling edge
	//EICRA &= ~(1 << ISC00);	//Trigger on falling edge
	
	/*-----Initialize UART-----*/
	UART_init(MYUBRR);
	printf("----UART working----\n\r");

	/*-----Initialize CAN-----*/
	if (CAN_init() == 0) {
		printf("----CAN working----\n\r");
		can_msg_send.id = 2;
		can_msg_send.length = 1;
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
	
	/*-----Initialize Motor controll-----*/
	control_init();
	printf("----Motor control working----\n\r");
	/*-----Initialize Solinoid----*/
	shooter_init();
	printf("----Shooter working----\n\r");
	
	//Do this when game starts
	ADC_start();
	
	//Enable global interrupts
	//sei();
		
	while(1) {

		_delay_ms(50);
		
		//Receive data from node 1
		can_msg_receive = CAN_data_receive();
		if (can_msg_receive.id == 1) {
			
			//Calculate servo position
			servo_angle = (can_msg_receive.data[0] * (-6.2) + 1551);
			//test --> printf("Angle: %i\n\n\r", servo_angle);
			PWM_set_pulse(servo_angle);
			printf("Data 1: %i",can_msg_receive.data[0]);
			
			//Calculate slider position
			
			printf("Data 2: %c",can_msg_receive.data[1]);
			
			//control_set_pos()
					
			//Check for button click
			printf("Data 3: %c\n\r",can_msg_receive.data[2]);
			
			if(can_msg_receive.data[2]){
				shooter_shoot();
			}
			
		}
		
		//Read IR
		adc_value += ADCH;
		adc_sample++;
		
		//Filter the signal
		if (adc_sample == 5) {
			adc_value = adc_value / adc_sample;
			//printf("ADC: %i", adc_value);
			
			//Check for the ball
			if (adc_value < 100) {
				ball_counter++;
				
				//Send the score to node 1
				//printf("Score: %i", ball_counter);
				can_msg_send.data[0] = ball_counter;
				CAN_message_send(&can_msg_send);
				
				//Wait until the ball is removed
				//while (adc_value < 100) {
					//adc_value = ADCH;
					//_delay_ms(800);
				//}
			}
						
			adc_value = 0;
			adc_sample = 0;
		}
    }
}