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
	//mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	
	//Enable normal mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	
	//is CANINTE.MERRE enabled?
	//Enable interrupt when message is sent (TX0IE = 1) and recived(RX0IE = 1)
	mcp2515_bit_modify(MCP_CANINTE, 0x03, 0x03);
	
	//Set recive all IDs
	//mcp2515_bit_modify(MCP_CANCTRL,0b11100000, 0x00);

	return 0;
}

uint8_t CAN_transmit_complete(void) {
	uint8_t status = mcp2515_read_status();
	
	if(!(status&(1<<TXB0CTRL_TXREQ))){
		return MCP_TXB0CTRL;
	}else if(!(status&(1<<TXB1CTRL_TXREQ))){
		return MCP_TXB1CTRL;
	}else if(!(status&(1<<TXB2CTRL_TXREQ))){
		return MCP_TXB2CTRL;
	}else{
		return 0; //return 1 when all the buffers are full
	}
}

void CAN_set_priority(uint8_t can_buffer, uint8_t priority){
	if (priority > 3){
		priority = 3;
		mcp2515_bit_modify(can_buffer,0x03,priority);
	}else if(priority < 0){
		priority = 0;
		mcp2515_bit_modify(can_buffer,0x03,priority);
	}else{
		mcp2515_bit_modify(can_buffer,0x03,priority);
	}
}

uint8_t CAN_send_message(CAN_message_t* message,uint8_t priority) {
	uint8_t can_buffer = 0;
	while(can_buffer == 0){
		can_buffer = CAN_transmit_complete();
	}
	
	CAN_set_priority(can_buffer, priority);
	
	mcp2515_write((can_buffer + 0x01),(uint8_t)(message->id>>3));
	mcp2515_write((can_buffer + 0x02),(uint8_t)(message->id<<5));
	
	//Set data bytes (max. 8 bytes)
	for(uint8_t i = 0; i < message->length; i++){
		mcp2515_write(can_buffer+0x06+i, message->data[i]);
	}
	
	//Set data length and use data frame (RTR = 0)	
	mcp2515_write(can_buffer+0x05,( message->length));
	mcp2515_request_to_send(0);
	
	return 0;
}

int CAN_error(void) {
	//TODO
	return 1;
}

uint8_t CAN_select_recivebuffer(){
	
	if(mcp2515_read(MCP_CANINTF)&MCP_RX0IF){
		return MCP_RXB0CTRL;
	}else if(mcp2515_read(MCP_CANINTF)&MCP_RX1IF){
		return MCP_RXB1CTRL;
	}else{
		return 0;
	}
}


CAN_message_t* CAN_receive_data(CAN_message_t* message) {
	/*while(1){
		uint8_t status = mcp2515_read_status();
		if(status&((1<<MCP)))
	}*/
	uint8_t can_buffer = 0;
	can_buffer = CAN_select_recivebuffer();
	
	if(can_buffer=0){
		return 0;
	}
	
	message->length = mcp2515_read(can_buffer+0x05);
	for (uint8_t i = 0; i < message->length; i++)
	{
		message->data[i] = mcp2515_read(can_buffer+0x06+i);
	}
	
	message->id  = mcp2515_read(can_buffer+0x02)>>5; //read CAN HI
	
	mcp2515_bit_modify(MCP_CANINTF, (1<<0)/*0x01*/,0x00);
	
	return message;
}

int CAN_int_vect(void) {
	//TODO
	return 0;
}

ISR(INT0_vect){
	//set interupt vectore value
	return INT0_vect;
}