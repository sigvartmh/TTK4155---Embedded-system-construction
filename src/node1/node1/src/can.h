#ifndef CAN_H_
#define CAN_H_

uint8_t rx_flag;

typedef struct {
	int id;
	uint8_t length;
	int8_t data[8];
} CAN_message_t;

int CAN_init(void);
int CAN_message_send(CAN_message_t* message);
int CAN_error(void);
int CAN_transmit_complete(void);
int CAN_int_vect(void);
CAN_message_t CAN_data_receive(void);

#endif