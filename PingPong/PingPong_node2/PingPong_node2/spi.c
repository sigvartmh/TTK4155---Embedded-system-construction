#include <avr/io.h>
#include "spi.h"

//Define SPI pins
#define SPI_SS PB0
#define SPI_MOSI PB2
#define SPI_MISO PB3
#define SPI_SCK PB1

int SPI_init(void) {
	//Set MOSI, SCK and SS as output pins
	DDRB |= (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS);
	
	//Set MISO as input pin
	DDRB &= ~(1<<SPI_MISO);
	
	//Enable SPI in master mode and set clock rate fosc/128
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1) | (1<<SPR0);
	
	return 0;
}

int SPI_send(char data) {
	//Start the transmission
	SPDR = data;
	
	//Wait for data to be transmitted (checks if the register is empty)
	while(!(SPSR & (1<<SPIF)));
	
	return 0;
}

uint8_t SPI_read(void) {
	//Send dummy data to read from slave
	SPI_send(0);
	
	//Wait for data to be received
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}

void SPI_select(void) {
	//Set !SS to 0 to select the slave
	PORTB &= ~(1<<SPI_SS);
}

void SPI_deselect(void) {
	//Set !SS to 1 to deselect the slave
	PORTB |= (1<<SPI_SS);
}
