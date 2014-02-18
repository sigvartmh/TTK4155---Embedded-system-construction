#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "font_8x8.h"
#include "font_drawings.h"
#include "oled.h"
#include "sram.h"

//Address for the OLED commands
volatile char *OLED_cmd = (char *) 0x1000;
//Address for the OLED data
volatile char *OLED_data = (char *) 0x1200;

uint8_t page, col;

int OLED_init(void) {
	//Enable the external memory interface/4 bits address
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);

	//Setup the OLED display
	
	//display off
	*OLED_cmd = 0xAE;
	//segment remap
	*OLED_cmd = 0xA1;
	
	//common pads hardware: alternative
	*OLED_cmd = 0xDA; 
	*OLED_cmd = 0x12;
	
	//common output scan direction:com63~com0
	*OLED_cmd = 0xC8; 

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

	//out follows RAM content
	*OLED_cmd = 0xA4; 

	//set normal display
	*OLED_cmd = 0xA6;
	//display on
	*OLED_cmd = 0xAF; 
	
	//Set page start address
	*OLED_cmd = 0xB0;
	//Set lower column start address
	*OLED_cmd = 0x00;
	//Set higher column start address
	*OLED_cmd = 0x10;
	
	//Clear the display
	OLED_clear();
	OLED_home();

	return 0;
}

int OLED_home(void) {
	//Reset the page and column
	page = 0;
	col = 0;
	
	//Set the cursor to the start of the screen
	*OLED_cmd = 0x21;
	*OLED_cmd = 0x00;
	*OLED_cmd = 0x7f;
	
	*OLED_cmd = 0x22;
	*OLED_cmd = 0x00;
	*OLED_cmd = 0x7;
	
	return 0;
}

int OLED_goto_line(uint8_t line) {
	OLED_home();
	
	//Check if it's a valid page
	if (line < 8) {
		//Save the page we are moving to
		page = line;
		//Set lower column address
		*OLED_cmd = 0x00;
		//Set higher column address
		*OLED_cmd = 0x10;
		//Set page address
		*OLED_cmd = 0xB0 | line;
	}

	return 0;
}

int OLED_pos(uint8_t line, uint8_t column) {
	OLED_goto_line(line);
	
	//Check if it's a valid column according to the font
	if (column < (128/FONTWIDTH)) {
		//Save the column we are moving to
		col = column*FONTWIDTH;
		//Set lower column start address
		*OLED_cmd = 0x00 + (column*(FONTWIDTH)>>4);
		//Set higher column start address
		*OLED_cmd = 0x10 + (column*(FONTWIDTH)>>4);
	}
	
	return 0;
}

int OLED_clear_line(uint8_t line) {
	OLED_goto_line(line);
	
	//Clear the page
	for (int i = 0; i < 128; i++) {
		*OLED_data=0x00;
	}	
	
	OLED_home();
	
	return 0;
}

int OLED_clear(void) {
	//Clear every page
	for (int k = 0; k < 8; k++) {
		OLED_clear_line(k);
	}
	
	return 0;
}

int OLED_print_char(char c) {
	//Write the complete character
	for (int i = 0; i < FONTWIDTH; i++) {
		*OLED_data = pgm_read_byte(&font[c-' '][i]);
	}
	
	return 0;
}

int OLED_print(char *data) {
	int i = 0;
	
	//Write the complete string
	while(data[i] != '\0'){
		OLED_print_char(data[i]);
		i++;
	}
	
	return 0;
}

int OLED_sram_clear_line(uint8_t line) {
	OLED_goto_line(line);
	
	//Clear the page
	for (int i = 0; i < 128; i++) {
		SRAM_write(page*128 + i, 0);
	}
	
	OLED_home();
	
	return 0;
}

int OLED_sram_clear(void) {
	//Clear every page
	for (int k = 0; k < 8; k++) {
		OLED_sram_clear_line(k);
	}
	
	return 0;
}

int OLED_sram_print_char(char c) {
	//Write the complete character
	for (int i = 0; i < FONTWIDTH; i++) {
		SRAM_write(page*128 + col + i, pgm_read_byte(&font[c-' '][i]));
	}
	//Increment the column
	col += FONTWIDTH;
	
	return 0;
}

int OLED_sram_print(char *data) {
	int i = 0;
	
	//Write the complete string
	while(data[i] != '\0'){
		OLED_sram_print_char(data[i]);
		i++;
	}
	
	return 0;
}

int OLED_sram_draw_mario(void) {
	OLED_home();

	for (int j = 0; j < 8; j++) {
		for(int i = 0; i < 24; i++) {
			SRAM_write(j*128 + i, pgm_read_byte(&mario[j][i]));
		}
	}

	return 0;
}

int OLED_sram_draw_mushroom(void) {
	for (int j = 0; j < 4; j++) {
		for(int i = 0; i < 32; i++) {
			SRAM_write((j+page)*128 + (i+col), pgm_read_byte(&mushroom[j][i]));
		}
	}

	return 0;
}

void OLED_refresh(void) {
	//Print the screen from the SRAM
	for (int line = 0; line < 8; line++) {
		OLED_goto_line(line);
		for (int col = 0; col < 128; col++) {
			*OLED_data = SRAM_read(line*128 + col);
		}
	}
}

int OLED_draw_circle(uint8_t x, uint8_t y, uint8_t r) {
	int circle;
	
	if (r < 8) {
		circle = r - 1;
	} else {
		return -1;
	}
	
	//Set position
	OLED_goto_line(x);
	if (y < 128) {
		*OLED_cmd = 0x00 + (y >> 4);
		*OLED_cmd = 0x10 + (y >> 4);
	}

	//Draw circle (first part)
	for(int i = 0; i < 16; i++) {
		*OLED_data = pgm_read_byte(&circles[circle][i]);
	}
	
	//Set position
	OLED_goto_line(x+1);
	if (y < 128) {
		*OLED_cmd = 0x00 + (y >> 4);
		*OLED_cmd = 0x10 + (y >> 4);
	}
	
	//Draw circle (second part)
	for(int i = 16; i < 32; i++) {
		*OLED_data = pgm_read_byte(&circles[circle][i]);

	}

	return 0;
}