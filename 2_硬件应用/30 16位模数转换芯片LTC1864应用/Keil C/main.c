//-----------------------------------------------------------------
//	名称: 16位模数转换芯片LTC1864应用
//-----------------------------------------------------------------
//	说明: 外部输入模拟电压经LTC1864模/数转换后显示在LCD屏上.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#include <math.h>
#define INT8U	unsigned char
#define INT16U	unsigned int
sbit SDO = P3^0;	//串行数据输出引脚
sbit SCK = P3^2;	//串行时钟引脚
sbit CONV = P3^4;	//转换控制引脚
extern void Initialize_LCD();
extern void LCD_ShowString(INT8U r, INT8U c,INT8U *str);
extern void delay_ms(INT16U x);
//-----------------------------------------------------------------
// 读取LTC1864模数转换值(16位,2字节)
//-----------------------------------------------------------------
INT16U Read_ADC()
{

}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	char dispBuff[17];
	Initialize_LCD();
	LCD_ShowString(0,0,"LTC1864 A/D Test");
	while(1)
	{	



	}
}