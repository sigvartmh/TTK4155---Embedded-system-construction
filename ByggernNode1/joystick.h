#ifndef JOYSTICK_H_
#define JOYSTICK_H_

uint8_t mid_x, mid_y;

typedef struct {
	int8_t x;
	int8_t y;
	char *direction;
} joy_position;

typedef struct {
	uint8_t left;
	uint8_t right;
} slider_position;

int JOY_init(void);
int JOY_calibrate(void);
int JOY_button(int button);
joy_position JOY_getPosition(void);
joy_position JOY_getDirection(void);
slider_position JOY_getSliderPosition(void);

#endif