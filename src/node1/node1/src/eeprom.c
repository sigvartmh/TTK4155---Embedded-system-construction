#include <avr/io.h>
#include <avr/interrupt.h>

int EEPROM_write(unsigned int address, unsigned char data) {
	//Disable interrupts
	cli();
	
	//Wait for previous write to complete
	while (EECR & (1 << EEWE));
	
	//Set up the address and data to write
	EEAR = address;
	EEDR = data;
	
	//Write the data to EEPROM
	EECR |= (1 << EEMWE);
	EECR |= (1 << EEWE);

	//Enable interrupts
	sei();
	
	return 0;	
}

unsigned char EEPROM_read(unsigned int address) {
	//Wait for previous write to complete
	while (EECR & (1 << EEWE));
	
	//Set up the address to read
	EEAR = address;
	
	//Read the data from EEPROM
	EECR |= (1 << EERE);
	
	return EEDR;
}

int EEPROM_save_score(int8_t data) {
	uint8_t temp[5], temp_index, value;
	temp_index = 4;
	
	for (int i = 4; i >= 0; i--) {
		value = EEPROM_read(i);
		if (data > value) {
			temp[temp_index] = value;
			//Max value
			if (i == 0) {
				EEPROM_write(0, data);
				//Reorder values
				while (temp_index < 4) {
					EEPROM_write(temp_index+1, temp[temp_index]);
					temp_index++;
				}
				return 0;
			}
			temp_index--;
		} else {
			temp[temp_index] = data;
			//Reorder values
			while (temp_index < 4) {
				EEPROM_write(temp_index+1, temp[temp_index]);
				temp_index++;
			}
			return 0;
		}
	}

	return 0;	
}