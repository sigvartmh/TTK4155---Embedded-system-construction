#include "setup.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "DAC_driver.h"
#include "control_driver.h"
#include "uart.h"

//MJ1 Connected to PORTA
//Motor
#define MJ1_PORT PORTA
#define MJ1_DDR  DDRA

//MJ2 Connected to PORTC
//Encoder
#define MJ2_PORT PORTC
#define MJ2_DDR  DDRC
#define MJ2_DATA PINC

#define ENCODER_OUTPUT_ENABLE PA7
#define ENCODER_RESET PA6
#define ENCODER_SELECT_BYTE PA5
 
#define MOTOR_ENABLE PA4
#define MOTOR_DIR PA3

#define K_p -1.15
#define K_i 0.05
#define K_d 0.01
//double Kp, Ki, Kd;

#define dt 0.01
#define MAX_speed 200
#define min_integral 0.1

#define ENCODER_MIN 1000
#define maxError 1
#define K_p_speed 0.55

static int16_t encoder_maxvalue;
static int16_t reference_value = 0;

//integral
static int16_t sumError;

//Timer counter for score keeping
static int counter = 0;
int timer = 0;
static int joystick_flag = 0;
static int timer_flag = 0;

/*
static double K_P, K_I, K_D;

void PID_tuning(double K_p,double K_i,double K_d){
	K_P=K_p;
	K_I=K_i;
	K_D=K_d;
}*/


int get_maxvalue(){
	return encoder_maxvalue;
}

void control_set_joystick_flag(int flag){
	joystick_flag = flag;
}

void control_set_speed(int value){
	uint8_t abs_value;
	
	//Change motor direction based on sign
	if(value < 0){
		clear_bit(MJ1_PORT, MOTOR_DIR);
	}
	else{
		set_bit(MJ1_PORT, MOTOR_DIR);
	}
	
	//Set max value to be 100
	if(abs(value)>100){
		value = 100;
	}
	abs_value = (abs(value)*255/100);
	DAC_write(abs_value);
	_delay_us(5);
}

void inti_clock(){
	//Trigger interrupt with interval of 100hz FQ 
	OCR3A = 10400;

	//Enable CTC mode
	TCCR3A |= (1 << COM3A0);

	//Prescale 8
	TCCR3B = (1 << CS31) | (1 << WGM32);	
	
	//Enable compare match A interrupt
	ETIMSK |= (1 << OCIE3A);
}

void control_init(){
	//Initiate DAC
	DAC_init();
	printf("DAC intiated\n\r");

	  // Set PortA (MJ1) as output
        DDRA = 0xFF;
        
        // Set PortC (MJ2) as input
        DDRC = 0x0;
        
        //Enable motor
        set_bit(PORTA, MOTOR_ENABLE);
        
        //Enable encoder
        clear_bit(PORTA, ENCODER_OUTPUT_ENABLE);
       // control_set_speed(-40);
        _delay_ms(200);
	control_set_reference(0);
	sumError = 0;
}

void control_set_reference(uint8_t value){
	reference_value = value;
}

void control_encoder_calibrate(){
	//set_bit(MJ1_PORT, ENCODER_OUTPUT_ENABLE); //Encoder Enabled
	control_set_speed(40);	//Set motor speed
	int i = 0;
	while(i<200){
		if(TCNT2 > 100){
			i++;
			TCNT2 = 0;
		}
	}
	control_set_speed(0);
	clear_bit(PORTA, ENCODER_RESET);
	_delay_ms(20);
	set_bit(PORTA, ENCODER_RESET);
	_delay_ms(20);
	control_set_speed(-40);
	
	i = 0;
	while(i<200){
		if(TCNT2 > 100){
			i++;
			TCNT2 = 0;
		}
	}
	control_set_speed(0);
	encoder_maxvalue = read_encoder();
	printf("Max encoder value: %i \n\r",encoder_maxvalue);
}

uint8_t reverse_byte(uint8_t byte){
	uint8_t bits = sizeof(byte) * 8;
	uint8_t reversed_byte = 0;
	uint8_t i, temp_bit;
	
	for (i = 0; i < bits ; i++)    {
		temp_bit = (byte & (1 << i));
		if(temp_bit){
			reversed_byte |= (1 << ((bits - 1) - i));
		}
	}
	
	return reversed_byte;
}


int16_t read_encoder(void){
	
	volatile int16_t encoder_byte=0;
	
	clear_bit(MJ1_PORT, ENCODER_SELECT_BYTE); //Set SEL low to get high bytes
	_delay_us(150); // wait 20us
	
	encoder_byte |= (reverse_byte(MJ2_DATA)<< 8); //READ MSB
	
	set_bit(MJ1_PORT, ENCODER_SELECT_BYTE); //Set SEL high to get low bites
	_delay_us(150);
	
	encoder_byte |= (reverse_byte(MJ2_DATA) << 0);
	_delay_us(5);
	
	return encoder_byte;
}

void control_speed_reg(int speed){
	//Speed regulator for joystick
	int16_t encodervalue = read_encoder();
	int output = speed*K_p_speed;
	int16_t error = 200;
	
	if((encodervalue > (encoder_maxvalue-error)))
	{
		output = 0;
		if(speed > 0){
			output=speed*K_p_speed;
		}
	}
	else if((encodervalue < 2000))
	{
		//printf("Encoder min og speed: %i",speed);
		output = 0;
		if (speed < 0)
		{
			output=speed*K_p_speed;
		}
	}
	control_set_speed(output);
}

void control_write_speed(int speed){
	DAC_write(speed);
	_delay_us(5);
}

int get_timer_value(void){
	return timer;
}

void control_reset_integral(void){
	sumError = 0;
}
void control_reset_timer(void){
	timer = 0;
}

void control_set_timer_flag(int flag){
	timer_flag = flag;
}


ISR (TIMER3_COMPA_vect)
{
	if(timer_flag){
		counter++;
		if(counter>100){
			timer++;
			if(timer>255){ //remove overflow
				timer = 0;
			}
			counter=0;
		}
	}
	
	if (joystick_flag)
	{
		return;
	}
	
	int16_t error, output;
	//printf("Encoder value: %i",read_encoder());
	int16_t encodervalue = read_encoder();
	if((encodervalue > encoder_maxvalue) || encodervalue<-4){
		control_set_speed(0);
		return;
	}

	//printf("Encoder : %i\n",encodervalue);
	error = (100-reference_value) - encodervalue/(encoder_maxvalue/100);
	if(abs(error) < 3){
		error=0;
		control_set_speed(0);
		return;
	}
	
	if(abs(error)>min_integral){
		sumError = sumError + error*dt;
	}
	
	output = K_p*error + K_i*sumError;
	
	if(output > 200){
		output = MAX_speed;
	}
	else if (output < -200){
		output = -MAX_speed;
	}
	control_set_speed(output);

	return;
}