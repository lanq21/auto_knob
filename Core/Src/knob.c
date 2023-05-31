#include "knob.h"

float Cos[360];
float Sin[360];

Knob_Mode_Type Knob_Mode;
float closest_angle[361];
uint16_t last_angle;

void Knob_Init()
{
    for (uint16_t i = 0; i < 360; i++)
    {
        Cos[i] = cos(i / 180.0 * 3.14159);
        Sin[i] = sin(i / 180.0 * 3.14159);
    }

    for (uint16_t i = 0; i < 360; ++i)
        closest_angle[i] = 0.0f;

    last_angle = 0;

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

    Motor_Init();
    HAL_TIM_Base_Start_IT(&htim2);
    Motor_Set_Angle_Goal_Deg(0.0f);

    OLED_Init();
    OLED_Clear();
    OLED_Draw_Line(10, 10, 227, 227, 10, WHITE);
    OLED_Draw_Line(10, 227, 227, 10, 10, WHITE);
    OLED_Clear();
}

void Knob_Fixed_Angle_Init(float angle)
{
    Knob_Mode = Fixed_Angle;
    Motor_Set_Angle_Goal_Deg(angle);
}

void Knob_Fixed_Speed_Init(float speed)
{
    Knob_Mode = Fixed_Speed;
    Motor_Set_Speed_Goal(speed);
}

void Knob_Fixed_Torque_Init(float torque)
{
    Knob_Mode = Fixed_Torque;
    Motor_Set_Torque_Goal(torque);
}

void Knob_Multi_Switch_Init(uint16_t count)
{
    Knob_Mode = Multi_Switch;
    uint16_t step = 360 / count;
    uint16_t angle = 0;
    for (int i = 1; i <= count; i++)
    {
        for (; angle < i * step; angle++)
            closest_angle[angle] = i * step - step / 2.0f;
    }
    for (; angle <= 360; angle++)
        closest_angle[angle] = 360.0f - step / 2.0f;
}

void Knob_Run()
{
	uint16_t angle = (uint16_t) Motor_Current_Angle;
    if (Knob_Mode == Multi_Switch)
    {
        OLED_Draw_Line(120, 120, 120 + 80 * Cos[last_angle], 120 - 80 * Sin[last_angle], 5, BLACK);
		OLED_Draw_Line(120, 120, 120 + 80 * Cos[angle], 120 - 80 * Sin[angle], 5, WHITE);
    }
    last_angle = angle;
}