#ifndef MCP2515_H_
#define MCP2515_H_

//SPI instruction set
#define MCP_RESET 0xC0			//1100 0000
#define MCP_READ 0x03			//0000 0011
#define MCP_WRITE 0x02			//0000 0010
#define MCP_RTS 0x80			//1000 0nnn
#define MCP_READ_STATUS 0xA0	//1010 0000
#define MCP_BIT_MODIFY 0x05		//0000 0101


int mcp2515_init(void);
int mcp2515_write(uint8_t address, uint8_t data);
int mcp2515_request_to_send(uint8_t command);
int mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
int mcp2515_reset(void);

uint8_t mcp2515_read(uint8_t address);
uint8_t mcp2515_read_status(void);

#endif