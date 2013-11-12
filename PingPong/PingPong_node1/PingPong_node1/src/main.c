#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#include "uart.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "can.h"

int main(void) {
	/*-----Define pins-----*/
	DDRD &= ~(1 << PIND2);		//Set D2(INT0) as input
	
	/*-----Define variables-----*/
	CAN_message_t can_msg_send;
	CAN_message_t can_msg_receive;
	uint8_t menu_display = 0;		//0=main menu, 1=start, 2=high scores
	uint8_t menu_item_selected = 0;
	uint8_t game_state = 1;			//1=animation, 2=menu, 3=play
	int circle_inc = 2;				//min radius
	int circle_dec = 7;				//max radius
	joy_position joy_pos;
	slider_position slider_pos;
	//slider_position slider_pos;
	uint8_t score = 0;
	
	/*-----Interrupts-----*/
	GICR |= (1 << INT0);		//Enable INT0
	MCUCR |= (1<<ISC01);		//Trigger on falling edge
	MCUCR &= ~(1<<ISC00);		//Trigger on falling edge
	
	/*-----Initialize UART-----*/
	UART_init(MYUBRR);
	printf("----UART working----\n\r");
	
	/*-----Initialize JOYSTICK-----*/
	if (JOY_init() == 0) {
		printf("----Joystick working----\n\r");
	} else {
		printf("----Joystick error!!----\n\r");
	}
	
	/*-----Initialize OLED-----*/
	OLED_init();
	OLED_clear();
	OLED_draw_mario();
	OLED_pos(1, 5);
	OLED_print("Ping Pong");
	OLED_pos(3, 5);
	OLED_print("Press Button");
	OLED_pos(4, 5);
	OLED_print("to start");

	/*-----Initialize CAN-----*/
	if (CAN_init() == 0) {
		printf("----CAN working----\n\r");
		can_msg_send.id = 1;
		can_msg_send.length = 3;
	} else {
		printf("----CAN error!!----\n\r");
	}
	
	//Configure menu
	init_menu();
	
	//Enable global interrupts
	sei();
	
	while(1) {

		_delay_ms(100);
		
		if (JOY_button(0) == 1) {
			switch (game_state) {
				case 1:
					game_state = 2;
					break;
				case 2:
					//Main Menu
					if (menu_display == 0) {
						//Selected Start
						if (menu_item_selected == 1) {
							menu_display = 1;
							game_state = 3;
						//Selected High Scores
						} else if (menu_item_selected == 2) {
							menu_display = 2;
						}
						//High Scores Menu
					} else if (menu_display == 2) {
						//Selected Return
						if (menu_item_selected == 1) {
							menu_display = 0;
						}
					}
					break;
				default:
					break;
			}
			//Remove bouncing
			while (JOY_button(0) == 1);
		}
		
		switch (game_state) {
			case 1:
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
				
				break;
			case 2:
				//Menu interface
				OLED_clear();
				joy_pos = JOY_getDirection();
				
				if (strcmp(joy_pos.direction,"UP") == 0) {
					menu_item_selected = draw_menu(menu_display, 1);
					//Avoid changing selection too fast
					_delay_ms(500);
				} else if (strcmp(joy_pos.direction,"DOWN") == 0) {
					menu_item_selected = draw_menu(menu_display, 2);
					//Avoid changing selection too fast
					_delay_ms(500);
				} else {
					menu_item_selected = draw_menu(menu_display, 0);
				}
				
				break;
			case 3:
				//Start game
				OLED_clear();
				
				//Get the score of the game
				can_msg_receive = CAN_data_receive();
				if (can_msg_receive.id == 2) {
					score = can_msg_receive.data[0];
					printf("Score %i",score); //testing
				}
				
				OLED_print("Score: ");
				OLED_print_char(score+0x30);
				
				//Send the joystick position to node 2
				joy_pos = JOY_getPosition();
				can_msg_send.data[0] = joy_pos.x;
				
				//Send the slider position to node 2
				slider_pos = JOY_getSliderPosition();
				can_msg_send.data[1] = slider_pos.right;
				
				//Send the button click to node 2
				can_msg_send.data[2] = JOY_button(0);
				
				CAN_message_send(&can_msg_send);
				
				//End game
				if (score == 5) game_state = 1;
			default:
				break;
		}
    }
}
