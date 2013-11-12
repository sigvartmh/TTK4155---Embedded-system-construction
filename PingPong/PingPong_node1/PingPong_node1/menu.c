#include <avr/io.h>
#include <stdlib.h>
#include "oled.h"
#include "menu.h"

struct menu_t main_menu;
struct menu_item_t start, playing;
struct menu_item_t high_scores, scores;
uint8_t item_selected;
	
void init_menu(void) {
	//Define the menu structure
	main_menu.name = "Menu";
	main_menu.items[0] = &start;
	main_menu.items[1] = &high_scores;
	main_menu.selected = 1;
	
	start.name = "1.Start";
	start.parent_item = NULL;
	start.sub_item = &playing;
	start.selected = 0;
	
	playing.name = "---Game on---";
	playing.parent_item = &start;
	playing.sub_item = NULL;
	playing.selected = 0;
	
	high_scores.name = "2.High Scores";
	high_scores.parent_item = NULL;
	high_scores.sub_item = &scores;
	high_scores.selected = 0;
	
	scores.name = "---High Scores---";
	scores.parent_item = &high_scores;
	scores.sub_item = NULL;
	scores.selected = 0;
	
	item_selected = 1;
}

uint8_t draw_menu(uint8_t menu_display, uint8_t direction) {
	
	switch(menu_display) {
		//Draw main menu (2 sub-items)
		case 0:
			//Draw the main menu
			OLED_home();
			OLED_print("======Menu======");
			OLED_goto_line(1);
			for(int i = 0; i < 16; i++) {
				OLED_print("-");
			}
			for(int i = 2; i < 7; i++){
				OLED_pos(i,0);
				OLED_print_char('|');
			}
			for(int i = 2; i < 7; i++){
				OLED_pos(i,15);
				OLED_print_char('|');
			}
			
			OLED_pos(2,3);
			OLED_print(main_menu.items[0]->name);
			OLED_pos(3,3);
			OLED_print(main_menu.items[1]->name);
			OLED_pos(4,4);
			OLED_print(" Option 3");
			OLED_pos(5,4);
			OLED_print(" Option 4");
			OLED_pos(6,4);
			OLED_print(" Option 5");
			
			OLED_goto_line(7);
			OLED_print_char('+');
			for(int i = 1; i < 15; i++){
				OLED_print("-");
			}
			OLED_print_char('+');
			
			//Draw cursor
			if (direction == 1 && item_selected == 2) {			//Move cursor up
				item_selected--;
			} else if (direction == 2 && item_selected == 1) {	//Move cursor down
				item_selected++;
			}
			OLED_pos(item_selected+1,1);
			OLED_print_char('x');
		break;
		
		//Draw start game (no sub-items)
		case 1:	
			//Draw screen
			OLED_home();
			OLED_print(playing.name);
		
			//Draw cursor
			item_selected = 1;
			OLED_pos(item_selected,0);
			OLED_print_char('x');
		break;
		
		//Draw high scores menu (1 sub-item)
		case 2:
			//Draw screen
			OLED_home();
			OLED_print(scores.name);
			OLED_pos(1,2);
			OLED_print("1000 - Erick");
			OLED_pos(2,2);
			OLED_print("RETURN");
					
			//Draw cursor
			item_selected = 1;
			OLED_pos(item_selected+1,0);
			OLED_print_char('x');
		break;
		
		default:
		break;
	}
	
	return item_selected;
}