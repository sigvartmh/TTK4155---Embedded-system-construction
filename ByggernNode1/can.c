#include <avr/io.h>
#include "mcp2515.h"

typedef struct can_message{
	uint32_t ID;
	uint8_t data;
	uint8_t length;
};

int CAN_init(void){
	
	//mcp2515_write(CANCTRL,MODE_LOOPBACK);
	return 0;
	
}