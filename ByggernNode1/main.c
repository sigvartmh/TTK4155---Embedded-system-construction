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
	message_send.length = 8;
	for(uint8_t i=0;i < message_send.length;i++){
		message_send.data[i] = (uint8_t) 1;
	}
	
	while(1) {
		
		CAN_send_message(&message_send,0);
		printf("Can message with id: %i sent\n\r",message_send.id);
		_delay_ms(1000);
		message_received = CAN_receive_data(&message_receive);
		printf("Can message with id: %i recived\n\r",message_receive.id);
    }
}
