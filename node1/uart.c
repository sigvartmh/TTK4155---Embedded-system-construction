#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

FILE *uart;

uint8_t uart_init(unsigned int baudrate){

	UBRR0L = (unsigned char) (baudrate);
	UBRR0H = (unsigned char) (baudrate >> 8);
	
	//enable tx0 and rx0
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	//set 8bit mode
	UCSR0C = (1<<URSEL0)|(1<<UCSZ00)|(3<<UCSZ01);//UCSR0C &= ~(3<<UCSZ01)
	
	uart = fdevopen(&uart_putchar, &uart_recchar);
	//(connecting printf)

	return 0;
}

uint8_t uart_putchar(char c, FILE *f){
	PORTB |=(1<<PB0);
	//_delay_ms(650);
	while (!( UCSR0A & (1<<UDRE0))); // (wait for UDR to be ready)
	UDR0 = c;
	PORTB &= ~(1<<PB0); // blinking led for transmitted char
	//_delay_ms(650);
	return 0;
}

unsigned char uart_recchar(){
	while (!(UCSR0A & (1<<RXC0))); //wait for data to be recived and udr to be ready
	return UDR0;	
};

void uart_print(char * str){
	int i = 0;
	while (str[i] != 0x00){
		uart_putchar(str[i],uart);
		i++;
	}
}
