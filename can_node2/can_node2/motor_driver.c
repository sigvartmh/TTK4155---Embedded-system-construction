#include "setup.h"
#include "DAC_driver.h"
//MJ1 Connected to PORTC

//Motor
#define ENABLE PC4
#define DIR PC3

//MJ2 Connected to PORTG
#define ENC_ENABLE
#define ENC_SELECT
#define ENC_RESET

static int encoder_maxvalue
static int reference_value = 0;

void Control_set_speed(int value){
	if(val < 0) clear_bit(PORTC, DIR);
	else set_bit(PORTC, DIR);
	if(abs(value)>100){
		value = 100;
	}

	value = (abs(value)*255/100);
	DAC_write(value);

}

uint8_t read_encoder(){
	int position = 0;
	uint8_t byte;

	clear_bit(PORTC, ENCODER_SELECT);
	_delay_us(20);
	byte = PINC;

	position = byte;
	position = position << 8;

	set_bit(PORTC, ENABLE_SELECT);

	position += byte;

	return position;
}

void Control_init(){
	//Initiate DAC

	DDRC = 0xFF; //PORTC(MJ1) output
	DDRG = 0x00; //PORTG(MJ2) input

	set_bit(PORTC, MOTOR_ENABLE);
	clear_bit(PORTC, ENCODER_ENABLE);

	//Calibrate encoder
	clear_bit(DDRD, PD7);
	Control_set_speed(-40);
	
	_delay_ms(1500);
	clear_bit(PORTC, ENCODER_RESET);
	set_bit(PORTC, ENCODER_RESET);

	while(check_bit(PIND, PD7)){};

	encoder_maxvalue = read_encoder();

	Control_set_speed(0);

}

Control_set_reference(int value){
	reference = value;
}

Controler_update_input(float dt){
	int error, output;
	error = reference - ((read_encoder())/(encoder_max/200) - 100);
	output = regulator(error, dt);
	Control_set_speed(output);
}