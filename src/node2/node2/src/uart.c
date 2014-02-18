#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"
#include "ring_buffer.h"

uint8_t in_buffer[BUFFER_SIZE];
struct ring_buffer rb_out;

FILE *uart;

int UART_init(unsigned int baudrate) {
	//Set UART1 baud rate
	UBRR1L = (unsigned char)(baudrate);
	UBRR1H = (unsigned char)(baudrate >> 8);
	
	//Enable TX1 and RX1
	UCSR1B |= (1<<RXEN1) | (1<<TXEN1);
	
	//Set frame format: 8data, 2stop bit
	UCSR1C |= (1<<USBS1)| (3<<UCSZ10);
	
	rb_out = ring_buffer_init(in_buffer, BUFFER_SIZE); //initialize in buffer
	
	//Connect uart to printf
	uart = fdevopen(&UART_putchar, &UART_recchar);

	return 0;
}

int UART_putchar(char c, FILE *f) {
	  cli();
	  if (ring_buffer_is_empty(&rb_out)) { // checks if the ringbuffer is empty 
		  UCSR1B |= (1 << UDRIE1);
	  }
	  
	  ring_buffer_put(&rb_out, c);
	  
	  sei();
	  return 0;
}

char UART_recchar(void) {
	//Wait for data to be received
	while (!(UCSR1A & (1<<RXC1)));
	
	//Return data
	return(UDR1);	
}


int UART_print(char * str){
	int i = 0;
	while (str[i] != 0x00){
		UART_putchar(str[i],uart);
		i++;
	}
	return 0;
}

ISR (USART1_UDRE_vect)
{
	/* Check if there is data in the buffer and send it */
	if (!ring_buffer_is_empty(&rb_out)) {
		UDR1 = ring_buffer_get(&rb_out);
		} else {
		/* No more data, turn off data ready interrupt */
		UCSR1B &= ~(1 << UDRIE1);
	}
}
