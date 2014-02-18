#include <avr/io.h>
#include <stdio.h>

int SRAM_init(void) {
	//Enable the external memory interface/4 bits address
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	return 0;
}

int SRAM_write(unsigned int address, unsigned int data) {
	//Start address for the SRAM
	volatile char *ext_ram = (char *) 0x1800;

	//Write address on SRAM
	ext_ram[address] = data;
	
	return 0;
}

unsigned int SRAM_read(unsigned int address) {
	//Start address for the SRAM
	volatile char *ext_ram = (char *) 0x1800;
	
	//Read address from SRAM
	return ext_ram[address];
}

void SRAM_test(void) {
	//Start address for the SRAM
	volatile char *ext_ram = (char *) 0x1800;

	uint16_t i, werrors, rerrors;
	werrors = 0;
	rerrors = 0;
	unsigned char testvalue;

	printf("Starting SRAM test...\r\n");

	for (i = 0; i < 0x800; i++) {
		testvalue = ~(i % 256);
		ext_ram[i] = testvalue;
		if (ext_ram[i] != testvalue) {
			printf("SRAM error (write phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			werrors++;
		}
	}

	for (i = 0; i < 0x800; i++) {
		testvalue = ~(i % 256);
		if (ext_ram[i] != testvalue) {
			printf("SRAM error (read phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			rerrors++;
		}
	}

	printf("SRAM test completed with %d errors in write phase and %d errors in read phase\r\n", werrors, rerrors);
}