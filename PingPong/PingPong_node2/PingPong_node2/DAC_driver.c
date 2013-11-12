#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "TWI_Master.h"
#include "uart.h"
#include "setup.h"

#define SLAVE_ADDRESS_WRITE 0b01010000

void DAC_init()
{
	TWI_Master_Initialise();
	set_bit(DDRD, PD0); //SCL
	set_bit(DDRD, PD1); //SDA
	
}

void DAC_write(uint8_t value)
{
	unsigned char msgSize = 3;
	unsigned char* i2c_write = malloc(3*sizeof(char));
	
	i2c_write[0] = SLAVE_ADDRESS_WRITE;
	i2c_write[1] = 0x00;
	i2c_write[2] = (uint8_t) value;
	_delay_us(50);
	TWI_Start_Transceiver_With_Data(i2c_write, msgSize);
	printf("TWI transmite value: %i to DAC \n\r",i2c_write[2]);
	free(i2c_write);
	
}