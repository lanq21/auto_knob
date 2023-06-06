#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define OLED_Size 20
#define BLACK '.'
#define PI 3.14159265358979323846f

char OLED[OLED_Size][OLED_Size];

int X_Begin, Y_Begin, X_End, Y_End;
int Index = 0;
void OLED_Draw(int xbegin, int ybegin, int xend, int yend)
{
    Index = 0;
    X_Begin = xbegin;
    Y_Begin = ybegin;
    X_End = xend;
    Y_End = yend;
}

void OLED_Write_Data_16(unsigned char color)
{
    static int x, y;
    if (Index == 0)
        x = X_Begin, y = Y_Begin;
    OLED[x][y] = color;
    if (x == X_End)
        x = X_Begin, y++;
    else
        x++;
    Index++;
}

void OLED_Init()
{
    for (int i = 0; i < OLED_Size; i++)
        for (int j = 0; j < OLED_Size; j++)
            OLED[i][j] = '.';
}

void OLED_Draw_Point(uint16_t x, uint16_t y, uint16_t color)
{
    OLED[x][y] = color;
}

void Exange(uint16_t *a, uint16_t *b)
{
    uint16_t temp = *a;
    *a = *b;
    *b = temp;
}

void OLED_Draw_Line(uint16_t x_begin, uint16_t y_begin, uint16_t x_end, uint16_t y_end, float width, uint16_t color)
{
    int16_t x_Delta = x_end - x_begin;
    int16_t y_Delta = y_end - y_begin;

    uint8_t base_axis = 0; // 0: x-axis, 1: y-axis
    if (abs(x_Delta) > abs(y_Delta))
    {
        base_axis = 1;
        Exange(&x_begin, &y_begin);
        Exange(&x_end, &y_end);
        if (x_Delta < 0)
        {
            Exange(&x_begin, &x_end);
            Exange(&y_begin, &y_end);
        }
    }
    else if (y_Delta < 0)
    {
        Exange(&x_begin, &x_end);
        Exange(&y_begin, &y_end);
    }

    y_Delta = y_end - y_begin;
    x_Delta = x_end - x_begin;

    float cot_theta = (float)x_Delta / (float)y_Delta;       // cot(theta) = (x_end - x_begin) / (y_end - y_begin)
    float tan_theta = 1.0 / cot_theta;                       // tan(theta) = 1 / cot(theta)
    float sin_theta = 1.0 / sqrt(1 + cot_theta * cot_theta); // sin(theta) = 1 / sqrt(1 + cot^2(theta))
    float cos_theta = sin_theta * cot_theta;                 // cos(theta) = cot(theta) * sin(theta)

    float half_width_sin_theta = 0.5 * width * sin_theta; // 1/2 * width * sin(theta)

    float x_cut_1 = x_begin - half_width_sin_theta; // x_cut_1 = x_begin - 1/2 * width * sin(theta)
    float x_cut_2 = x_begin + half_width_sin_theta; // x_cut_2 = x_begin + 1/2 * width * sin(theta)
    float x_cut_3 = x_end - half_width_sin_theta;   // x_cut_3 = x_end - 1/2 * width * sin(theta)
    float x_cut_4 = x_end + half_width_sin_theta;   // x_cut_4 = x_end + 1/2 * width * sin(theta)

    uint16_t x_min = (x_begin - width / 2.0 > 0) ? ceil(x_begin - width / 2.0) : 0;
    uint16_t x_max = (x_end + width / 2.0 < OLED_Size - 1) ? floor(x_end + width / 2.0) : (OLED_Size - 1);
    float y_min, y_max, y_max_last = OLED_Size - 1;
    for (uint16_t x = x_min; x <= x_max; x++)
    {
        if (x < x_cut_2)
            y_min = y_begin - sqrt((width) * (width) / 4.0 - (x - x_begin) * (x - x_begin));
        else if (x > x_cut_4)
            y_min = y_end - sqrt((width) * (width) / 4.0 - (x - x_end) * (x - x_end));
        else
            y_min = y_begin + (x - x_begin) * tan_theta - 0.5 * width / cos_theta;
        if (x < x_cut_1)
            y_max = y_begin + sqrt((width) * (width) / 4.0 - (x - x_begin) * (x - x_begin));
        else if (x > x_cut_3)
            y_max = y_end + sqrt((width) * (width) / 4.0 - (x - x_end) * (x - x_end));
        else
            y_max = y_begin + (x - x_begin) * tan_theta + 0.5 * width / cos_theta;
        uint16_t average = (y_min + y_max) / 2.0 + 0.5;
        y_min = (y_min > 0) ? (y_min > y_max_last) ? y_max_last : ceil(y_min) : 0;
        y_max = (y_max < OLED_Size - 1) ? floor(y_max) : (OLED_Size - 1);
        for (uint16_t y = y_min; y <= y_max; y++)
        {
            if (base_axis == 0)
                OLED_Draw_Point(x, y, color);
            else
                OLED_Draw_Point(y, x, color);
        }
        y_max_last = y_max;
    }
}

void OLED_Draw_Rectangle(uint16_t x_begin, uint16_t y_begin, uint16_t x_end, uint16_t y_end, uint16_t color)
{
    OLED_Draw_Line(x_begin, y_begin, x_end, y_begin, 1, color);
    OLED_Draw_Line(x_begin, y_begin, x_begin, y_end, 1, color);
    OLED_Draw_Line(x_end, y_begin, x_end, y_end, 1, color);
    OLED_Draw_Line(x_begin, y_end, x_end, y_end, 1, color);
}

void OLED_Draw_Circle(uint16_t x, uint16_t y, float r, uint16_t color)
{
    int16_t x_begin = x - r + 0.5;
    int16_t x_end = x + r + 0.5;
    int16_t y_begin = y - r + 0.5;
    int16_t y_end = y + r + 0.5;

    x_begin = (x_begin > 0) ? x_begin : 0;
    x_end = (x_end < OLED_Size - 1) ? x_end : (OLED_Size - 1);
    y_begin = (y_begin > 0) ? y_begin : 0;
    y_end = (y_end < OLED_Size - 1) ? y_end : (OLED_Size - 1);
    uint32_t r_square = r * r + 0.5;

    OLED_Draw(x_begin, y_begin, x_end, y_end);

    for (uint16_t i = y_begin; i <= y_end; i++)
        for (uint16_t j = x_begin; j <= x_end; j++)
            if ((i - y) * (i - y) + (j - x) * (j - x) <= r_square)
                OLED_Write_Data_16(color);
            else
                OLED_Write_Data_16(BLACK);
}

void OLED_Draw_Radiu(uint16_t x, uint16_t y, float r, float width, int16_t angle_begin, int16_t angle_end, uint16_t color)
{
    float half_width = width / 2.0;
    if (angle_begin < 0)
        angle_begin += 360;
    while (angle_end < angle_begin)
        angle_end += 360;

    int16_t x_r_cos_begin = x + r * cosf(angle_begin / 180.0f * PI) + 0.5;
    int16_t y_r_sin_begin = y + r * sinf(angle_begin / 180.0f * PI) + 0.5;
    int16_t x_r_cos_end = x + r * cosf(angle_end / 180.0f * PI) + 0.5;
    int16_t y_r_sin_end = y + r * sinf(angle_end / 180.0f * PI) + 0.5;

    int16_t x_begin, x_end, y_begin, y_end;
    if (angle_begin <= 180 && angle_end >= 180 || angle_end >= 180 + 360)
        x_begin = x - r;
    else
        x_begin = (x_r_cos_begin < x_r_cos_end) ? x_r_cos_begin : x_r_cos_end;

    if (angle_end >= 360)
        x_end = x + r;
    else
        x_end = (x_r_cos_begin > x_r_cos_end) ? x_r_cos_begin : x_r_cos_end;

    if (angle_begin < 270 && angle_end > 270 || angle_end > 270 + 360)
        y_begin = y - r;
    else
        y_begin = (y_r_sin_begin < y_r_sin_end) ? y_r_sin_begin : y_r_sin_end;

    if (angle_begin < 90 && angle_end > 90 || angle_end > 90 + 360)
        y_end = y + r;
    else
        y_end = (y_r_sin_begin > y_r_sin_end) ? y_r_sin_begin : y_r_sin_end;

    x_begin = x_begin - half_width + 0.5;
    x_end = x_end + half_width + 0.5;
    y_begin = y_begin - half_width + 0.5;
    y_end = y_end + half_width + 0.5;

    x_begin = (x_begin > 0) ? x_begin : 0;
    x_end = (x_end < OLED_Size - 1) ? x_end : (OLED_Size - 1);
    y_begin = (y_begin > 0) ? y_begin : 0;
    y_end = (y_end < OLED_Size - 1) ? y_end : (OLED_Size - 1);

    uint32_t r_square_in = (r - half_width) * (r - half_width) + 0.5;
    uint32_t r_square_out = (r + half_width) * (r + half_width) + 0.5;

    OLED_Draw(x_begin, y_begin, x_end, y_end);

    uint32_t distance_square;
    for (uint16_t i = y_begin; i <= y_end; i++)
        for (uint16_t j = x_begin; j <= x_end; j++)
        {
            distance_square = (i - y) * (i - y) + (j - x) * (j - x);
            if (distance_square <= r_square_out && distance_square >= r_square_in)
            {
                int16_t angle = atan2f(i - y, j - x) / PI * 180.0f + 0.5;
                while(angle < angle_begin)
                    angle += 360;
                if (angle <= angle_end)
                    OLED_Write_Data_16(color);
                else
                    OLED_Write_Data_16(BLACK);
            }
            else
                OLED_Write_Data_16(BLACK);
        }
}

void OLED_Display()
{
    for (int i = 0; i < OLED_Size; i++)
    {
        for (int j = 0; j < OLED_Size; j++)
            printf("%c", OLED[i][j]);
        printf("\n");
    }
}

int main()
{
    OLED_Init();
    // OLED_Draw_Line(0, 0, 19, 19, 1, 'l');
    // OLED_Draw_Circle(10, 10, 5, 'c');
    OLED_Draw_Radiu(10, 10, 6, 2, 30, 160, 'r');
    OLED_Display();
    return 0;
}