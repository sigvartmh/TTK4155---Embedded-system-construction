#include <avr/pgmspace.h>

#ifndef FONT_DRAWINGS_H_
#define FONT_DRAWINGS_H_

const unsigned char PROGMEM mario[8][24] = {
	//Line 0
	{0b00000000,0b00000000,0b00000000,0b00000000,0b11110000,0b11111100,0b11111111,0b11111111,
	 0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b11111100,0b11110000,0b11110000,0b11110000,0b11110000,0b11110000,0b00000000,0b00000000},
	//Line 1
	{0b00000000,0b00000000,0b11110000,0b11111100,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b11111111,0b11111111,0b11110000,0b11110000,0b11110000,0b11000000,0b00000000,0b00000000},
	//Line 2
	{0b00000000,0b00000000,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b00111111,0b00001111,0b00001111},
	//Line 3
	{0b00000000,0b00000000,0b00000000,0b00000000,0b11000000,0b11110000,0b11111111,0b11111111,
	 0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b00001111,0b00001111,0b00001111,0b00000011,0b00000000,0b00000000,0b00000000,0b00000000},
	//Line 4
	{0b11000000,0b11110000,0b11111100,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111100,0b11110000,0b11000000},
	//Line 5
	{0b11111111,0b11111111,0b11111111,0b00111111,0b00111111,0b11111111,0b11111111,0b11111111,
	 0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b11111111,0b11111111,0b11111111,0b00111111,0b00111111,0b11111111,0b11111111,0b11111111},
	//Line 6
	{0b00001111,0b00001111,0b00001111,0b00001111,0b11000000,0b11111111,0b11111111,0b11111111,
	 0b11111111,0b00111111,0b00001111,0b00001111,0b00001111,0b00001111,0b00111111,0b11111111,
	 0b11111111,0b11111111,0b11111111,0b11000000,0b00001111,0b00001111,0b00001111,0b00001111},
	//Line 7
	{0b11110000,0b11111100,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111100,0b11110000}
};

const unsigned char PROGMEM mushroom[4][32] = {
	//Line 0
	{0b00000000,0b00000000,0b11000000,0b11000000,0b11110000,0b11110000,0b00111100,0b00111100,
	 0b11111111,0b11111111,0b11111111,0b11111111,0b00111111,0b00111111,0b00000011,0b00000011,
	 0b00000011,0b00000011,0b00111111,0b00111111,0b11111111,0b11111111,0b11111111,0b11111111,
	 0b00111100,0b00111100,0b11110000,0b11110000,0b11000000,0b11000000,0b00000000,0b00000000},
	//Line 1
	{0b11111100,0b11111100,0b11111111,0b11111111,0b11111111,0b11111111,0b11111100,0b11111100,
	 0b00000000,0b00000000,0b11110000,0b11110000,0b11111100,0b11111100,0b11111100,0b11111100,
	 0b11111100,0b11111100,0b11111100,0b11111100,0b11110000,0b11110000,0b00000000,0b00000000,
	 0b11111100,0b11111100,0b11111111,0b11111111,0b11111111,0b11111111,0b11111100,0b11111100},
	//Line 2
	{0b11111111,0b11111111,0b11000011,0b11000011,0b11000011,0b11000011,0b11110000,0b11110000,
	 0b00110000,0b00110000,0b00110011,0b00110011,0b11111111,0b11111111,0b00111111,0b00111111,
	 0b00111111,0b00111111,0b11111111,0b11111111,0b00110011,0b00110011,0b00110000,0b00110000,
	 0b11110000,0b11110000,0b11000011,0b11000011,0b11000011,0b11000011,0b11111111,0b11111111},
	//Line 3
	{0b00000000,0b00000000,0b00000011,0b00000011,0b00111100,0b00111100,0b11000000,0b11000000,
	 0b11000000,0b11000000,0b11000000,0b11000000,0b11000011,0b11000011,0b11000000,0b11000000,
	 0b11000000,0b11000000,0b11000011,0b11000011,0b11000000,0b11000000,0b11000000,0b11000000,
	 0b11000000,0b11000000,0b00111100,0b00111100,0b00000011,0b00000011,0b00000000,0b00000000}
};

const unsigned char PROGMEM circles[7][32] = {
	//clear
	{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=2
	{0b00000110,0b00001001,0b00001001,0b00000110,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=3
	{0b00001100,0b00010010,0b00100001,0b00100001,0b00010010,0b00001100,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=4
	{0b00111100,0b01000010,0b10000001,0b10000001,0b10000001,0b10000001,0b01000010,0b00111100,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=5
	{0b01111000,0b10000100,0b00000010,0b00000001,0b00000001,0b00000001,0b00000001,0b00000010,
	 0b10000100,0b01111000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000000,0b00000000,0b00000001,0b00000010,0b00000010,0b00000010,0b00000010,0b00000001,
	 0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=6
	{0b11111000,0b00000100,0b00000010,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,
	 0b00000001,0b00000010,0b00000100,0b11111000,0b00000000,0b00000000,0b00000000,0b00000000,
	 0b00000001,0b00000010,0b00000100,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,
	 0b00001000,0b00000100,0b00000010,0b00000001,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=7
	{0b11110000,0b00001000,0b00000100,0b00000010,0b00000001,0b00000001,0b00000001,0b00000001,
	 0b00000001,0b00000001,0b00000010,0b00000100,0b00001000,0b11110000,0b00000000,0b00000000,
	 0b00000011,0b00000100,0b00001000,0b00010000,0b00100000,0b00100000,0b00100000,0b00100000,
	 0b00100000,0b00100000,0b00010000,0b00001000,0b00000100,0b00000011,0b00000000,0b00000000}
};

#endif