#include <stdio.h>
#include <math.h>

int hasEnd = 1;
float endAngle = 280;
int hasStart = 1;
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
        Knob_TIM();
    }
}