#include "setup.h"
#include <avr/io.h>

int PWM_init(void) {
	//Clear OC1A (channel A) on compare match, use fast PWM, ICR1 used as TOP, prescaler (clk/8)
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1A &= ~(1 << COM1A0) & ~(1 << WGM10);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	TCCR1B &= ~(1 << CS12) & ~(1 << CS10);
	
	//Define PWM period of 20ms
	ICR1 = 20788;
	
	//Initialize pulse width 1.5ms
	OCR1A = 1551;
	
	return 0;
}

int PWM_set_pulse(unsigned int servo_angle) {
	//Check if it's between range
	if (servo_angle >= 930 && servo_angle <= 2171) {
		OCR1A = servo_angle;
	}
	
	return 0;
}