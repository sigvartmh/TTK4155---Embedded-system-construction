#ifndef CONTROL_DRIVER_H_
#define CONTROL_DRIVER_H_

//Output saturation
#define MAX  200                  
#define MIN -200

int get_maxvalue();

/*Initialize control*/
void control_init();

void control_set_reference(uint8_t value);
void control_encoder_calibrate();
void control_speed_reg(int speed);


void inti_clock();
int get_timer_value(void);
//timer functions for score keeping
void control_set_timer_flag(int flag);
void control_reset_timer();

//Gives out a 16bit number from the encoder
int16_t read_encoder();

//Resets the integral summed error after ended game
void control_reset_integral(void);

/*Enablse the joystick control option by disabling the
timed position control regulator*/
void control_set_joystick_flag(int flag);



#endif /* CONTROL_DRIVER_H_ */