#include <avr/io.h>
#include "setup.h"
#include "mcp2515.h"
#include "can.h"

#define TXB0CTRL_TXREQ 2
#define TXB1CTRL_TXREQ 4
#define TXB2CTRL_TXREQ 3

uint8_t CAN_init(void) {
	mcp2515_init();
	
	//Enable loop back mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	
	//Enable normal mode
	//mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	
	//is CANINTE.MERRE enabled?
	//Enable interrupt when message is sent (TX0IE = 1) and recived(RX0IE = 1)
	mcp2515_bit_modify(MCP_CANINTE, 0x03, 0x03);
	
	//Set recive all IDs
	mcp2515_bit_modify(MCP_CANCTRL,0b11100000, 0x00);

	return 0;
}

uint8_t CAN_send_message(CAN_message_t* message,uint8_t priority) {
	
	uint8_t status = mcp2515_read_status();
	
	uint8_t can_buffer = 0;
	
	//Check if there is no pending transmission(CAN_transmission_complete can maybe used to this)
	if(!(status&(1<<TXB0CTRL_TXREQ))){
		can_buffer = MCP_TXB0CTRL;
	}else if(!(status&(1<<TXB1CTRL_TXREQ))){
		can_buffer = MCP_TXB1CTRL;
	}else if(!(status&(1<<TXB2CTRL_TXREQ))){
		can_buffer = MCP_TXB2CTRL;
	}else{
		return 1; //return 1 when all the buffers are full
	};
	
	if (priority > 3){
		priority = 3;
		mcp2515_bit_modify(can_buffer,0x03,priority);
	}else if(priority < 0){
		priority = 0;
		mcp2515_bit_modify(can_buffer,0x03,priority);
	}else{
		mcp2515_bit_modify(can_buffer,0x03,priority);
	}
	
	
	mcp2515_write((can_buffer + 0x02),(((uint8_t)(message->id&0x7))<<5)); //Set CAN LO ID (maybe delete MCP_TXB0IDH &LO)
	mcp2515_write((can_buffer + 0x01),(uint8_t)((message->id)>>3) & 0xff); //Set CAN HI ID
	
	//Set data bytes (max. 8 bytes)
	for(uint8_t i = 0; i < message->length; i++){
		mcp2515_write(can_buffer+0x06+i, message->data[i]);
	}
	
	//Set data length and use data frame (RTR = 0)	
	//mcp2515_write(MCP_TXB0DLC, (uint8_t)(message->length << 4));
	mcp2515_write(can_buffer+0x05,(0x0f & message->length));

		
		
	//Request to send via TX0
	if (status)
	{
	}
	
	//mcp2515_write(can_buffer, (1<<3));
	//mcp2515_request_to_send(0)
	mcp2515_request_to_send(1);
	return 0;
}

int CAN_error(void) {
	//TODO
	return 1;
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
	return 0;
}

CAN_message_t* CAN_receive_data(CAN_message_t* message) {
	/*while(1){
		uint8_t status = mcp2515_read_status();
		if(status&((1<<MCP)))
	}*/
	
	uint8_t can_buffer = MCP_RXB0CTRL;
	
	message->length = mcp2515_read(can_buffer+0x05) & 0x0f;
	for (uint8_t i = 0; i <message->length; i++)
	{
		message->data[i] = mcp2515_read(can_buffer+0x06+i);
	}
	
	message->id  = mcp2515_read(can_buffer+0x01); //read CAN HI
	
	//message->id  = (uint8_t)(mcp2515_read(MCP_RXB0SIDH) << 3);
	//message->id  = (uint8_t)(mcp2515_read(MCP_RXB0SIDL) >> 5);
	
	mcp2515_bit_modify(MCP_CANINTF, (1<<0)/*0x01*/,0x00);
	
	return message;
}

ISR(INT0_vect){
	//set interupt vectore value
	return INT0_vect;
}