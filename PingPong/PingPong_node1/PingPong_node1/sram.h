#ifndef SRAM_H_
#define SRAM_H_

int SRAM_init(void);
int SRAM_write(unsigned int address, unsigned int data);
void SRAM_test(void);

#endif