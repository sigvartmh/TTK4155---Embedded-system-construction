void DAC_init()
{
	TWI_Master_Initialise();
	BIT_SET(DDRD, PD0); //SCL
	BIT_SET(DDRD, PD1); //SDA
}

#define SLAVE_ADDR_WRITE 0b01010000

void DAC_write(uint8_t val)
{
	uint8_t* msg = malloc(3*sizeof(uint8_t));
	uint8_t msgSize = 3;
	
	msg[0] = SLAVE_ADDR_WRITE;
	msg[1] = 0;
	msg[2] = val;

	TWI_Start_Transceiver_With_Data(msg, msgSize);
	free(msg);
}