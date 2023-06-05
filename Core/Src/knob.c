#include "knob.h"

uint8_t uartBuf[30];
float startAngle, endAngle, lvlAngle;
uint8_t hasStart, hasEnd, hasLvl;
uint8_t Draw_Mode;

float Cos[360];
float Sin[360];

float closest_angle[361];
uint16_t last_angle;
uint8_t clear_task;

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

    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uartBuf, 30);

    OLED_Init();
    OLED_Clear();
    OLED_Draw_Line(10, 10, 227, 227, 10, WHITE);
    OLED_Draw_Line(10, 227, 227, 10, 10, WHITE);
    OLED_Clear();

    Draw_Mode = 0;
    clear_task = 0;
}

void Knob_Draw()
{
    uint16_t angle = (uint16_t)Motor_Current_Angle;
    if (clear_task)
    {
        OLED_Clear();
        clear_task = 0;
    }
    if (Draw_Mode == 0)
    {
        OLED_Draw_Circle_Covered(120 + 70 * Cos[last_angle], 120 - 70 * Sin[last_angle], 10, BLACK);
        OLED_Draw_Circle_Covered(120 + 70 * Cos[angle], 120 - 70 * Sin[angle], 10, WHITE);
        uint8_t mode = 5 - (angle + 36) / 72;
        mode = mode > 4 ? 0 : mode;
        OLED_Fill(120 - 8, 120 - 16, 120 + 8, 120 + 16, BLACK);
        OLED_Draw_Int(120 - 8, 120 - 16, mode, WHITE, BLACK, 32, 1);
    }
    else if (Draw_Mode == 1)
    {
        OLED_Draw_Circle_Covered(120 + 70 * Cos[last_angle], 120 - 70 * Sin[last_angle], 10, BLACK);
        OLED_Draw_Circle_Covered(120 + 70 * Cos[angle], 120 - 70 * Sin[angle], 10, WHITE);
        uint8_t vol = 100 - Restrict(angle / 2 - 40, 0, 100);
        OLED_Fill(120 - 16, 120 - 16, 120 + 32, 120 + 16, BLACK);
        OLED_Draw_Int(120 - 16, 120 - 16, vol, WHITE, BLACK, 32, 1);
    }
    else if (Draw_Mode == 2)
    {
        OLED_Draw_Line(120, 120, 120 + 80 * Cos[last_angle], 120 - 80 * Sin[last_angle], 5, BLACK);
        OLED_Draw_Line(120, 120, 120 + 80 * Cos[angle], 120 - 80 * Sin[angle], 5, WHITE);
    }
    else if (Draw_Mode == 3 || Draw_Mode == 4)
    {
        if (last_angle < 180)
            OLED_Draw_Radiu(120, 120, 70, 6, last_angle - 5, 180, BLACK);
        else
            OLED_Draw_Radiu(120, 120, 70, 6, 180, last_angle + 5, BLACK);
        if (angle < 180)
            OLED_Draw_Radiu(120, 120, 70, 4, angle, 180, WHITE);
        else
            OLED_Draw_Radiu(120, 120, 70, 4, 180, angle, WHITE);
        uint8_t err = angle > 180 ? angle - 180 : 180 - angle;
        OLED_Fill(120 - 16, 120 - 16, 120 + 32, 120 + 16, BLACK);
        OLED_Draw_Int(120 - 16, 120 - 16, err, WHITE, BLACK, 32, 1);
    }
    last_angle = angle;
}

void Knob_TIM()
{
    float tmpAngleGoal;
    if (hasEnd && Motor_Global_Angle > endAngle)
    {
        tmpAngleGoal = endAngle;
        Motor_Set_Angle_Goal_Deg(tmpAngleGoal);
    }
    else if (hasStart && Motor_Global_Angle < startAngle)
    {
        tmpAngleGoal = startAngle;
        Motor_Set_Angle_Goal_Deg(tmpAngleGoal);
    }
    else if (hasLvl && lvlAngle > 0.0f)
    {
        int32_t tmp = (Motor_Global_Angle - startAngle) / lvlAngle;
        float res = fabs(Motor_Global_Angle - (startAngle + tmp * lvlAngle)) / lvlAngle;
        if (res > 0.5f)
        {
            if (Motor_Global_Angle > startAngle)
                tmpAngleGoal = startAngle + (tmp + 1) * lvlAngle;
            else
                tmpAngleGoal = startAngle + (tmp - 1) * lvlAngle;
        }
        else
            tmpAngleGoal = startAngle + tmp * lvlAngle;
        Motor_Set_Angle_Goal_Deg(tmpAngleGoal);
    }
    else
        Motor_Mode = Motor_Mode_Stop;
}

void Knob_UART()
{
    hasStart = uartBuf[0] & (1 << 0);
    hasEnd = uartBuf[0] & (1 << 1);
    hasLvl = uartBuf[0] & (1 << 2);
    lvlAngle = *((float *)(uartBuf + 1));
    startAngle = *((float *)(uartBuf + 5));
    endAngle = *((float *)(uartBuf + 9));
    if (Draw_Mode != uartBuf[13])
        clear_task = 1;
    Draw_Mode = uartBuf[13];
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uartBuf, 30);
}