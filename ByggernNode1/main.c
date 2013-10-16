#include "setup.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "mcp2515.h"
#include "can.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define MYUBRR F_OSC/16/BAUD-1

int main(void) {
	CAN_message_t* message_send;
	CAN_message_t* message_receive;
	int i = 0;
	
	UART_init(MYUBRR);
	printf("Uart initiated\n\r");
	CAN_init();
	printf("CAN initiated\n\r");
	
	message_send->id = 3;
	message_send->length = 1;
	message_send->data[0] = (uint8_t)'U';
	CAN_message_send(&message_send);
	printf("Message sent\n\r");
	
	_delay_ms(100);
	
	message_receive = CAN_data_receive();
	printf("Message id: %i\n\r", message_receive->id);
	printf("Message length: %i\n\r", message_receive->length);
	for(i = 0; i < message_receive->length; i++) {
		printf("Message data: %i\n\r", message_receive->data[i]);
	}
	
	while(1) {

	_delay_ms(100);

    }
}
