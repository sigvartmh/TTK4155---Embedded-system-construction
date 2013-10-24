#include "setup.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "oled.h"
#include "menu.h"
#include "mcp2515.h"
#include "can.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


//retardness
#include <stdlib.h>
//end retard

#define MYUBRR F_OSC/16/BAUD-1

int main(void) {
	CAN_message_t message_send;
	CAN_message_t message_receive;
	CAN_message_t* message_received = malloc(sizeof(CAN_message_t));
	
	UART_init(MYUBRR);
	printf("Uart initiated\n\r");
	CAN_init();
	printf("CAN initiated\n\r");
	
	message_send.id = 3;
	message_send.length = 1;
	message_send.data[0] = (uint8_t) 1;
	CAN_send_message(&message_send,0);
	printf("Message sent\n\r");
	
	_delay_ms(100);
	
	message_received = CAN_receive_data(&message_receive);
	printf("Message id: %i\n\r", message_receive.id);
	printf("Message length: %i\n\r", message_receive.length);
	for(int i = 0; i < message_receive.length; i++) {
		printf("Message data: %i\n\r", message_receive.data[i]);
	}
	printf("Message id: %i\n\r", message_received->id);
	
	while(1) {

	_delay_ms(100);

    }
}
