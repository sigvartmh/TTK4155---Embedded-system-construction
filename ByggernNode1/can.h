#ifndef CAN_H_
#define CAN_H_

typedef struct {
	uint16_t id;
	uint8_t length;
	uint8_t data[8];
} CAN_message_t;

uint8_t CAN_init(void);
uint8_t CAN_send_message(CAN_message_t* message,uint8_t priority);
int CAN_error(void);
int CAN_transmit_complete(void);
int CAN_int_vect(void);
CAN_message_t* CAN_receive_data(CAN_message_t* message);

#endif