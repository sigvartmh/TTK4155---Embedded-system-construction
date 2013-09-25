#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "font_8x8.h"
#include "oled.h"

//Address for the OLED commands
#define volatile char *OLED_cmdd = (char *) 0x1000;
//Address for the OLED data
#define volatile char *OLED_data = (char *) 0x1200;

int OLED_init(void) {
	//Enable the external memory interface/4 bits address
	MCUCR  |= (1<<SRE);
	SFIOR  |= (1<<XMM2);

	//Setup the OLED display
	
	*OLED_cmd = 0xAE; //display off
	*OLED_cmd = 0xA1; //segment remap
	
	//common pads hardware: alternative
	*OLED_cmd = 0xDA; 
	*OLED_cmd = 0x12;
	
	*OLED_cmd = 0xC8; //common output scan direction:com63~com0

	//multiplex ration mode:63
	*OLED_cmd = 0xA8; 
	*OLED_cmd = 0x3F;

	//display divide ratio/osc. freq. mode
	*OLED_cmd = 0xD5; 
	*OLED_cmd = 0x80;

	//contrast control
	*OLED_cmd = 0x81; 
	*OLED_cmd = 0x50;

	//set pre-charge period
	*OLED_cmd = 0xD9; 
	*OLED_cmd = 0x21;

	//set Memory Addressing Mode
	*OLED_cmd = 0x20; 
	*OLED_cmd = 0x02;

	//VCOM deselect level mode
	*OLED_cmd = 0xDB;
	*OLED_cmd = 0x30;

	//master configuration
	*OLED_cmd = 0xAD; 
	*OLED_cmd = 0x00;

	*OLED_cmd = 0xA4; //out follows RAM content
	*OLED_cmd = 0xA6; //set normal display
	*OLED_cmd = 0xAF; //display on
	
	//Set lower column start address
	*OLED_cmd = 0x00;
	//Set higher column start address
	*OLED_cmd = 0x10;
	//Set page start address
	*OLED_cmd = 0xB0;
	
	//Clear the display
	for (int k = 0; k < 8; k++) {
		OLED_clear_line(k);
	}

	return 0;
}

int OLED_goto_line(int line) {
	//Set lower column address
	*OLED_cmd = 0x00;
	//Set higher column address
	*OLED_cmd = 0x10;
	//Set page address
	if (line < 8) {
		*OLED_cmd = 0xB0 | line;
	} else {
		return 1;
	}
	
	return 0;
}

int OLED_clear_line(int line) {
	//Set page address
	int r = OLED_goto_line(line);
	
	//Clear the page
	if (r == 0) {
		for (int j = 0; j < 16; j++) {
			for(int i = 0; i < 8; i++) {
				*OLED_data = pgm_read_byte(&font[0][i]);
			}
		}
	} else {
		return 1;
	}
	
	return 0;
}

int OLED_pos(int row, int column) {
	//Set column
	if (column < 16) {
		uint8_t col = column * 8;
		//Set lower column start address
		*OLED_cmd = (col | 0x00);

		//Set higher column start address
		*OLED_cmd = (col | (1<<4))
	}
	
	//Set row
	if (row < 8) {
		//Set page address
		*OLED_cmd = 0xB0 | row;
	}
	
	return 0;
}

int OLED_write_char(char c) {
	
	//Write the complete character (8x8)
	for(int i = 0; i < FONTWIDTH; i++) {
		*OLED_data = pgm_read_byte(&font[c-' '][i]);
	}
	
	return 0;
}

int OLED_print(char *data) {
	int i = 0;
	
	//Write the string
	while (data[i] > 0x1F && data[i] < 0x7F){
		OLED_print_char(data[i]);
		i++;
	}
	
	return 0;
}