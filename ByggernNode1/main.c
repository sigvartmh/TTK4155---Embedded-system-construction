#include "setup.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "joystick.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "mcp2515.h"
#include "can.h"

//#include "can.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define MYUBRR F_OSC/16/BAUD-1

int main(void) {
	
	/*TEST MCP2515*/
	mcp2515_init();
	
	
	while(1) {
	mcp2515_write(MCP_CANSTAT,0xff);
	_delay_ms(10);
	mcp2515_read(MCP_CANSTAT);
		
		
    }
}
