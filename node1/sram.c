#include <avr/io.h>
#include <stdio.h>

#define OFFSET 0x1000

void init_SRAM(){
	MCUCR  |= (1<<SRW10) | (1<<SRE); //if we include setup.h we can do set_bit instaed
	EMCUCR |= (1<<SRW00);
	SFIOR  |= (1<<XMM2);
}

void SRAM_test(){
	unsigned int i, werrors, rerrors;
	werrors = 0;
	rerrors = 0;

	unsigned char *ext_ram = (unsigned char *) (OFFSET+1);

	unsigned char testvalue;
	printf("Starting SRAM test...\r\n");
	for (i = 0; i < 0x800; i++) {
		
		testvalue = ~(i % 256);
		ext_ram[i] = testvalue;

		if (ext_ram[i] != testvalue) {
			printf("SRAM error (write phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			werrors++;
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

}