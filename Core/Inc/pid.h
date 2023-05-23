#ifndef _PID_H_
#define _PID_H_

#include "stdint.h"

typedef struct PID
{
    float Kp;
    float Ki;
    float Kd;
    float goal;
    float error;
    float error_last;
    float error_sum;
    uint8_t flag_angle;
} PID;

float Restrict(float value,float min,float max);

float Normalize(float value, float min, float max);

void PID_Init(PID *pid, float Kp, float Ki, float Kd);

void PID_Clear(PID *pid);

void PID_Set_Goal(PID *pid, float goal);

float PID_Calculate(PID *pid, float data);

#endif