#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "oled.h"
#include "menu.h"
#include "uart.h"


void draw_menu()
{
	OLED_print("======Menu======");
	OLED_goto_line(1);
	for(int i=0;i<16;i++){
		OLED_print("-");
	}	
	OLED_pos(2,4);
	OLED_print(" Option 1");
	
	for(int i=2;i<7;i++){
	OLED_pos(i,0);
	OLED_print_char('|');
	}	
	
	for(int i=2;i<7;i++){
	OLED_pos(i,15);
	OLED_print_char('|');
	}	
	
	OLED_pos(3,4);
	OLED_print(" Option 2");
	OLED_pos(4,4);
	OLED_print(" Option 3");
	OLED_pos(5,4);
	OLED_print(" Option 4");
	OLED_pos(6,4);
	OLED_print(" Option 5");
	OLED_goto_line(7);
	OLED_print_char('+');
	for(int i=1;i<15;i++){
		OLED_print("-");
	}
	OLED_print_char('+');

};

int main_menu(int dir, int pos, int select){
	OLED_pos((pos+2),5);
	OLED_print_char('>');
		
	if(pos < 0){
		pos = 0;
	}
	else if(pos > 5){
		pos = 4;
	}
		
	if((dir == 1) && (pos != 0)){
		OLED_pos((pos+2),5);
		OLED_print_char(' ');
		pos = pos-1;
		OLED_pos((pos+2),5);
		OLED_print_char('>');
		return pos;
	}		
	else if((dir == 2) && (pos != 4)){
		OLED_pos((pos+2),5);
		OLED_print_char(' ');
		pos = pos+1;
		OLED_pos((pos+2),5);
		OLED_print_char('>');
		return pos;
	}
	
	if(select){
		switch(pos){
			case 0:
				OLED_clear();
				OLED_pos(3,5);
				OLED_print("Option 1");
				_delay_ms(3000);
				OLED_clear();
				OLED_goto_line(0);
				draw_menu();
				break;
			case 1:
				OLED_clear();
				OLED_pos(3,5);
				OLED_print("Option 2");
				_delay_ms(3000);
				OLED_clear();
				OLED_goto_line(0);
				draw_menu();
				break;
			case 2:
				OLED_clear();
				OLED_pos(3,5);
				OLED_print("Option 3");
				_delay_ms(3000);
				OLED_clear();
				OLED_goto_line(0);
				draw_menu();
				break;
			
			case 3:
				OLED_clear();
				OLED_pos(3,5);
				OLED_print("Option 4");
				_delay_ms(3000);
				OLED_clear();
				OLED_goto_line(0);
				draw_menu();
				break;
			
			case 4:
				OLED_clear();
				OLED_pos(3,5);
				OLED_print("Option 5");
				_delay_ms(3000);
				OLED_clear();
				OLED_goto_line(0);
				draw_menu();
				break;
		}
	}	
	
	return pos;
}