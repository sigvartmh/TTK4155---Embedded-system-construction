#include <avr/io.h>
#include "mcp2515.h"

typedef struct {
	uint8_t ID;
	int8_t data[8];
	uint8_t length;
} CAN_message_t;

int CAN_init(void){
	
	mcp2515_inti(void);

	//Enables Loopback mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	

	return 0;
	
}

int CAN_send(uint8_t address, CAN_message_t data)
{
	mcp2515_write(address, data.ID);
	
}