#include <avr/io.h>
#include <stdio.h>
#include "setup.h"

int ADC_init(void) {
	//Enable the external memory interface/4 bits address
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	//Set the interrupt pin to input
	DDRE &= ~(1<<PINE0);
	
	return 0;
}

uint8_t ADC_read(uint8_t channel) {
	//Address for the ADC
	volatile char *adc = (char *) 0x1400;
	
	if(channel > 3) {return 0;}
	
	//Choose channel in ADC
	*adc = 0x04 | channel;
	
	//Wait for the data to be read (this can be done with an interrupt)
	while(test_bit(PINE, PINE0));
	
	return *adc;
}