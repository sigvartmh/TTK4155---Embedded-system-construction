/*
 * control_driver.h
 *
 * Created: 05/11/2013 17:44:32
 *  Author: Sigvart
 */ 


#ifndef CONTROL_DRIVER_H_
#define CONTROL_DRIVER_H_

void control_init();
void control_set_speed(int value);
int16_t read_encoder();
int get_maxvalue();


#endif /* CONTROL_DRIVER_H_ */