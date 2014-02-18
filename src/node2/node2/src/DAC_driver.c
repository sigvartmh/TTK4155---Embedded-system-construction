#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "TWI_Master.h"

#define SLAVE_ADDRESS_WRITE 0x50; 

void DAC_init()
{
	TWI_Master_Initialise();
	set_bit(DDRD, PD0); //SCL port
	set_bit(DDRD, PD1); //SDA port
	
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
	free(i2c_write);
	
}