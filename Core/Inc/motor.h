#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "stm32f1xx_hal.h"
#include "math.h"
#include "spi.h"
#include "pid.h"
#include "tim.h"

#define PI 3.14159265358979323846f
#define Motor_Pole_Pairs 11
#define Motor_Direction -1

typedef enum Motor_Mode_Type
{
    Motor_Mode_Stop,
    Motor_Mode_Angle,
    Motor_Mode_Speed
} Motor_Mode_Type;

extern Motor_Mode_Type Motor_Mode;
extern PID Motor_Angle;
extern PID Motor_Speed;

extern float Motor_PWM_Duty_a;
extern float Motor_PWM_Duty_b;
extern float Motor_PWM_Duty_c;

extern uint16_t rxData;
extern float Motor_Current_Angle;
extern float Motor_Current_Speed;

extern float Motor_Voltage_Limit;
extern float Motor_Power_Voltage;
extern float Motor_Zero_Electric_Angle;

void Motor_Init();

void Motor_TransmitReceive();

void Motor_Set_Angle_Goal_Deg(float angle);

void Motor_Set_Speed_Goal(float speed);

void Motor_Set_Voltage(float U_q, float U_d, float electric_angle);

void Motor_TIM();
#endif