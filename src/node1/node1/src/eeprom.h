#ifndef EEPROM_H_
#define EEPROM_H_

int EEPROM_write(unsigned int address, unsigned char data);
unsigned char EEPROM_read(unsigned int address);
int EEPROM_save_score(int8_t data);

#endif