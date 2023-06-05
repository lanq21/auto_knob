#include "oled.h"

void Exange(uint16_t *a, uint16_t *b)
{
    uint16_t temp = *a;
    *a = *b;
    *b = temp;
}

// OLED 初始化
void OLED_Init(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET); // 复位
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_Delay(100);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET); // 打开背光
    HAL_Delay(100);

    OLED_Write_Cmd(0xEF);
    OLED_Write_Cmd(0xEB);
    OLED_Write_Data_8(0x14);

    OLED_Write_Cmd(0xFE);
    OLED_Write_Cmd(0xEF);

    OLED_Write_Cmd(0xEB);
    OLED_Write_Data_8(0x14);

    OLED_Write_Cmd(0x84);
    OLED_Write_Data_8(0x40);

    OLED_Write_Cmd(0x85);
    OLED_Write_Data_8(0xFF);

    OLED_Write_Cmd(0x86);
    OLED_Write_Data_8(0xFF);

    OLED_Write_Cmd(0x87);
    OLED_Write_Data_8(0xFF);

    OLED_Write_Cmd(0x88);
    OLED_Write_Data_8(0x0A);

    OLED_Write_Cmd(0x89);
    OLED_Write_Data_8(0x21);

    OLED_Write_Cmd(0x8A);
    OLED_Write_Data_8(0x00);

    OLED_Write_Cmd(0x8B);
    OLED_Write_Data_8(0x80);

    OLED_Write_Cmd(0x8C);
    OLED_Write_Data_8(0x01);

    OLED_Write_Cmd(0x8D);
    OLED_Write_Data_8(0x01);

    OLED_Write_Cmd(0x8E);
    OLED_Write_Data_8(0xFF);

    OLED_Write_Cmd(0x8F);
    OLED_Write_Data_8(0xFF);

    OLED_Write_Cmd(0xB6);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0x20);

    OLED_Write_Cmd(0x36);
    OLED_Write_Data_8(0x08);

    OLED_Write_Cmd(0x3A);
    OLED_Write_Data_8(0x05);

    OLED_Write_Cmd(0x90);
    OLED_Write_Data_8(0x08);
    OLED_Write_Data_8(0x08);
    OLED_Write_Data_8(0x08);
    OLED_Write_Data_8(0x08);

    OLED_Write_Cmd(0xBD);
    OLED_Write_Data_8(0x06);

    OLED_Write_Cmd(0xBC);
    OLED_Write_Data_8(0x00);

    OLED_Write_Cmd(0xFF);
    OLED_Write_Data_8(0x60);
    OLED_Write_Data_8(0x01);
    OLED_Write_Data_8(0x04);

    OLED_Write_Cmd(0xC3);
    OLED_Write_Data_8(0x13);
    OLED_Write_Cmd(0xC4);
    OLED_Write_Data_8(0x13);

    OLED_Write_Cmd(0xC9);
    OLED_Write_Data_8(0x22);

    OLED_Write_Cmd(0xBE);
    OLED_Write_Data_8(0x11);

    OLED_Write_Cmd(0xE1);
    OLED_Write_Data_8(0x10);
    OLED_Write_Data_8(0x0E);

    OLED_Write_Cmd(0xDF);
    OLED_Write_Data_8(0x21);
    OLED_Write_Data_8(0x0c);
    OLED_Write_Data_8(0x02);

    OLED_Write_Cmd(0xF0);
    OLED_Write_Data_8(0x45);
    OLED_Write_Data_8(0x09);
    OLED_Write_Data_8(0x08);
    OLED_Write_Data_8(0x08);
    OLED_Write_Data_8(0x26);
    OLED_Write_Data_8(0x2A);

    OLED_Write_Cmd(0xF1);
    OLED_Write_Data_8(0x43);
    OLED_Write_Data_8(0x70);
    OLED_Write_Data_8(0x72);
    OLED_Write_Data_8(0x36);
    OLED_Write_Data_8(0x37);
    OLED_Write_Data_8(0x6F);

    OLED_Write_Cmd(0xF2);
    OLED_Write_Data_8(0x45);
    OLED_Write_Data_8(0x09);
    OLED_Write_Data_8(0x08);
    OLED_Write_Data_8(0x08);
    OLED_Write_Data_8(0x26);
    OLED_Write_Data_8(0x2A);

    OLED_Write_Cmd(0xF3);
    OLED_Write_Data_8(0x43);
    OLED_Write_Data_8(0x70);
    OLED_Write_Data_8(0x72);
    OLED_Write_Data_8(0x36);
    OLED_Write_Data_8(0x37);
    OLED_Write_Data_8(0x6F);

    OLED_Write_Cmd(0xED);
    OLED_Write_Data_8(0x1B);
    OLED_Write_Data_8(0x0B);

    OLED_Write_Cmd(0xAE);
    OLED_Write_Data_8(0x77);

    OLED_Write_Cmd(0xCD);
    OLED_Write_Data_8(0x63);

    OLED_Write_Cmd(0x70);
    OLED_Write_Data_8(0x07);
    OLED_Write_Data_8(0x07);
    OLED_Write_Data_8(0x04);
    OLED_Write_Data_8(0x0E);
    OLED_Write_Data_8(0x0F);
    OLED_Write_Data_8(0x09);
    OLED_Write_Data_8(0x07);
    OLED_Write_Data_8(0x08);
    OLED_Write_Data_8(0x03);

    OLED_Write_Cmd(0xE8);
    OLED_Write_Data_8(0x34);

    OLED_Write_Cmd(0x62);
    OLED_Write_Data_8(0x18);
    OLED_Write_Data_8(0x0D);
    OLED_Write_Data_8(0x71);
    OLED_Write_Data_8(0xED);
    OLED_Write_Data_8(0x70);
    OLED_Write_Data_8(0x70);
    OLED_Write_Data_8(0x18);
    OLED_Write_Data_8(0x0F);
    OLED_Write_Data_8(0x71);
    OLED_Write_Data_8(0xEF);
    OLED_Write_Data_8(0x70);
    OLED_Write_Data_8(0x70);

    OLED_Write_Cmd(0x63);
    OLED_Write_Data_8(0x18);
    OLED_Write_Data_8(0x11);
    OLED_Write_Data_8(0x71);
    OLED_Write_Data_8(0xF1);
    OLED_Write_Data_8(0x70);
    OLED_Write_Data_8(0x70);
    OLED_Write_Data_8(0x18);
    OLED_Write_Data_8(0x13);
    OLED_Write_Data_8(0x71);
    OLED_Write_Data_8(0xF3);
    OLED_Write_Data_8(0x70);
    OLED_Write_Data_8(0x70);

    OLED_Write_Cmd(0x64);
    OLED_Write_Data_8(0x28);
    OLED_Write_Data_8(0x29);
    OLED_Write_Data_8(0xF1);
    OLED_Write_Data_8(0x01);
    OLED_Write_Data_8(0xF1);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0x07);

    OLED_Write_Cmd(0x66);
    OLED_Write_Data_8(0x3C);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0xCD);
    OLED_Write_Data_8(0x67);
    OLED_Write_Data_8(0x45);
    OLED_Write_Data_8(0x45);
    OLED_Write_Data_8(0x10);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0x00);

    OLED_Write_Cmd(0x67);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0x3C);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0x01);
    OLED_Write_Data_8(0x54);
    OLED_Write_Data_8(0x10);
    OLED_Write_Data_8(0x32);
    OLED_Write_Data_8(0x98);

    OLED_Write_Cmd(0x74);
    OLED_Write_Data_8(0x10);
    OLED_Write_Data_8(0x85);
    OLED_Write_Data_8(0x80);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0x00);
    OLED_Write_Data_8(0x4E);
    OLED_Write_Data_8(0x00);

    OLED_Write_Cmd(0x98);
    OLED_Write_Data_8(0x3e);
    OLED_Write_Data_8(0x07);

    OLED_Write_Cmd(0x35);
    OLED_Write_Cmd(0x21);

    OLED_Write_Cmd(0x11);
    HAL_Delay(120);
    OLED_Write_Cmd(0x29);
    HAL_Delay(20);
}

// SPI 发送命令
void OLED_Write_Cmd(uint8_t cmd)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
}

// SPI 发送数据
void OLED_Write_Data_8(uint8_t data)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}

void OLED_Write_Data_16(uint16_t data)
{
    uint8_t data_buf[2];
    data_buf[0] = data >> 8;
    data_buf[1] = data;
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, data_buf, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}

void OLED_Draw(uint16_t x_begin, uint16_t y_begin, uint16_t x_end, uint16_t y_end)
{
    OLED_Write_Cmd(0x2a); // 设置列地址
    OLED_Write_Data_16(x_begin);
    OLED_Write_Data_16(x_end);
    OLED_Write_Cmd(0x2b); // 设置行地址
    OLED_Write_Data_16(y_begin);
    OLED_Write_Data_16(y_end);
    OLED_Write_Cmd(0x2c); // 储存器写
}

// 清屏, 全部填充为黑色
void OLED_Clear()
{
    OLED_Fill(0, 0, OLED_Size - 1, OLED_Size - 1, BLACK);
}

// 填充矩形区域
void OLED_Fill(uint16_t x_begin, uint16_t y_begin, uint16_t x_end, uint16_t y_end, uint16_t color)
{
    if (x_begin > x_end)
        Exange(&x_begin, &x_end);
    if (y_begin > y_end)
        Exange(&y_begin, &y_end);
    x_end = x_end >= OLED_Size ? OLED_Size - 1 : x_end;
    y_end = y_end >= OLED_Size ? OLED_Size - 1 : y_end;

    OLED_Draw(x_begin, y_begin, x_end, y_end);

    for (uint16_t i = y_begin; i <= y_end; i++)
        for (uint16_t j = x_begin; j <= x_end; j++)
            OLED_Write_Data_16(color);
}

// 画一个点
void OLED_Draw_Point(uint16_t x, uint16_t y, uint16_t color)
{
    OLED_Draw(x, y, x, y);
    OLED_Write_Data_16(color);
}

void OLED_Draw_Line(uint16_t x_begin, uint16_t y_begin, uint16_t x_end, uint16_t y_end, float width, uint16_t color)
{
    int16_t x_Delta = x_end - x_begin;
    int16_t y_Delta = y_end - y_begin;

    uint8_t base_axis = 0;                                                                      // 0: x-axis, 1: y-axis
    if ((x_Delta < y_Delta || y_Delta < -x_Delta) && (y_Delta > -x_Delta || y_Delta < x_Delta)) // abs(x_Delta) < abs(y_Delta)
    {
        base_axis = 1;
        Exange(&x_begin, &y_begin);
        Exange(&x_end, &y_end);
        if (y_Delta < 0)
        {
            Exange(&x_begin, &x_end);
            Exange(&y_begin, &y_end);
        }
    }
    else if (x_Delta < 0)
    {
        Exange(&x_begin, &x_end);
        Exange(&y_begin, &y_end);
    }

    y_Delta = y_end - y_begin;
    x_Delta = x_end - x_begin;

    float tan_theta = (float)y_Delta / (float)x_Delta;             // tan(theta) = (y_end - y_begin) / (x_end - x_begin)
    float cos_theta = 1.0 / sqrt(1 + tan_theta * tan_theta);       // cos(theta) = 1 / sqrt(1 + tan^2(theta))
    float sin_theta = tan_theta / sqrt(1 + tan_theta * tan_theta); // sin(theta) = tan(theta) / sqrt(1 + tan^2(theta))

    float half_width_sin_theta = 0.5 * width * sin_theta; // 1/2 * width * sin(theta)

    float x_cut_1 = x_begin - half_width_sin_theta; // x_cut_1 = x_begin - 1/2 * width * sin(theta)
    float x_cut_2 = x_begin + half_width_sin_theta; // x_cut_2 = x_begin + 1/2 * width * sin(theta)
    float x_cut_3 = x_end - half_width_sin_theta;   // x_cut_3 = x_end - 1/2 * width * sin(theta)
    float x_cut_4 = x_end + half_width_sin_theta;   // x_cut_4 = x_end + 1/2 * width * sin(theta)

    uint16_t x_min = (x_begin - width / 2.0 > 0) ? ceil(x_begin - width / 2.0) : 0;
    uint16_t x_max = (x_end + width / 2.0 < OLED_Size - 1) ? floor(x_end + width / 2.0) : (OLED_Size - 1);
    float y_min, y_max;
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

        y_min = (y_min > 0) ? ceil(y_min) : 0;
        y_max = (y_max < OLED_Size - 1) ? floor(y_max) : (OLED_Size - 1);
        if (y_min > y_max)
            y_min = y_max = (uint16_t)(y_min + y_max) / 2.0 + 0.5;
        for (uint16_t y = y_min; y <= y_max; y++)
        {
            if (base_axis == 0)
                OLED_Draw_Point(x, y, color);
            else
                OLED_Draw_Point(y, x, color);
        }
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
    for (uint16_t i = y_begin; i <= y_end; i++)
        for (uint16_t j = x_begin; j <= x_end; j++)
            if ((i - y) * (i - y) + (j - x) * (j - x) <= r_square)
                OLED_Draw_Point(j, i, color);
}

void OLED_Draw_Circle_Covered(uint16_t x, uint16_t y, float r, uint16_t color)
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
    int16_t y_r_sin_begin = y - r * sinf(angle_begin / 180.0f * PI) + 0.5;
    int16_t x_r_cos_end = x + r * cosf(angle_end / 180.0f * PI) + 0.5;
    int16_t y_r_sin_end = y - r * sinf(angle_end / 180.0f * PI) + 0.5;

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

    uint32_t distance_square;
    for (uint16_t i = y_begin; i <= y_end; i++)
        for (uint16_t j = x_begin; j <= x_end; j++)
        {
            distance_square = (i - y) * (i - y) + (j - x) * (j - x);
            if (distance_square <= r_square_out && distance_square >= r_square_in)
            {
                int16_t angle = atan2f(y - i, j - x) / PI * 180.0f + 0.5;
                while (angle < angle_begin)
                    angle += 360;
                if (angle <= angle_end)
                    OLED_Draw_Point(j, i, color);
            }
        }
}

void OLED_Draw_Char(uint16_t x, uint16_t y, uint8_t ch, uint16_t color, uint16_t back_color, uint8_t sizey, uint8_t cover)
{
    // ch = ch - ' ';
    // uint8_t sizex = sizey / 2;

    // OLED_Draw(x, y, x + sizex - 1, y + sizey - 1); // 设置光标位置
    // for (uint16_t i = 0; i < sizey; i++)
    // {
    //     uint8_t ch_line;
    //     if (sizey == 12)
    //         ch_line = ascii_1206[ch][i]; // 调用6x12字体
    //     else if (sizey == 16)
    //         ch_line = ascii_1608[ch][i]; // 调用8x16字体
    //     else if (sizey == 24)
    //         ch_line = ascii_2412[ch][i]; // 调用12x24字体
    //     else if (sizey == 32)
    //         ch_line = ascii_3216[ch][i]; // 调用16x32字体
    //     else
    //         return;
    //     uint8_t line_count = 0;
    //     for (uint8_t ch_point = 0; ch_point < 8; ch_point++)
    //     {
    //         if (ch_line & (0x01 << ch_point))
    //             OLED_Write_Data_16(color);
    //         else
    //             OLED_Write_Data_16(color);
    //         if (line_count++ == sizex)
    //             break;
    //     }
    // }

    uint8_t temp, sizex, t, m = 0;
    uint16_t i, TypefaceNum; // 一个字符所占字节大小
    uint16_t x0 = x;
    sizex = sizey / 2;
    TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
    ch = ch - ' ';                                 // 得到偏移后的值
    OLED_Draw(x, y, x + sizex - 1, y + sizey - 1); // 设置光标位置
    for (i = 0; i < TypefaceNum; i++)
    {
        if (sizey == 12)
            temp = ascii_1206[ch][i]; // 调用6x12字体
        else if (sizey == 16)
            temp = ascii_1608[ch][i]; // 调用8x16字体
        else if (sizey == 24)
            temp = ascii_2412[ch][i]; // 调用12x24字体
        else if (sizey == 32)
            temp = ascii_3216[ch][i]; // 调用16x32字体
        else
            return;
        for (t = 0; t < 8; t++)
        {
            if (cover) // 非叠加模式
            {
                if (temp & (0x01 << t))
                    OLED_Write_Data_16(color);
                else
                    OLED_Write_Data_16(back_color);
                m++;
                if (m % sizex == 0)
                {
                    m = 0;
                    break;
                }
            }
            else // 叠加模式
            {
                if (temp & (0x01 << t))
                    OLED_Draw_Point(x, y, color); // 画一个点
                x++;
                if ((x - x0) == sizex)
                {
                    x = x0;
                    y++;
                    break;
                }
            }
        }
    }
}

void OLED_Draw_Int(uint16_t x, uint16_t y, int num, uint16_t color, uint16_t back_color, uint8_t sizey, uint8_t cover)
{
    uint8_t sizex = sizey / 2;
    uint8_t num_buf[10];
    uint8_t num_len = 0;
    if (num == 0)
    {
        num_buf[0] = '0';
        num_len = 1;
    }
    else
    {
        while (num)
        {
            num_buf[num_len++] = num % 10 + '0';
            num /= 10;
        }
    }
    for (uint8_t i = 0; i < num_len; i++)
        OLED_Draw_Char(x + sizex * i, y, num_buf[num_len - i - 1], color, back_color, sizey, cover);
}