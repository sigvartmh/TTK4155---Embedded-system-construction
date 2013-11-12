#include "setup.h"
#include <avr/io.h>


#define SOLINOID_PIN //(solonoid output pin)

void shooter_init(){
	set_bit(DDRx, SOLENOID_PIN);
	set_bit(PORTx, SOLENOID_PIN);

	//intiate timer with 1/1024 prescaler
	set_bit(TCCR2,CS22);
	set_bit(TCCR2,CS20);
}

void shooter_shoot(){
	clear_bit(PORTx, SOLENOID_PIN);
	TCNT2 =0; //set timer to 0
	int i = 0;
	while(i<20){
		if(TCNT2 > 100){
			i++;
			TCNT2 = 0;
		}
	}
	set_bit(PORTx,SOLENOID_PIN);
}
