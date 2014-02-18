#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>

#define SOLINOIDPORT PORTD
#define SOLINOIDDDR	 DDRD
#define SOLINOID_PIN PD4//(solonoid output pin)

void shooter_init(){
	
	//Clear and set bits
	clear_bit(DDRD,SOLINOID_PIN);
	clear_bit(PORTD, SOLINOID_PIN);
	//_delay_ms(100);
	set_bit(DDRD, SOLINOID_PIN);
	set_bit(PORTD, SOLINOID_PIN);

	//intiate timer with 1/1024 prescaler
	set_bit(TCCR2,CS22);
	set_bit(TCCR2,CS20);
	
	clear_bit(PORTD, SOLINOID_PIN);
	TCNT2 =0; //set timer to 0
	int i = 0;
	while(i<20){
		if(TCNT2 > 100){
			i++;
			TCNT2 = 0;
		}
	}
	set_bit(PORTD,SOLINOID_PIN);
}

void shooter_shoot(){
	clear_bit(PORTD, SOLINOID_PIN);
	TCNT2 =0; //set timer to 0
	int i = 0;
	while(i<40){
		if(TCNT2 > 100){
			i++;
			TCNT2 = 0;
		}
	}
	set_bit(PORTD,SOLINOID_PIN);
}
