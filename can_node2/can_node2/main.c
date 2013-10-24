#include "uart.h"
#include "setup.h"
#include "can.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define MYUBRR F_OSC/16UL/BAUD-1

int main(void)
{
	UART_init(MYUBRR);
	printf("Uart initiated\n\r");
	CAN_init();
	printf("Can initiated\n\r");
	
	CAN_message_t message_send;
	CAN_message_t message_receive;
	message_receive.id = 0;
	message_receive.length = 0;
	for(int i = 0; i < 8; i++) {
		message_receive.data[i]=0;
	}
	CAN_message_t* message_received = malloc(sizeof(CAN_message_t));
	
	message_send.id = 24;
	message_send.length = 7;
	for(uint8_t i; i < message_send.length;i++){
	message_send.data[i] = (uint8_t) 1;
	}	
	
	
	_delay_ms(100);
	
	
	for(int i = 0; i < message_receive.length; i++) {
		 printf("%i", message_receive.data[i]);
	}
	printf("\n\r");
	
    while(1)
    {
		_delay_ms(1000);
		CAN_send_message(&message_send,0);
		printf("Message sent\n\r");
		_delay_ms(1000);
		CAN_receive_data(&message_receive);
		printf("Recived message: \n\r");
		printf("Message id: %i\n\r", message_receive.id);
		printf("Message length: %i\n\r", message_receive.length);
		printf("Message data: ");
    }
}