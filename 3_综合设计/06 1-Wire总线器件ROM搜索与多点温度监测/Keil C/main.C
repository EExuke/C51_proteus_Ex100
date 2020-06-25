//-----------------------------------------------------------------
//  名称: 1-Wire总线器件ROM搜索程序及多点DS18B20监测
//-----------------------------------------------------------------
//  说明: 本例自动搜索所有1-Wire总线器件,遇到温度传感器时显示其温度值
//        否则仅显示其ROMCODE编码及当前搜索到的器件总数.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#define INT8U  unsigned char
#define INT16U unsigned int
#include "1-Wire.h"
extern void LCD_Initialize();
extern void LCD_ShowString(INT8U r, INT8U c,INT8U *str);
extern void Search_ALL_ROM();
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{



}