#include <avr/io.h>
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"

int mcp2515_init(void) {
	volatile uint8_t value;
	
	//Initialize SPI driver
	SPI_init();
	
	//Reset the CAN controller
	mcp2515_reset();
	
	//Self-test
	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		UART_print("MCP2515 is NOT in configuration mode after reset!");
		return 1;
	}
	
	return 0;
}

int mcp2515_write(uint8_t address, uint8_t data) {
	//Select CAN-controller
	SPI_select();
		
	SPI_send(MCP_WRITE);	//Send write command
	SPI_send(address);		//Send address
	SPI_send(data);			//Send data
		
	//Deselect CAN-controller
	SPI_deselect();
		
	return 0;
}

int mcp2515_request_to_send(uint8_t command) {
	/*	
	#define MCP_RTS_TX0		0x81 -> command = 1
	#define MCP_RTS_TX1		0x82 -> command = 2
	#define MCP_RTS_TX2		0x84 -> command = 4
	#define MCP_RTS_ALL		0x87 -> command = 7
	*/

	//Check the last three bits for the commands
	if(command <= 7) {
		command = MCP_RTS | command;
	} else {
		command = MCP_RTS;
	}
	
	//Select CAN-controller
	SPI_select();
		
	SPI_send(command);		//Send RTS command
		
	//Deselect CAN-controller
	SPI_deselect();
		
	return 0;
}

int mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	//Select CAN-controller
	SPI_select();
		
	SPI_send(MCP_BITMOD);		//Send bit modify command
	SPI_send(address);			//Send address
	SPI_send(mask);				//Send mask byte
	SPI_send(data);				//Send data
		
	//Deselect CAN-controller
	SPI_deselect();
		
	return 0;
}

int mcp2515_reset(void) {
	//Select CAN-controller
	SPI_select();
	
	SPI_send(MCP_RESET);	//Send reset command
	
	//Deselect CAN-controller
	SPI_deselect();
	
	return 0;
}

uint8_t mcp2515_read(uint8_t address) {
	uint8_t result;

	//Select CAN-controller
	SPI_select();
	
	SPI_send(MCP_READ);		//Send read command
	SPI_send(address);		//Send address
	result = SPI_read();	//Read result
	
	//Deselect CAN-controller
	SPI_deselect();
	
	return result;
}

uint8_t mcp2515_read_status(void) {
	uint8_t result;

	//Select CAN-controller
	SPI_select();
	
	SPI_send(MCP_READ_STATUS);	//Send read status command
	result = SPI_read();		//Read result
	
	//Deselect CAN-controller
	SPI_deselect();
	
	return result;
}