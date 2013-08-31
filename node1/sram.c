#include <avr/io.h>
#include <stdio.h>

void initSRAM(){
	MCUCR  |= (1<<SRW10) | (1<<SRE); //if we include setup.h we can do set_bit instaed
	EMCUCR |= (1<<SRW00);
	SFIOR  |= (1<<XMM2);
}

void SRAM_test(){
