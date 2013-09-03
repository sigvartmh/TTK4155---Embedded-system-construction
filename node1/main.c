#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "setup.h"

#define MYUBRR F_OSC/16/BAUD-1

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
	
	char c;

	while(1)
    {
		
	
		//uart_putchar('U',uart);
		//fprintf(uart,"Hello, World!\n");
		//printf("Hello, World!\n\r");
		c = uart_recchar();
		printf("%c\n\r",c);
    }
	
	
}
