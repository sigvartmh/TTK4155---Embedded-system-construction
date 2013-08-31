#include <avr/io.h>
#include "uart.h"
#include "setup.h"

#define MYUBRR F_OSC/16/BAUD-1

int main(void)
{
	uart_init(MYUBRR);
	DDRB  |= (1<<DDB0);
	
	while(1)
    {
		uart_putchar('U',uart);
		//fprintf(uart, "Hello, World!\n"); 
    }
}
