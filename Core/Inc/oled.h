// 绘图方式:
// 1. 调用 OLED_Modify_Region() 函数设置要编辑的矩形区域
// 2. 调用 OLED_Write_Data_16() 发送每点的 2 字节颜色值

#ifndef _OLED_H_
#define _OLED_H_

#define OLED_Size 240

#include "stm32f1xx_hal.h"
#include "spi.h"
#include "math.h"
#include "font.h"

// GPIO
// PC0: BLK
// PC1: CS
// PC2: DC
// PC3: RES

void OLED_Init(void);

void OLED_Write_Cmd(uint8_t cmd);       // 写入命令
void OLED_Write_Data_8(uint8_t data);   // 写入 1 字节数据
void OLED_Write_Data_16(uint16_t data); // 写入 2 字节数据

#define WHITE      0xFFFF
#define BLACK      0x0000
#define BLUE       0x001F
#define BRED       0XF81F
#define GRED       0XFFE0
#define GBLUE      0X07FF
#define RED        0xF800
#define MAGENTA    0xF81F
#define GREEN      0x07E0
#define CYAN       0x7FFF
#define YELLOW     0xFFE0
#define BROWN      0XBC40 // 棕色
#define BRRED      0XFC07 // 棕红色
#define GRAY       0X8430 // 灰色
#define DARKBLUE   0X01CF // 深蓝色
#define LIGHTBLUE  0X7D7C // 浅蓝色
#define GRAYBLUE   0X5458 // 灰蓝色
#define LIGHTGREEN 0X841F // 浅绿色
#define LGRAY      0XC618 // 浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE  0XA651 // 浅灰蓝色(中间层颜色)
#define LBBLUE     0X2B12 // 浅棕蓝色(选择条目的反色)

void OLED_Clear();                                                                                                          // 清屏
void OLED_Fill(uint16_t x_begin, uint16_t y_begin, uint16_t x_end, uint16_t y_end, uint16_t color);                         // 填充矩形区域
void OLED_Draw_Point(uint16_t x, uint16_t y, uint16_t color);                                                               // 画一个点
void OLED_Draw_Line(uint16_t x_begin, uint16_t y_begin, uint16_t x_end, uint16_t y_end, float width, uint16_t color);       // 画一条线
void OLED_Draw_Rectangle(uint16_t x_begin, uint16_t y_begin, uint16_t x_end, uint16_t y_end, uint16_t color);               // 画一个矩形
void OLED_Draw_Circle_Covered(uint16_t x, uint16_t y, float r, uint16_t color);                                             // 画一个圆
void OLED_Draw_Circle(uint16_t x, uint16_t y, float r, uint16_t color);                                                     // 画一个圆
void OLED_Draw_Radiu(uint16_t x, uint16_t y, float r, float width, int16_t angle_begin, int16_t angle_end, uint16_t color); // 画一个扇形
void OLED_Draw_Char(uint16_t x,uint16_t y,uint8_t ch, uint16_t color,uint16_t back_color,uint8_t sizey,uint8_t cover);      // 画一个字符
void OLED_Draw_Int(uint16_t x,uint16_t y,int num, uint16_t color,uint16_t back_color,uint8_t sizey,uint8_t cover);          // 画一个整数

#endif