#include "uart.h"
#include <avr/io.h>

FILE *uart;


int UART_init(unsigned int baudrate) {
	//Set UART0 baud rate
	UBRR1L = (unsigned char)(baudrate);
	UBRR1H = (unsigned char)(baudrate >> 8);
	
	//Enable TX0 and RX0
	UCSR1B |= (1<<RXEN1) | (1<<TXEN1);
	
	//Set frame format: 8data, 1stop bit
	UCSR1C |=  (1<<USBS1)| (3<<UCSZ10);
	
	//Connect printf
	uart = fdevopen(&UART_putchar, &UART_recchar);

	return 0;
}

int UART_putchar(char c, FILE *f) {
	//Wait for empty transmit buffer
	while (!(UCSR1A & (1<<UDRE1)));
	
	//Put data into buffer
	UDR1 = c;

	return 0;
}

unsigned char UART_recchar(void) {
	//Wait for data to be received
	while (!(UCSR1A & (1<<RXC1)));
	
	//Return data
	return UDR1;	
}

int UART_print(char * str){
	int i = 0;
	while (str[i] != 0x00){
		UART_putchar(str[i],uart);
		i++;
	}
	return 0;
}
