#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "oled.h"
#include "menu.h"
#include "buzzer.h"
#include "eeprom.h"

struct screen start, main_menu, game, scores, options;
uint8_t circle_inc, circle_dec, music_on, song_on;
static int uart_control_on, joystick_on;

struct screen * init_menu(void) {
	circle_inc = 2;		//min radius
	circle_dec = 7;		//max radius
	music_on = 1;
	song_on = 1;
	uart_control_on = 0;
	joystick_on = 0;
	
	BUZZER_choose_game_song(song_on);
	
	//Define the menu structure
	start.name = "start";
	start.parent = NULL;
	start.child[0] = &main_menu;
	start.child[1] = NULL;
	start.child[2] = NULL;
	start.child_selected = 0;
	start.game_on = 0;
	
	main_menu.name = "main";
	main_menu.parent = &start;
	main_menu.child[0] = &game;
	main_menu.child[1] = &scores;
	main_menu.child[2] = &options;
	main_menu.child_selected = 0;
	main_menu.game_on = 0;
	
	game.name = "game";
	game.parent = &scores;
	game.child[0] = NULL;
	game.child[1] = NULL;
	game.child[2] = NULL;
	game.child_selected = 0;
	game.game_on = 1;
	
	scores.name = "scores";
	scores.parent = &main_menu;
	scores.child[0] = NULL;
	scores.child[1] = NULL;
	scores.child[2] = NULL;
	scores.child_selected = 0;
	scores.game_on = 0;
	
	options.name = "options";
	options.parent = &main_menu;
	options.child[0] = NULL;
	options.child[1] = NULL;
	options.child[2] = NULL;
	options.child_selected = 0;
	options.game_on = 0;
	
	return &start;
}

void draw_screen(struct screen *display_screen, char *direction, uint8_t lives, uint16_t score) {
	if (strcmp(display_screen->name, "start") == 0) {
		//Startup animation
		if(circle_inc > 7) circle_inc = 2;
		if(circle_dec < 2) circle_dec = 7;
		OLED_draw_circle(5,50,1);
		OLED_draw_circle(5,50,circle_inc);
						
		OLED_draw_circle(5,70,1);
		OLED_draw_circle(5,70,circle_dec);
						
		OLED_draw_circle(5,90,1);
		OLED_draw_circle(5,90,circle_inc);
		circle_inc++;
		circle_dec--;
		_delay_ms(100);
		
	} else if (strcmp(display_screen->name, "main") == 0) {
		OLED_sram_clear();
		
		//Print screen
		OLED_sram_print("======Menu======");
		OLED_goto_line(1);
		for(int i = 0; i < 16; i++) {
			OLED_sram_print("-");
		}
		for(int i = 2; i < 7; i++) {
			OLED_pos(i,0);
			OLED_sram_print_char('|');
		}
		for(int i = 2; i < 7; i++) {
			OLED_pos(i,15);
			OLED_sram_print_char('|');
		}
		OLED_pos(2,2);
		OLED_sram_print("1.Start Game");
		OLED_pos(3,2);
		OLED_sram_print("2.High Scores");
		OLED_pos(4,2);
		OLED_sram_print("3.Options");
		OLED_goto_line(7);
		OLED_sram_print_char('+');
		for(int i = 1; i < 15; i++) {
			OLED_sram_print_char('-');
		}
		OLED_sram_print_char('+');

		//Draw cursor
		if (strcmp(direction, "UP") == 0) {
			if (display_screen->child_selected > 0) {
				display_screen->child_selected--;
			}
		} else if (strcmp(direction, "DOWN") == 0) {
			if (display_screen->child_selected < 2) {
				display_screen->child_selected++;
			}
		}
		OLED_pos(display_screen->child_selected+2, 1);
		OLED_sram_print_char('x');
			
	} else if (strcmp(display_screen->name, "game") == 0) {
		OLED_sram_clear();
		char score_str[3];
		
		//Print screen
		OLED_sram_print("====Playing=====");
		OLED_pos(1,1);
		OLED_sram_print("Score:");
		itoa(score, score_str,10);
		OLED_sram_print(score_str);
		
		//Draw lives
		switch (lives) {
			case 1:
				OLED_pos(3,1);
				OLED_sram_draw_mushroom();
				break;
			case 2:
				OLED_pos(3,1);
				OLED_sram_draw_mushroom();
				OLED_pos(3,6);
				OLED_sram_draw_mushroom();
				break;
			case 3:
				OLED_pos(3,1);
				OLED_sram_draw_mushroom();
				OLED_pos(3,6);
				OLED_sram_draw_mushroom();
				OLED_pos(3,11);
				OLED_sram_draw_mushroom();
				break;
			default:
				break;
		}
				
	} else if (strcmp(display_screen->name, "scores") == 0) {
		OLED_sram_clear();
		unsigned char score;
		char score_str[3];
		
		//Print screen
		OLED_sram_print("=====Scores=====");
		for (int i = 0; i < 5; i++) {
			OLED_pos(2+i,2);
			score = EEPROM_read(i);
			if (score > 0) {
				itoa(score,score_str,10);
				OLED_sram_print(score_str);
				OLED_sram_print(" - Erick");
			}
		}
		
		OLED_pos(7,2);
		OLED_sram_print("RETURN");
				
		//Draw cursor
		display_screen->child_selected = -1;
		OLED_pos(7,0);
		OLED_sram_print_char('x');
	
	} else if (strcmp(display_screen->name, "options") == 0) {
		OLED_sram_clear();
		
		//Print screen
		OLED_sram_print("=====Options====");
		OLED_pos(2,2);
		OLED_sram_print("RETURN");
		OLED_pos(3,2);
		if (music_on == 1) {
			OLED_sram_print("1.Music On");
		} else {
			OLED_sram_print("1.Music Off");
		}
		OLED_pos(4,2);
		if (game_song == 1) {
			OLED_sram_print("2.Song:Zelda");
		} else if (game_song == 2) {
			OLED_sram_print("2.Song:Mario1");
		} else if (game_song == 3) {
			OLED_sram_print("2.Song:Mario2");
		}
		OLED_pos(5,2);
		if (uart_control_on == 1) {
			OLED_sram_print("3.Web on");
		} else {
			OLED_sram_print("3.Web off");
		}
		OLED_pos(6,2);
		if (joystick_on == 1) {
			OLED_sram_print("4.Joystick on");
		} else {
			OLED_sram_print("4.Joystick off");
		}
		
		//Draw cursor
		if (strcmp(direction, "UP") == 0) {
			if (display_screen->child_selected > -1) {
				display_screen->child_selected--;
			}
		} else if (strcmp(direction, "DOWN") == 0) {
			if (display_screen->child_selected < 3) {
				display_screen->child_selected++;
			}
		}
		
		//Turn on/off music
		if (display_screen->child_selected == 0) {
			if ((strcmp(direction, "LEFT") == 0) || (strcmp(direction, "RIGHT") == 0)) {
				if (music_on == 1) {
					music_on = 0;
					BUZZER_start(0);
				} else {
					music_on = 1;
					BUZZER_start(1);
				}
			}
		//Change song selection
		} else if (display_screen->child_selected == 1) {
			if (strcmp(direction, "RIGHT") == 0) {
				if (song_on < 3) {
					song_on++;
					BUZZER_choose_game_song(song_on);
				}
			} else if (strcmp(direction, "LEFT") == 0) {
				if (song_on > 1) {
					song_on--;
					BUZZER_choose_game_song(song_on);
				}
			}
		//Turn on/off web control
		} else if (display_screen->child_selected == 2) {
			if ((strcmp(direction, "LEFT") == 0) || (strcmp(direction, "RIGHT") == 0)) {
				if (uart_control_on == 1) {
					uart_control_on = 0;
				} else {
					uart_control_on = 1;
				}
			}
		//Turn on/off joystick to control servo
		} else if (display_screen->child_selected == 3) {
			if ((strcmp(direction, "LEFT") == 0) || (strcmp(direction, "RIGHT") == 0)) {
				if (joystick_on == 1) {
					joystick_on = 0;
				} else {
					joystick_on = 1;
				}
			}
		}
		
		OLED_pos(display_screen->child_selected+3, 1);
		OLED_sram_print_char('x');
	}
}

uint8_t menu_get_option_uart(void) {
	return uart_control_on;
}

uint8_t menu_get_option_joy(void) {
	return joystick_on;
}