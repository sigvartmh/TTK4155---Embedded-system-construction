#include <avr/io.h>

int ADC_init(void) {
	//Use AVCC as reference, result left adjusted
	ADMUX &= ~(1 << REFS1);
	ADMUX |= (1 << REFS0) | (1 << ADLAR);
	
	//Use channel 0
	ADMUX &= ~(1 << MUX4) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);
	
	//Enable ADC and use free running
	ADCSRA |= (1 << ADEN) | (1 <<ADFR);
	
	return 0;
}

void ADC_start(void) {
	//Start the ADC
	ADCSRA |= (1 << ADEN) | (1 <<ADFR);
	ADCSRA |= (1 << ADSC);
}

void ADC_stop(void) {
	//Stop the ADC
	ADCSRA &= ~(1 << ADEN);
}