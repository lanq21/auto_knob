#include <stdio.h>
#include <math.h>
#include <stdint.h>

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

float Normalize(float value, float min, float max)
{
    float T = max - min;
    while (value >= max)
        value -= T;
    while (value < min)
        value += T;
    return value;
}

float PID_Calculate(PID *pid, float data)
{
    pid->error = pid->goal - data;
    if (pid->flag_angle)
        pid->error = Normalize(pid->error, -180.0f, 180.0f);
    pid->error_sum += pid->error;
    float output = pid->Kp * pid->error + pid->Ki * pid->error_sum + pid->Kd * (pid->error - pid->error_last);
    pid->error_last = pid->error;
    return output;
}

PID Motor_Angle = {0.1f, 0.0f, 0.0f, 100, 0, 0, 0, 1};

float closest_angle[360];
void Knob_Multi_Switch_Init(uint16_t count)
{
    uint16_t step = 360 / count;
    uint16_t angle = 0;
    for (int i = 1; i <= count; i++)
    {
        for (; angle < i * step; angle++)
            closest_angle[angle] = i * step - step / 2.0f;
    }
    for(; angle<360;angle++)
        closest_angle[angle] = 360.0f - step / 2.0f;
}

#include <stdio.h>
#include <math.h>

int hasEnd = 0;
float endAngle = 360;
int hasStart = 0;
float startAngle = 0;
int hasLvl = 1;
float lvlAngle = 72;

float Motor_Global_Angle = 0.0f;

void Motor_Set_Angle_Goal_Deg(float angle)
{
    printf("Motor_Set_Angle_Goal_Deg: %f\n", angle);
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
        int tmp = (Motor_Global_Angle - startAngle) / lvlAngle;
        float res = fabs(Motor_Global_Angle - (startAngle + tmp * lvlAngle)) / lvlAngle;
        if (res > 0.5f)
            tmpAngleGoal = startAngle + (tmp + 1) * lvlAngle;
        else
            tmpAngleGoal = startAngle + tmp * lvlAngle;
        tmpAngleGoal = fmod(tmpAngleGoal, 360.0f);
        if (tmpAngleGoal < 0.0f)
            tmpAngleGoal += 360.0f;

        Motor_Set_Angle_Goal_Deg(tmpAngleGoal);
    }   
}

int main()
{
    while (1)
    {
        //scanf("%f", &Motor_Global_Angle);
        //Knob_TIM();
        int a= 1;
        printf("%d\n", 395/72);
    }
}