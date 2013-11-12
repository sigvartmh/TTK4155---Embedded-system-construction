#define epsilon 0.01
#define dt 0.02             //10ms loop time
#define MAX  200                   //For Current Saturation
#define MIN -200

PID_tuning(K_p, K_i, K_d){
	
}

int16_t PID_calculations(uint16_t reference, int16_t actual_position, int reset)
{
	static int16_t pre_error = 0;
    static double integral = 0;
	
	double K_p, K_i, K_d;

	error = reference - actual_position;
	if(abs(error) > epsilon)
    {
    	//printf("error: %d\n", (int)(error*dt*10000));
    	integral = integral + error*dt;
        //printf("integral: %d\n", (int)integral);
    }
    derivative = (error - pre_error)/dt;
    output = Kp*error + Ki*integral + Kd*derivative;

    if(output > MAX) output = MAX;
    else if(output < MIN) output = MIN;

    pre_error = error;

    return output;
}