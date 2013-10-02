#include "SPIdriver.h"

#define MCP_READ 0x03

uint8_t mcp2515_read_register(const uint8_t address){
	
	uint8_t result;

	SPI_selected();
	SPI_transmit(MCP_READ);
	SPI_transmit(address);
	result = SPI_recive();
	SPI_deselect();
}