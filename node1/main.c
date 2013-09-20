#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "joystick.h"
#define MYUBRR F_OSC/16/BAUD-1


int main(void) {
	/*TEST UART*/
	UART_init(MYUBRR);
=======
//change on git

int main(void)
{
	uart_init(MYUBRR);
	
	//PORTE |= (1<<PE1);
	//DDRB  |= (1<<DDB0);
	
	DDRA  |= (1<<PA0);
	DDRE  |= (1<<PE1);
	
	set_bit(PORTE,PE1);
	_delay_ms(1000);
	set_bit(PORTA,PA0);
	_delay_ms(1000);
	
	clear_bit(PORTA,PA0);
	_delay_ms(1000);
	clear_bit(PORTE,PE1);
	
>>>>>>> b3e41569554b479095cc682706680dc357b2518b
	char c;
	
	/*TEST SRAM*/
	/*SRAM_init();
	SRAM_test();
	SRAM_write(0x0000, 0xAB);
	printf("\n");*/
	
	/*TEST ADC*/
	//ADC_init();
	//uint8_t adc_data;
	
	/*TEST JOYSTICK*/
	JOY_init();
	joy_position joy_pos;
	slider_position slider_pos;
	
	while(1) {
		printf("Button = %i\n\r", JOY_button(0));
		printf("Slider Button L= %i\n\r", JOY_button(1));
		printf("Slider Button R = %i\n\r", JOY_button(2));

		joy_pos = JOY_getPosition();
		printf("X: %i%%   Y: %i%%\n\r", joy_pos.x, joy_pos.y);
		
		joy_pos = JOY_getDirection();
		printf("Direction: %s\n\r", joy_pos.direction);
		
		slider_pos = JOY_getSliderPosition();
		printf("Slider Left = %i%% \n\r", slider_pos.left);
		printf("Slider Right = %i%% \n\r", slider_pos.right);
		
		printf("\n");
		_delay_ms(500);
    }
}
