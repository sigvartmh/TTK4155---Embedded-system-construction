#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#include "uart.h"
#include "sram.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "can.h"
#include "buzzer.h"
#include "eeprom.h"

int main(void) {
	/*-----Define pins-----*/
	DDRD &= ~(1 << PIND2);		//Set D2(INT0) as input
	DDRD |= (1 << PIND5);		//Set D5(OC1A) as output
	
	/*-----Define variables-----*/
	struct screen *display_screen;
	char *prev_screen = " ";
	char *joy_direction = " ";
	CAN_message_t can_msg_send;
	CAN_message_t can_msg_receive;
	joy_position joy_pos;
	slider_position slider_pos;
	int8_t score = 0;
	uint8_t lives = 3;
	int button_pressed = 0;
	int prev_button = 0;
	
	/*-----Interrupts-----*/
	GICR |= (1 << INT0);		//Enable INT0
	MCUCR |= (1<<ISC01);		//Trigger on falling edge
	MCUCR &= ~(1<<ISC00);		//Trigger on falling edge
	
	/*-----Initialize UART-----*/
	UART_init(MYUBRR);
	printf("----UART working----\n\r");
	
	/*-----Initialize SRAM-----*/
	SRAM_init();
	SRAM_test();
	
	/*-----Initialize JOYSTICK-----*/
	if (JOY_init() == 0) {
		printf("----Joystick working----\n\r");
	} else {
		printf("----Joystick error!!----\n\r");
	}
	
	/*-----Initialize OLED-----*/
	OLED_init();
	OLED_sram_clear();
	OLED_sram_draw_mario();
	OLED_pos(1, 5);
	OLED_sram_print("Ping Pong");
	OLED_pos(3, 4);
	OLED_sram_print("Press Button");
	OLED_pos(4, 5);
	OLED_sram_print("to start");
	display_screen = init_menu();

	/*-----Initialize CAN-----*/
	if (CAN_init() == 0) {
		printf("----CAN working----\n\r");
		can_msg_send.id = 1;
		can_msg_send.length = 6;
	} else {
		printf("----CAN error!!----\n\r");
	}
	
	/*-----Initialize Buzzer-----*/
	BUZZER_init();
	
	//Erase EEPROM
	EEPROM_write(0,0);
	EEPROM_write(1,0);
	EEPROM_write(2,0);
	EEPROM_write(3,0);
	EEPROM_write(4,0);	
	
	//Enable global interrupts
	sei();
	
	while(1) {
		
		//------------Menu------------//
		if (display_screen->game_on == 0) {

			//Get joystick position
			joy_pos = JOY_getDirection();
					
			if (strcmp(joy_pos.direction,"UP") == 0) {
				joy_direction = "UP";
				//Avoid changing selection too fast
				_delay_ms(300);
			} else if (strcmp(joy_pos.direction,"DOWN") == 0) {
				joy_direction = "DOWN";
				//Avoid changing selection too fast
				_delay_ms(300);
			} else if (strcmp(joy_pos.direction,"LEFT") == 0) {
				joy_direction = "LEFT";
				//Avoid changing selection too fast
				_delay_ms(300);
			} else if (strcmp(joy_pos.direction,"RIGHT") == 0) {
				joy_direction = "RIGHT";
				//Avoid changing selection too fast
				_delay_ms(300);
			} else {
				joy_direction = " ";
			}
			
			//Check for option selected
			if (JOY_button(0) == 1) {		
				//Remove bouncing
				while (JOY_button(0) == 1);
				
				if (display_screen->child_selected >= 0) {
					if (display_screen->child[display_screen->child_selected] != NULL) {
						display_screen = display_screen->child[display_screen->child_selected];
					}
				} else {
					display_screen = display_screen->parent;
				}
				
				//Change song depending on screen
				if ((strcmp(display_screen->name,"main") == 0) && (strcmp(prev_screen,"options") != 0))
					BUZZER_play_song(display_screen->name);
				else if (strcmp(display_screen->name,"game") == 0)
					BUZZER_play_song(display_screen->name);
					
				prev_screen = display_screen->name;
			}
						
		//------------Game------------//
		} else {
			//Get the info of the game
			can_msg_receive = CAN_data_receive();
			if (can_msg_receive.id == 2 && can_msg_receive.length == 2) {
				lives = can_msg_receive.data[0];
				score = can_msg_receive.data[1];
			}
			
			//Send the joystick position to node 2
			joy_pos = JOY_getPosition();
			can_msg_send.data[0] = joy_pos.x;
			
			//Send the slider position to node 2
			slider_pos = JOY_getSliderPosition();
			can_msg_send.data[1] = slider_pos.right;
			
			//Send the button click to node 2
			button_pressed = JOY_button(0);
			if ((button_pressed == 1) && (button_pressed != prev_button)) {
				can_msg_send.data[2] = 1;
			} else {
				can_msg_send.data[2] = 0;
			}
			prev_button = button_pressed;
			
			//Send the status of the game (playing)
			can_msg_send.data[3] = 1;
			
			//Send the mode playing (board/web)
			can_msg_send.data[4] = menu_get_option_uart();
			
			//Send the joystick controlling servo/speed
			can_msg_send.data[5] = menu_get_option_joy();
			
			CAN_message_send(&can_msg_send);
			
			//End game
			if (lives == 0) {
				//Tell node 2 game is over
				can_msg_send.data[3] = 0;
				CAN_message_send(&can_msg_send);
				
				//Save score in EEPROM
				EEPROM_save_score(score);
				
				//Return to high scores screen
				display_screen = display_screen->parent;
				
				//Play game over song
				BUZZER_play_song("gameover");
				_delay_ms(6000);
				BUZZER_play_song("none");
				
				lives = 3;
				score = 0;
			}
		}
		
		//Refresh the screen
		draw_screen(display_screen, joy_direction, lives, score);
		OLED_refresh();
		
    }
}
