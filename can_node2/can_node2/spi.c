#include <avr/io.h>
#include "spi.h"

//Define SPI port
#define SPI_DDR DDRB
#define SPI_PORT PORTB

//Define SPI pins
#define SPI_SS PB0
#define SPI_MOSI PB2
#define SPI_MISO PB3
#define SPI_SCK PB1

int SPI_init(void) {
	//Set MOSI, SCK and SS as output pins
	SPI_DDR |= (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS);
	
	//Set MISO as input pin (maybe not needed)
	SPI_DDR &= ~(1<<SPI_MISO);
	
	//Enable SPI in master mode and set clock rate fosc/16
	SPCR	 |= ((1<<SPE) | (1<<MSTR) | ((1<<SPR1)| (1<<SPR0)));
	
	return 0;
}

void SPI_write(uint8_t data) {
	
	//Start the transmission
	SPDR = data;
	
	//Wait for data to be transmitted (checks if the register is empty)
	while(!(SPSR & (1<<SPIF)));
	
}

uint8_t SPI_read(void) {
	//Send dummy data to read from slave
	SPDR=0x00;
	
	//Wait for data to be received
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}

void SPI_select(void) {
	//Set !SS to 0 to select the slave
	SPI_PORT &= ~(1<<SPI_SS);
}

void SPI_deselect(void) {
	//Set !SS to 1 to de-select the slave
	SPI_PORT |= (1<<SPI_SS);
}