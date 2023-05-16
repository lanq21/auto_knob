#include "oled.h"

uint8_t *spi_buf; // SPI 发送缓冲区
uint16_t *graph_buf; // OLED 显示缓冲区

void Exange(uint16_t *a, uint16_t *b)
{
    uint16_t temp = *a;
    *a = *b;
    *b = temp;
}

// OLED 初始化
void OLED_Init(void)
{
    spi_buf = (uint8_t *)malloc(sizeof(uint8_t) * OLED_Size * OLED_Size * 2 + 100);
    graph_buf = (uint16_t *)malloc(sizeof(uint16_t) * OLED_Size * OLED_Size);
    for (int i = 0; i < OLED_Size * OLED_Size; i++)
        graph_buf[i] = BLACK;

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
    if (OLED_Direction == 0)
        OLED_Write_Data_8(0x08);
    else if (OLED_Direction == 1)
        OLED_Write_Data_8(0xC8);
    else if (OLED_Direction == 2)
        OLED_Write_Data_8(0x68);
    else
        OLED_Write_Data_8(0xA8);

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
    spi_buf[0] = cmd;
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, spi_buf, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
}

// SPI 发送数据
void OLED_Write_Data_8(uint8_t data)
{
    spi_buf[0] = data;
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, spi_buf, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}

void OLED_Write_Data_16(uint16_t data)
{
    spi_buf[0] = data >> 8;
    spi_buf[1] = data;
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, spi_buf, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}

void OLED_Draw(uint16_t x_begin, uint16_t y_begin, uint16_t x_end, uint16_t y_end)
{
    if (x_begin > x_end) Exange(&x_begin, &x_end);
    if (y_begin > y_end) Exange(&y_begin, &y_end);
    x_end = x_end >= OLED_Size ? OLED_Size-1 : x_end;
    y_end = y_end >= OLED_Size ? OLED_Size-1 : y_end;

    OLED_Write_Cmd(0x2a); // 设置列地址
    OLED_Write_Data_16(x_begin);
    OLED_Write_Data_16(x_end);
    OLED_Write_Cmd(0x2b); // 设置行地址
    OLED_Write_Data_16(y_begin);
    OLED_Write_Data_16(y_end);
    OLED_Write_Cmd(0x2c); // 储存器写

    uint16_t count = 0;
    for (uint16_t i = y_begin; i <= y_end; i++)
        for (uint16_t j = x_begin; j <= x_end; j++)
        {
            uint16_t color = graph_buf[i * OLED_Size + j];
            spi_buf[count++] = color >> 8;
            spi_buf[count++] = color;
        }
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, spi_buf, count, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}

// 清屏, 全部填充为黑色
void OLED_Clear()
{
    OLED_Fill(0, 0, OLED_Size-1, OLED_Size-1, BLACK);
}

// 填充矩形区域
void OLED_Fill(uint16_t x_begin, uint16_t y_begin, uint16_t x_end, uint16_t y_end, uint16_t color)
{
    for (uint16_t i = y_begin; i <= y_end; i++)
        for (uint16_t j = x_begin; j <= x_end; j++)
            graph_buf[i * (x_end - x_begin + 1) + j] = color;
    OLED_Draw(x_begin, y_begin, x_end, y_end);
}

// 画一个点
void OLED_Draw_Point(uint16_t x, uint16_t y, uint16_t color)
{
    graph_buf[y * OLED_Size + x] = color;
    OLED_Draw(x, y, x, y);
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
        uint16_t average = (y_min + y_max) / 2.0 + 0.5;
        y_min = (y_min > 0) ? ceil(y_min) : 0;
        y_max = (y_max < OLED_Size - 1) ? floor(y_max) : (OLED_Size - 1);
        if (y_min <= y_max)
        {
            for (uint16_t y = y_min; y <= y_max; y++)
            {
                if (base_axis == 0)
                    OLED_Draw_Point(x, y, color);
                else
                    OLED_Draw_Point(y, x, color);
            }
        }
        else
        {
            if (base_axis == 0)
                OLED_Draw_Point(x, average, color);
            else
                OLED_Draw_Point(average, x, color);
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

void OLED_Draw_Circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color)
{
}
