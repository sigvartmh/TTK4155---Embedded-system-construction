#include <avr/io.h>
#include "setup.h"
#include "mcp2515.h"
#include "can.h"

int CAN_init(void) {
	mcp2515_init();
	
	//Enable normal mode
	//mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	
	//Enable loop back mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	
	//Enable interrupt when message is sent (TX0IE = 1)
	mcp2515_bit_modify(MCP_CANINTE, 0x04, 1);
	
	//Enable interrupt when message is received (RX0IE = 1)
	mcp2515_bit_modify(MCP_CANINTE, 0x01, 1);

	return 0;
}

int CAN_message_send(CAN_message_t* message) {
	uint8_t i;
	
	//Check if there is no pending transmission
	if (CAN_transmit_complete()) {
		
		//Set transmit priority (0 - lowest)
		mcp2515_bit_modify(MCP_TXB0CTRL, 0x03, 0);
		
		//Set the message id (use standard identifier)
		mcp2515_write(MCP_TXB0SIDH, (uint8_t)(message->id >> 3));
		mcp2515_write(MCP_TXB0SIDL, (uint8_t)(message->id << 5));
		
		//Set data length and use data frame (RTR = 0)
		mcp2515_write(MCP_TXB0DLC, (uint8_t)(message->length << 4));

		//Set data bytes (max. 8 bytes)
		for (i = 0; i < message->length; i++) {
			mcp2515_write(MCP_TXB0D0 + i, message->data[i]);
		}
		
		//Request to send via TX0
		mcp2515_request_to_send(1);
		
	} else {
		//TODO: Check why is there a pending transmission
	}
	
	return 0;
}

int CAN_error(void) {
	//TODO
}


int CAN_transmit_complete(void) {
	//Check if TX buffer is not pending transmission (TXREQ = 0)
	if (test_bit(mcp2515_read(MCP_TXB0CTRL), 3)) {
		return 0;
	} else {
		return 1;
	}
}

int CAN_int_vect(void) {
	//TODO
}

CAN_message_t* CAN_data_receive(void) {
	uint8_t i;
	CAN_message_t* message = malloc(sizeof(CAN_message_t));
	
	//Get message id
	message->id  = (mcp2515_read(MCP_RXB0SIDH) << 3) && (mcp2515_read(MCP_RXB0SIDL) >> 5);
	//message->id  = (uint8_t)(mcp2515_read(MCP_RXB0SIDH) << 3);
	//message->id  = (uint8_t)(mcp2515_read(MCP_RXB0SIDL) >> 5);
	
	//Get message length
	message->length = (0x0F) & (mcp2515_read(MCP_RXB0DLC));
	
	//Get message data
	for(i = 0; i < message->length; i++) {
		message->data[i] = mcp2515_read(MCP_RXB0D0 + i);
	}
	
	return message;
}

//uint8_t int_vector;
	//
//int_vector = mcp2515_read(MCP_CANINTF);
	//
////TX0 interrupt
//if (test_bit(int_vector, 2)) {
		//
	//mcp2515_bit_modify(MCP_CANINTF, 0x04, 0);
//}
////RX0 interrupt
//if (test_bit(int_vector, 0)) {
	////read data
	//mcp2515_bit_modify(MCP_CANINTF, 0x01, 0);
//}