#include "..\Inc\pid.h"
#include "pid.h"

float Restrict(float value, float min, float max)
{
    return (value) < min ? min : (value > max ? max : value);
}

float Normalize(float value, float min, float max)
{
    float mod = fmod(value, max - min);
    return (mod >= 0) ? (mod + min) : (mod + max);
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
    pid->error_sum = 0;
    pid->goal = goal;
}

float PID_Calculate(PID *pid, float data)
{
    pid->error = pid->goal - data;
    pid->error_sum += pid->error;
    float output = pid->Kp * pid->error + pid->Ki * pid->error_sum + pid->Kd * (pid->error - pid->error_last);
    pid->error_last = pid->error;
    return output;
}
