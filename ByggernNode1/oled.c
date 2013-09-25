#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "font_8x8.h"
#include "oled.h"

//Address for the OLED commands
volatile char *oled_cm = (char *) 0x1000;
//Address for the OLED data
volatile char *oled_dt = (char *) 0x1200;

int OLED_init(void) {
	//Enable the external memory interface/4 bits address
	MCUCR  |= (1<<SRE);
	SFIOR  |= (1<<XMM2);

	//Setup the OLED display
	*oled_cm = 0xAE; //display off
	*oled_cm = 0xA1; //segment remap
	*oled_cm = 0xDA; //common pads hardware: alternative
	*oled_cm = 0x12;
	*oled_cm = 0xC8; //common output scan direction:com63~com0
	*oled_cm = 0xA8; //multiplex ration mode:63
	*oled_cm = 0x3F;
	*oled_cm = 0xD5; //display divide ratio/osc. freq. mode
	*oled_cm = 0x80;
	*oled_cm = 0x81; //contrast control
	*oled_cm = 0x50;
	*oled_cm = 0xD9; //set pre-charge period
	*oled_cm = 0x21;
	*oled_cm = 0x20; //set Memory Addressing Mode
	*oled_cm = 0x02;
	*oled_cm = 0xDB; //VCOM deselect level mode
	*oled_cm = 0x30;
	*oled_cm = 0xAD; //master configuration
	*oled_cm = 0x00;
	*oled_cm = 0xA4; //out follows RAM content
	*oled_cm = 0xA6; //set normal display
	*oled_cm = 0xAF; //display on
	
	//Clear the display
	for (int k = 0; k < 8; k++) {
		OLED_clear_line(k);
	}
	
	//Set lower column start address
	*oled_cm = 0x00;
	//Set higher column start address
	*oled_cm = 0x10;
	//Set page start address
	*oled_cm = 0xB0;

	return 0;
}

int OLED_goto_line(int line) {
	//Set lower column start address
	*oled_cm = 0x00;
	//Set higher column start address
	*oled_cm = 0x10;
	//Set page address
	if (line < 8) {
		*oled_cm = 0xB0 + line;	
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
				*oled_dt = pgm_read_byte(&font[0][i]);
			}
		}
	} else {
		return 1;
	}
	
	return 0;
}

int OLED_print_char(char data) {
	uint8_t character = data - 32;
	
	//Write the complete character (8x8)
	for(int i = 0; i < 8; i++) {
		*oled_dt = pgm_read_byte(&font[character][i]);
	}
	
	return 0;
}

int OLED_printf(char *data) {
	int i = 0;
	
	//Write the string
	while (data[i] > 0x1F && data[i] < 0x7F){
		OLED_print_char(data[i]);
		i++;
	}
	
	return 0;
}