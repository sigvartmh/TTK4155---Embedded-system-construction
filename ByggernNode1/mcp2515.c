#include <avr/io.h>
#include "spi.h"
#include "mcp2515.h"

//SPI instruction set
#define MCP_RESET 0xC0			//1100 0000
#define MCP_READ 0x03			//0000 0011
#define MCP_WRITE 0x02			//0000 0010
#define MCP_RTS 0x80			//1000 0nnn
#define MCP_READ_STATUS 0xA0	//1010 0000
#define MCP_BIT_MODIFY 0x05		//0000 0101

int mcp2515_init(void) {
	//uint8_t value;
	
	//Initialize SPI driver
	SPI_init();
	
	//Reset the CAN controller
	mcp2515_reset();
	
	//Self-test
	/*mcp2515_read(MCP_CANSTAT, &value);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf(”MCP2515 is NOT in configuration mode
		after reset!\n”);
		return 1;
	}*/
	// More initialization
	
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

int mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	//Select CAN-controller
	SPI_select();
		
	SPI_send(MCP_BIT_MODIFY);	//Send bit modify command
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