#include "pid.h"

float Restrict(float value, float min, float max)
{
    return (value) < min ? min : (value > max ? max : value);
}

float Normalize(float value, float min, float max)
{
    float T = max - min;
    while (value >= max)
        value -= T;
    while (value < min)
        value += T;
    return value;
}

void PID_Init(PID *pid, float Kp, float Ki, float Kd)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->error = 0;
    pid->error_last = 0;
    pid->error_sum = 0;
}

void PID_Clear(PID *pid)
{
    pid->error_sum = 0;
}

void PID_Set_Goal(PID *pid, float goal)
{
		if(pid->goal != goal)
		{
				pid->error_sum = 0;
				pid->goal = goal;
		}
}

float PID_Calculate(PID *pid, float data)
{
    pid->error = pid->goal - data;
    pid->error_sum += pid->error;
    float output = pid->Kp * pid->error + pid->Ki * pid->error_sum + pid->Kd * (pid->error - pid->error_last);
    pid->error_last = pid->error;
    return output;
}