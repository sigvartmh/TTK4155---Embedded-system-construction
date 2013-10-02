#ifndef MCP2515_H_
#define MCP2515_H_

int mcp2515_init(void);
uint8_t mcp2515_read(uint8_t address);
int mcp2515_write(uint8_t address, uint8_t data);
int mcp2515_request_to_send(uint8_t command);
uint8_t mcp2515_read_status(void);
int mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
int mcp2515_reset(void);

#endif