#include <avr/io.h>
#include <stdlib.h>
#include "oled.h"
#include "menu.h"
#include "uart.h"

menu_t* create_menu(char* name, uint8_t selected, menu_t *sub_item){
	menu_t *new_menu_item =(menu_t*)malloc(sizeof(menu_t));
	
	if(new_menu_item == NULL){
		fprintf(uart,"Out of memory!!! (create_node)\n");
		exit(1);
	}
	new_menu_item -> name = name;
	new_menu_item -> selected = NULL;
	new_menu_item -> parent = NULL;
	new_menu_item -> sub_item = sub_item;
	
	return new_menu_item;
	
}

menu_t* insert_item(char* name, uint8_t selected){
	
}



void draw_menu()
{
	OLED_print("======Menu======");
	OLED_goto_line(1);
	for(int i=0;i<16;i++){
		OLED_print("-");
	}	
	OLED_pos(2,4);
	OLED_print(">Option 1");
	
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
	OLED_goto_line(7);
	OLED_print_char('+');
	for(int i=1;i<15;i++){
		OLED_print("-");
	}
	OLED_print_char('+');

};