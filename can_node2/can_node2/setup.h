#ifndef _SETUP_H_
#define _SETUP_H_

//Setup for the OSC fq which is then set to be the CPU fq
//Not sure if it's the right OSC freq. will test with usart
#define F_OSC 8500000UL 
#define F_CPU F_OSC
#define BAUD  19200
//#define BAUD  9600 

//Added from the project description to help setting bits in registers
#define set_bit(reg,bit) (reg |= (1 << bit))
#define clear_bit(reg,bit) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
//#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
//#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) ) 

#endif
