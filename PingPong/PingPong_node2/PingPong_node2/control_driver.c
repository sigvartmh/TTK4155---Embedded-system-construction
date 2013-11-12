#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"

#include "setup.h"
#include "DAC_driver.h"

//PORTF connected to DAC

//MJ1 Connected to PORTA
//Motor
#define MOTOR_PORT PORTA
#define MOTOR_DDR  DDRA

//MJ2 Connected to PORTC
//Encoder
#define ENCODER_PORT PORTC
#define ENCODER_DDR  DDRC
#define ENCODER_DATA PINC


#define MOTOR_ENABLE PA4
#define MOTOR_DIR PA3

#define ENCODER_SELECT_BYTE PA5
#define ENCODER_RESET PA6
#define ENCODER_OUTPUT_ENABLE PA7

static int encoder_maxvalue;
static int reference_value = 0;

int get_maxvalue(){
	return encoder_maxvalue;
}

void control_set_speed(int value){
	uint8_t abs_value;
	if(value < 0){
		clear_bit(MOTOR_PORT, MOTOR_DIR);
		printf("Changed motor DIR\n\r");
	}
	else{
		set_bit(MOTOR_PORT, MOTOR_DIR);
	}
	
	if(abs(value)>100){
		value = 100;
	}
	printf("Writing motor speed value: %i \n\r",abs(value)*255/100);
	abs_value = (abs(value)*255/100);
	DAC_write(abs_value);
	_delay_us(5);
}

void control_init(){
	//Initiate DAC
	DAC_init();
	printf("DAC intiated\n\r");

	DDRA = 0xFF; //PORTC(MJ1) output
	DDRC = 0x00; //PORTG(MJ2) input

	set_bit(MOTOR_PORT, MOTOR_ENABLE); //Motor enabled
	set_bit(MOTOR_PORT, ENCODER_OUTPUT_ENABLE); //Set !OE to high which = low
	
	clear_bit(MOTOR_PORT,ENCODER_RESET);
	set_bit(MOTOR_PORT, ENCODER_RESET);
	
	printf("Enabled motor \n\r");
}

void control_encoder_calibrate(){
	set_bit(MOTOR_PORT, ENCODER_OUTPUT_ENABLE); //Encoder Enabled
	
	control_set_speed(-40);	//Set motor speed
	int i = 0;
	while(i<200){
		if(TCNT2 > 100){
			i++;
			TCNT2 = 0;
		}
	}
	control_set_speed(0);
	set_bit(MOTOR_PORT, ENCODER_RESET);
	_delay_us(20);
	clear_bit(MOTOR_PORT, ENCODER_RESET);
	control_set_speed(40);
	
	i = 0;
	while(i<200){
		if(TCNT2 > 100){
			i++;
			TCNT2 = 0;
		}
	}
	control_set_speed(0);
	encoder_maxvalue = read_encoder();
}

uint8_t reverse_bit(uint8_t bits){
	uint8_t  NO_OF_BITS = sizeof(bits) * 8;
	uint8_t reverse_num = 0, i, temp;
	for (i = 0; i < NO_OF_BITS; i++)    {
		temp = (bits & (1 << i));
		if(temp)
		reverse_num |= (1 << ((NO_OF_BITS - 1) - i));
	}
	return reverse_num;
}

void control_set_reference(int value){
	reference_value = value;
}

void controler_update_input(float dt){
	int error, control_output;
	control_output =((read_encoder())/(encoder_maxvalue/200) - 100);
	//output = PID_calculations(reference_value, encoder_output,0);
	control_set_speed(control_output);
}
/*

int16_t read_encoder(){
	//set_bit(MOTOR_PORT,ENCODER_RESET);
	int16_t position = 0;
	uint8_t byte = 0;
	
	clear_bit(MOTOR_PORT, ENCODER_OUTPUT_ENABLE); //Enable output from encoder
	clear_bit(MOTOR_PORT, ENCODER_SELECT_BYTE); //Set SEL low to get high bytes
	
	_delay_us(20); // wait 20us
	
	byte = ENCODER_DATA; //READ MSB
	position = (reverse_bit(byte) << 8);//(REVERSE) READ MSB
	
	set_bit(MOTOR_PORT, ENCODER_SELECT_BYTE); //Set SEL high to get low bites
	_delay_us(20);
	byte = PINC;
	
	position |= (reverse_bit(byte)<<0); // READ LSB
	
	//_bit(MOTOR_PORT, ENCODER_RESET);
	set_bit(MOTOR_PORT, ENCODER_OUTPUT_ENABLE);

	return position;
}
*/

int16_t read_encoder(){
	
	int16_t byte = 0;
	
	clear_bit(MOTOR_PORT,ENCODER_OUTPUT_ENABLE);
	clear_bit(MOTOR_PORT,ENCODER_SELECT_BYTE);
	_delay_us(20);
	
	byte |= (PINC << 8); //MSB
	
	set_bit(MOTOR_PORT,ENCODER_SELECT_BYTE);
	_delay_us(20);
	
	byte |= (PINC << 0); //LSB
	
	clear_bit(MOTOR_PORT,ENCODER_RESET);
	_delay_us(10);
	set_bit(MOTOR_PORT,ENCODER_RESET);
	
	return byte;
}