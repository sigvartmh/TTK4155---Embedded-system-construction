#include <avr/io.h>

#define epsilon 0.01
#define dt 0.02            //10ms loop time
#define MAX  200           //For Current Saturation
#define MIN -200

static double K_P, K_I, K_D;

void PID_tuning(double K_p, double K_i,double K_d){
	K_P=K_p;
	K_I=K_i;
	K_D=K_d;
}

int abs(int value){
	if(value < 0){
		return value*-1;
	}
	else{
		return value;
	}
}

int16_t PID_calculations(uint16_t reference, int16_t actual_position, int reset)
{
	int16_t output;
	
	double error;
	double derivative;
	
	static int16_t pre_error = 0;
    static double integral = 0;
	

	error = reference - actual_position;
	if(abs(error) > epsilon)
    {
    	integral = integral + error*dt;
    }
    derivative = (error - pre_error)/dt;
    output = K_P*error + K_I*integral + K_D*derivative;

    if(output > MAX) output = MAX;
    else if(output < MIN) output = MIN;

    pre_error = error;

    return output;
}