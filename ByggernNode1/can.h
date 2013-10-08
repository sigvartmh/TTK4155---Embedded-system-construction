#pragma once

typedef struct {
	unsigned int ID;
	uint8_t data[8];
	uint8_t length;
} CAN_message_t;

CAN_message_t* CAN_data_receive();

int CAN_init(void);
int CAN_message_send(uint8_t address, CAN_message_t message);
int CAN_error();
int CAN_transmit_complete();
int CAN_int_vect();