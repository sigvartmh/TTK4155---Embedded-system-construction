#include "setup.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include <avr/io.h>
#include <util/delay.h>

#define MYUBRR F_OSC/16/BAUD-1

int main(void) {
	/*TEST UART*/
	/*UART_init(MYUBRR);
	char c;*/
	
	/*TEST SRAM*/
	/*SRAM_init();
	SRAM_test();
	SRAM_write(0x0000, 0xAB);
	printf("\n");*/
	
	/*TEST ADC*/
	/*ADC_init();
	uint8_t adc_data;*/
	
	/*TEST JOYSTICK*/
	/*JOY_init();
	joy_position joy_pos;
	slider_position slider_pos;*/

	/*TEST OLED*/
OLED_init();
draw_menu();


/*

OLED_goto_line(3);
OLED_print("h3");
OLED_goto_line(0);
OLED_print("h1");*/


int i = 0;
	while(1) {
		/*printf("Button = %i\n\r", JOY_button(0));
		printf("Slider Button L = %i\n\r", JOY_button(1));
		printf("Slider Button R = %i\n\r", JOY_button(2));

		joy_pos = JOY_getPosition();
		printf("Position X: %i%%\n\r", joy_pos.x);
		printf("Position Y: %i%%\n\r", joy_pos.y);

		slider_pos = JOY_getSliderPosition();
		printf("Slider L = %i\n\r", slider_pos.left);
		printf("Slider R = %i\n\r", slider_pos.right);*/
		
		/* OLED test*/
		/*_delay_ms(1000);
		OLED_goto_line(4);
		OLED_print("Hi there");
		_delay_ms(1000);
		OLED_clear_line(4);
		*/
		
    }
}
