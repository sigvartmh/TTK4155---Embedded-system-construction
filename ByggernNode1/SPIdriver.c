#include "SPIdriver.h"
#include <avr/io.h>

//Set macros for PINS
#define SPI_MISO PB6
#define SPI_MOSI PB5
#define SPI_SCK PB7
#define SPI_SS PB4


int SPI_init(){ //you can do a shorthand if you want

	//
		SPCR |= (1<<SPE); //set SPI enabled in SPCRegister
		SPCR |= (1<<MSTR); //Set master selected on SPI mode
		SPCR |= (1<<SPR0); //set SCK rate (f_osc/16)

		DDRB |= (1<<SPI_MOSI); //set MOSI as output PIN B2
		DDRB |= (1<<SPI_SCK); //Set SCK as output PIN B1
		DDRB |= (1<<SPI_SS); //set !SS as output PIN B0

		DDRB &=~(1<<SPI_MISO) //set MISO as input pin PB3

		//set SS to 1

}

int SPI_transmit(char data){

	SPDR = data; //puts data in the SPD register
	while(!(SPSR & (1<<SPIF))){} // wait for data to be completely transmited(checks the register if its empty)
	return 0;
}

char SPI_receive(){

	//loopback
	/* SPI_transmit('NULL')*/

	while(!(SPSR & (1<<SPIF))){} //wait for data to be recived(same as above)
	return SPDR;
}

void SPI_selected(){
	PORTB &= ~(1<<SPI_SS); //(set !SS to 0 which = 1)
}

void SPI_deselected(){
	PORTB |= (1<<SPI_SS); //(set !SS to 1 which = 0)
}