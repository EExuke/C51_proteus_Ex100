//-----------------------------------------------------------------
//  名称: 用M145026与M145027设计的无线收发系统
//-----------------------------------------------------------------
//  说明: 系统运行时,发射端按键号将显示在LCD上.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#define INT8U  unsigned char
#define INT16U unsigned int
extern void LCD_Initialize();
extern void LCD_ShowString(INT8U r, INT8U c,INT8U *str);
INT8U LCD_Disp_Buff[21];
sbit Rec_Pin	= P3^3;			//接收信号通知
sbit BEEP		= P1^7;			//蜂鸣器定义
//-----------------------------------------------------------------
// 声音输出	  
//-----------------------------------------------------------------
void Sounder()
{	INT8U i, j = 40;
	for ( i = 0; i < 30; i++) { BEEP = ~BEEP; while (--j); }
}
	
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	int Rec_Code;
	LCD_Initialize();			//初始化LCD
	LCD_ShowString(0,0,(INT8U*)"[Remote Control]");
	LCD_ShowString(1,0,(INT8U*)"----------------");
	LCD_ShowString(2,0,(INT8U*)"RECEIVED KEYNO:");	
	while (1)
	{




	}
}