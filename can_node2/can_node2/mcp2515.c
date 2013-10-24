#include <avr/io.h>
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"

uint8_t mcp2515_init(void) {
	volatile uint8_t value;
	
	//Initialize SPI driver
	SPI_init();
	
	//Reset the CAN controller
	mcp2515_reset();
	
	//Self-test
	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in configuration mode after reset!\n\r");
		return 1;
	}
	
	return 0;
}

uint8_t mcp2515_read(uint8_t address) {
	//Select CAN-controller
	SPI_select();
	
	SPI_write(MCP_READ);		//Send read command
	SPI_write(address);			//Send address
	
	uint8_t result = SPI_read();	//Read result
	
	//De-select CAN-controller
	SPI_deselect();
	
	return result;
}

void mcp2515_write(uint8_t address, uint8_t data) {
	//Select CAN-controller
	SPI_select();
		
	SPI_write(MCP_WRITE);	//Send write command
	SPI_write(address);		//Send address
	SPI_write(data);			//Send data
		
	//De-select CAN-controller
	SPI_deselect();
}

void mcp2515_request_to_send(uint8_t command) {
	//Select CAN-controller
	SPI_select();
	
	//Check the last three bits for the commands
	if(command < 8) {
		SPI_write(MCP_RTS | (1<<command));
	} 
	
	//Deselect CAN-controller
	SPI_deselect();	
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	//Select CAN-controller
	SPI_select();
		
	SPI_write(MCP_BITMOD);		//Send bit modify command
	SPI_write(address);			//Send address
	SPI_write(mask);				//Send mask byte
	SPI_write(data);				//Send data
		
	//Deselect CAN-controller
	SPI_deselect();
}

void mcp2515_reset(void) {
	SPI_select();			//Select CAN-controller
	SPI_write(MCP_RESET);	//Send reset command
	SPI_deselect();			//De-select CAN-controller
}



uint8_t mcp2515_read_status(void) {
	//Select CAN-controller
	SPI_select();
	
	SPI_write(MCP_READ_STATUS);	//Send read status command
	uint8_t result = SPI_read();		//Read result
	
	//Deselect CAN-controller
	SPI_deselect();
	
	return result;
}