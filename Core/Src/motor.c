#include "motor.h"

Motor_Mode_Type Motor_Mode;

PID Motor_Angle;
PID Motor_Speed;
float Motor_Torque_Goal;

float Motor_PWM_Duty_a;
float Motor_PWM_Duty_b;
float Motor_PWM_Duty_c;

const uint16_t cmdAngle = 0xffff;
uint16_t rxData;
float Motor_Current_Angle;
float Motor_Current_Speed;

float Motor_Zero_Electric_Angle = 0;

float Motor_Electric_Angle()
{
    return Normalize(Motor_Current_Angle * Motor_Pole_Pairs  * Motor_Direction - Motor_Zero_Electric_Angle, 0.0f, 360.0f);
}

void Motor_TransmitReceive()
{
	HAL_GPIO_WritePin(SPI3CS_GPIO_Port, SPI3CS_Pin, 0);
    HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)&cmdAngle, (uint8_t *)&rxData, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(SPI3CS_GPIO_Port, SPI3CS_Pin, 1);
	
	HAL_GPIO_WritePin(SPI3CS_GPIO_Port, SPI3CS_Pin, 0);
    HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)&cmdAngle, (uint8_t *)&rxData, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(SPI3CS_GPIO_Port, SPI3CS_Pin, 1);
	
    float angle = (float)(rxData & 0x3fff) * 360.0f / 16384.0f;
    Motor_Current_Speed = Normalize(angle - Motor_Current_Angle, -180.0f, 180.0f);
    Motor_Current_Angle = angle;
}

void Motor_PWM_Output(float U_a, float U_b, float U_c)
{
    U_a = Restrict(U_a, 0.0f, Motor_Voltage_Limit);
    U_b = Restrict(U_b, 0.0f, Motor_Voltage_Limit);
    U_c = Restrict(U_c, 0.0f, Motor_Voltage_Limit);

    Motor_PWM_Duty_a = Restrict(U_a / Motor_Power_Voltage, 0.0f, 1.0f);
    Motor_PWM_Duty_b = Restrict(U_b / Motor_Power_Voltage, 0.0f, 1.0f);
    Motor_PWM_Duty_c = Restrict(U_c / Motor_Power_Voltage, 0.0f, 1.0f);

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (uint16_t)(Motor_PWM_Duty_a * 1999));
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (uint16_t)(Motor_PWM_Duty_b * 1999));
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, (uint16_t)(Motor_PWM_Duty_c * 1999));
}

void Motor_Set_Voltage(float U_q, float U_d, float electric_angle)
{
    float _electric_angle = Normalize(electric_angle, 0.0f, 360.0f) / 180.0f * PI;
    float U_alpha = U_d * cosf(_electric_angle) - U_q * sinf(_electric_angle);
    float U_beta = U_d * sinf(_electric_angle) + U_q * cosf(_electric_angle);
    float U_a = U_alpha + Motor_Power_Voltage / 2.0f;
    float U_b = -0.5f * U_alpha + sqrt(3) / 2.0f * U_beta + Motor_Power_Voltage / 2.0f;
    float U_c = -0.5f * U_alpha - sqrt(3) / 2.0f * U_beta + Motor_Power_Voltage / 2.0f;
    Motor_PWM_Output(U_a, U_b, U_c);
}

void Motor_Init()
{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 1);
    PID_Init(&Motor_Angle, 1.0f, 0.0f, 0.0f);
    Motor_Angle.flag_angle = 1;
    PID_Init(&Motor_Speed, 0.1f, 0.0f, 0.0f);
    Motor_TransmitReceive();
    Motor_Current_Speed = 0;
    Motor_Set_Voltage(3, 0, 270);
    HAL_Delay(3000);
    Motor_TransmitReceive();
    Motor_Zero_Electric_Angle = Motor_Electric_Angle();
    Motor_Set_Voltage(0, 0, 270);
    Motor_Mode = Motor_Mode_Stop;
}

void Motor_Set_Angle_Goal_Deg(float angle)
{
    Motor_Mode = Motor_Mode_Angle;
    PID_Set_Goal(&Motor_Angle, angle);
}

void Motor_Set_Speed_Goal(float speed)
{
    Motor_Mode = Motor_Mode_Speed;
    PID_Set_Goal(&Motor_Speed, speed);
}

void Motor_Set_Torque_Goal(float torque)
{
    Motor_Mode = Motor_Mode_Torque;
    Motor_Torque_Goal = torque;
}

void Motor_Run()
{
    float U_q;
    if (Motor_Mode == Motor_Mode_Speed)
        U_q += PID_Calculate(&Motor_Speed, Motor_Current_Speed);
    else if (Motor_Mode == Motor_Mode_Angle)
        U_q = PID_Calculate(&Motor_Angle, Motor_Current_Angle);
    else if(Motor_Mode == Motor_Mode_Torque)
        U_q = Restrict(Motor_Torque_Goal, -1.0f, 1.0f)* Motor_Voltage_Limit / 2.0f;
    else if (Motor_Mode == Motor_Mode_Stop)
        U_q = 0;
    U_q = Restrict(U_q, -Motor_Voltage_Limit / 2.0f, Motor_Voltage_Limit / 2.0f);
    Motor_Set_Voltage(U_q, 0, Motor_Electric_Angle());
}

void Motor_TIM()
{
    Motor_TransmitReceive();
    Motor_Run();
}