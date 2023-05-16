#include "motor.h"
#include "usart.h"

Motor_Mode_Type Motor_Mode = Motor_Mode_Stop;

PID Motor_Angle;
PID Motor_Speed;

float Motor_PWM_Duty_a;
float Motor_PWM_Duty_b;
float Motor_PWM_Duty_c;

uint16_t cmdAngle = 0xffff;
uint16_t rxData;
float Motor_Current_Angle;
float Motor_Current_Speed;

float Motor_Voltage_Limit = 10;
float Motor_Power_Voltage = 12.6;
float Motor_Zero_Electric_Angle = 0;

void Motor_Init()
{
    PID_Init(&Motor_Angle, 0.1f, 0.0f, 0.0f);
    PID_Init(&Motor_Speed, 0.1f, 0.0f, 0.0f);
    Motor_TransmitReceive();
    rxData = 0;
    Motor_Current_Angle = 0;
    Motor_Current_Speed = 0;
    Motor_Set_Voltage(3, 0, 270);
    HAL_Delay(3000);
    Motor_Set_Voltage(0, 0, 270);
    Motor_Zero_Electric_Angle = Motor_Current_Angle;
    Motor_Mode = Motor_Mode_Stop;
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
    Motor_Current_Speed = angle - Motor_Current_Angle;
    Motor_Current_Angle = angle;
	u1_printf("%f\n",angle);
}

float Motor_Electric_Angle()
{
    return Normalize(Motor_Current_Angle * Motor_Pole_Pairs  * Motor_Direction - Motor_Zero_Electric_Angle, 0.0f, 360.0f);
}

void Motor_PWM_Output(float U_a, float U_b, float U_c)
{
    U_a = Restrict(U_a, 0.0f, Motor_Voltage_Limit);
    U_b = Restrict(U_b, 0.0f, Motor_Voltage_Limit);
    U_c = Restrict(U_c, 0.0f, Motor_Voltage_Limit);

    Motor_PWM_Duty_a = Restrict(U_a / Motor_Power_Voltage, 0.0f, 1.0f);
    Motor_PWM_Duty_b = Restrict(U_b / Motor_Power_Voltage, 0.0f, 1.0f);
    Motor_PWM_Duty_c = Restrict(U_c / Motor_Power_Voltage, 0.0f, 1.0f);

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (uint16_t)(Motor_PWM_Duty_a * 65535));
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (uint16_t)(Motor_PWM_Duty_b * 65535));
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, (uint16_t)(Motor_PWM_Duty_c * 65535));
}

void Motor_Set_Voltage(float U_q, float U_d, float electric_angle)
{
    electric_angle = Normalize(electric_angle, 0.0f, 360.0f) / 180.0f * PI;
    float U_alpha = U_d * cosf(electric_angle) - U_q * sinf(electric_angle);
    float U_beta = U_d * sinf(electric_angle) + U_q * cosf(electric_angle);
    float U_a = U_alpha + Motor_Power_Voltage / 2.0f;
    float U_b = -0.5f * U_alpha + sqrt(3) / 2.0f * U_beta + Motor_Power_Voltage / 2.0f;
    float U_c = -0.5f * U_alpha - sqrt(3) / 2.0f * U_beta + Motor_Power_Voltage / 2.0f;
    Motor_PWM_Output(U_a, U_b, U_c);
}

void Motor_Set_Angle_Goal_Deg(float angle)
{
    Motor_Mode = Motor_Mode_Angle;
    float goal_negetive = angle - 360.0f;
    float goal_positive = angle + 360.0f;
    if (Motor_Current_Angle - goal_negetive < fabsf(Motor_Current_Angle - angle))
        angle = goal_negetive;
    else if (goal_positive - Motor_Current_Angle < fabsf(Motor_Current_Angle - angle))
        angle = goal_positive;
    PID_Set_Goal(&Motor_Angle, angle);
}

void Motor_Set_Speed_Goal(float speed)
{
    Motor_Mode = Motor_Mode_Speed;
    // todo
    PID_Set_Goal(&Motor_Speed, speed);
}

void Motor_Run()
{
    float U_q;
    if (Motor_Mode == Motor_Mode_Speed)
        U_q = PID_Calculate(&Motor_Speed, Motor_Current_Angle);
    else if (Motor_Mode == Motor_Mode_Angle)
        U_q = PID_Calculate(&Motor_Angle, Motor_Current_Angle);
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