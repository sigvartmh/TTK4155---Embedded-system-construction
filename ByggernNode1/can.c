#include <avr/io.h>
#include "mcp2515.h"

typedef struct {
	unsigned int ID;
	uint8_t data[8];
	uint8_t length;
} CAN_message_t;

int CAN_init(void){
	
	mcp2515_inti(void);

	//Enables Loopback mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	//Enable Normal mode
	//mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);

	return 0;
	
}

int CAN_message_send(uint8_t address, CAN_message_t message)
{
	/* Sets the CAN id*/
	//Write the CAN id to the transmit ctrl register
	mcp2515_write(MCP_TXB0CTRL+1,(uint8_t)(message.id>>3));
	mcp2515_write(MCP_TXB0CTRL+2,(uint8_t)(message.id<<5));
	
	//Set max data length to 8 bit
	mcp2515_bit_modify(MCP_TXB0CTRL+5,0x0f,msg->length);

	/* Set CAN data in register */
	//Writes the data to the transmit control register
	uint8_t i;
	for (i = 0; i < msg->length; i++){
		mcp2515_write(MCP_TXB0CTRL+6+i,message.data[i]));
	}
	
	//Sends the command to request a sending operation of the message
	MCP2515_request_to_send(0); // not completely sure if 0 is correct
	
}

CAN_message_t* CAN_data_receive(){
	CAN_message_t* message = malloc(sizeof(CAN_message_t));

	//get message id from recive register
	message->id  = (uint8_t)(mcp2515_read(MCP_RXB0CTRL+1) << 3);
	message->id  = (uint8_t)(mcp2515_read(MCP_RXB0CTRL+2) >> 5);

	//get message length from recive register
	msg->length = (0x0f) & (mcp2515_read(MCP_RXB0CTRL+5));

	//Get message data from recive register
	uint8_t i;
	for(i = 0; i<msg->length; i++){
		msg->data[i] = mcp2515_read(MCP_RXB0CTRL+6+i); //can probably be done differently and better with bit-shifting
	}

	//need some interupt maybe to trigger a recive notification
	//mcp2515_bit_modify(MCP_CANINTF,0x01,0x00);//set INT1

	/*	maybe MCP_TX01_INT is also something to look into */
}

int CAN_error(){}
int CAN_transmit_complete(){}

int CAN_int_vect(){} //can interupt vector
