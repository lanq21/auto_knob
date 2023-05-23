#include "motor.h"
#include "oled.h"

#include "math.h"
#include "tim.h"

typedef enum Knob_Mode_Type
{
    Fixed_Angle,
    Fixed_Speed,
    Fixed_Torque,
    Multi_Switch,
} Knob_Mode_Type;


extern float Cos[360];
extern float Sin[360];

extern float closest_angle[361];

extern Knob_Mode_Type Knob_Mode;

void Knob_Init();

void Knob_Fixed_Angle_Init(float angle);

void Knob_Fixed_Speed_Init(float speed);

void Knob_Fixed_Torque_Init(float torque);

void Knob_Multi_Switch_Init(uint16_t count);

void Knob_Run();