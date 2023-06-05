#include "motor.h"
#include "oled.h"

#include "math.h"
#include "tim.h"
#include "usart.h"

extern uint8_t uartBuf[30];
extern float startAngle, endAngle, lvlAngle;
extern uint8_t hasStart, hasEnd, hasLvl;
extern uint8_t Draw_Mode;

extern float Cos[360];
extern float Sin[360];

extern float closest_angle[361];

void Knob_Init();

void Knob_Draw();

void Knob_TIM();

void Knob_UART();