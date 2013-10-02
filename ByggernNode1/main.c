#include "setup.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "mcp2515.h"
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
	joy_position joy_pos;*/
	//slider_position slider_pos;

	/*TEST OLED*/
	/*OLED_init();
	draw_menu();
	int pos = 0;
	int dir = 0;*/
	
	/*TEST SPI*/
	SPI_init();
	
	while(1) {
		/*joy_pos = JOY_getDirection();
		dir = joy_pos.dir;
		_delay_ms(200); 
		pos = main_menu(dir,pos,JOY_button(0));*/
		
		SPI_select();
		SPI_send('b');
		SPI_deselect();
		_delay_ms(1);
    }
}
