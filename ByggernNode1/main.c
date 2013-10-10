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

//#include "can.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define MYUBRR F_OSC/16/BAUD-1

int main(void) {
	/*UART_init(MYUBRR);
	CAN_message_t *recived;
	CAN_message_t message;
	message.id='H';
	message.data[0] = 'W';
	message.length = 8;
	*/
	CAN_message_t message;
	CAN_message_t *recived;
	CAN_init();
	recived = malloc(sizeof(CAN_message_t));
	
	message.id = 'c';
	for(int i; i<8;i++){
		message.data[i]=1;
	}
	message.length = 8;
	//uint8_t recived;
	CAN_init();
	
	UART_init(MYUBRR);
	UART_print("Uart initiated\n\r");
	while(1) {
		recived = mcp2515_read(MCP_CANSTAT);
		
		CAN_message_send(1,message); //RTS send all
		recived = CAN_data_receive();
		for(int i = 0; i<recived->length;i++){
			_delay_ms(10);
			UART_print(recived->data[i]);
			UART_print("\r\n");
			_delay_ms(10);
		}
		_delay_ms(200);
		/*UART_putchar(recived,0);
		UART_print("\n\r");
		
		//set up interupt so you know if there is a message recived
		//
*/

    }
}
