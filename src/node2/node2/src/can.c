#include "setup.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "mcp2515.h"
#include "can.h"

uint8_t rx_flag = 0;

int CAN_init(void) {
	//Enter config mode
	mcp2515_init();
			
	//RX0 - Turn masks/filters off, rollover disabled
	mcp2515_bit_modify(MCP_RXB0CTRL, 0b01100100, 0xFF);
	
	//Enable normal mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

	return 0;
}

int CAN_message_send(CAN_message_t* message) {
	uint8_t i;
	
	//Check if there is no pending transmission
	if (CAN_transmit_complete()) {
		
		//Set the message id (use standard identifier)
		mcp2515_write(MCP_TXB0SIDH, (int8_t)(message->id >> 3));
		mcp2515_write(MCP_TXB0SIDL, (int8_t)(message->id << 5));
		
		//Set data length and use data frame (RTR = 0)
		mcp2515_write(MCP_TXB0DLC, (0x0F) & (message->length));

		//Set data bytes (max. 8 bytes)
		for (i = 0; i < message->length; i++) {
			mcp2515_write(MCP_TXB0D0 + i, message->data[i]);
		}
		
		//Request to send via TX0
		mcp2515_request_to_send(1);
		
	} else {
		if (CAN_error() < 0) {
			return -1;
		}
	}
	
	return 0;
}

int CAN_error(void) {
	uint8_t error = mcp2515_read(MCP_TXB0CTRL);
	
	//Transmission error detected
	if (test_bit(error, 4)) return -1;
	
	//Message lost arbitration
	if (test_bit(error, 5)) return -2;
	
	return 0;
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
	//Clear interrupt flag
	mcp2515_bit_modify(MCP_CANINTF, 0x01, 0);
	rx_flag = 1;

	return 0;
}

CAN_message_t CAN_data_receive(void) {
	uint8_t i;
	CAN_message_t message;
	
	//Check if RX buffer has a message
	if (test_bit(mcp2515_read(MCP_CANINTF), 0)) {
		
		//Get message id
		message.id  = (mcp2515_read(MCP_RXB0SIDH) << 3) | (mcp2515_read(MCP_RXB0SIDL) >> 5);
	
		//Get message length
		message.length = (0x0F) & (mcp2515_read(MCP_RXB0DLC));
	
		//Get message data
		for(i = 0; i < message.length; i++) {
			message.data[i] = mcp2515_read(MCP_RXB0D0 + i);
		}
		
		//Clear interrupt flag
		mcp2515_bit_modify(MCP_CANINTF, 0x01, 0);
		
	} else {
		//Message not received
		message.id = -1;
	}
	
	return message;
}