#include "uart.h"
#include <avr/io.h>

FILE *uart;

int UART_init(unsigned int baudrate) {
	//Set UART0 baud rate
	UBRR0L = (unsigned char)(baudrate);
	UBRR0H = (unsigned char)(baudrate >> 8);
	
	//Enable TX0 and RX0
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	//Set frame format: 8data, 2stop bit
	UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00);
	
	//Connect printf
	uart = fdevopen(&UART_putchar, &UART_recchar);

	return 0;
}

int UART_putchar(char c, FILE *f) {
	//Wait for empty transmit buffer
	while (!(UCSR0A & (1<<UDRE0)));
	
	//Put data into buffer
	UDR0 = c;

	return 0;
}

unsigned char UART_recchar(void) {
	//Wait for data to be received
	while (!(UCSR0A & (1<<RXC0)));
	
	//Return data
	return UDR0;	
}

int UART_print(char * str){
	int i = 0;
	while (str[i] != 0x00){
		UART_putchar(str[i],uart);
		i++;
	}
	return 0;
}
