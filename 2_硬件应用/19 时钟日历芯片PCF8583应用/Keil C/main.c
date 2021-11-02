//-----------------------------------------------------------------
//  名称: PCF8583实时时钟显示程序
//-----------------------------------------------------------------
//  说明: 从PCF8583中读取日历时钟数据并刷新显示于LCD.
//
//-----------------------------------------------------------------
#define INT8U  unsigned char
#define INT16U unsigned int
#include <stdio.h>
#include <reg51.h>
#include <intrins.h>
#include <string.h>
#include "PCF8583.h"

extern void LCD_ShowString(INT8U r, INT8U c,INT8U *str);
extern void Initialize_LCD();
extern void delay_ms(INT16U ms);
extern INT8U DateTime[7];
extern char WEEK[][4];
char buf1[12] = "DATE: 00/00";
char buf2[16] = "TIME: 00-00-00";
char disp_buff[10];

//-----------------------------------------------------------------
// 日期与时间值转换为数字字符
//-----------------------------------------------------------------
void Format_DateTime(INT8U d, INT8U *a)
{ 
	*a = (d >> 4) + '0'; *(a+1) = (d & 0x0F) + '0';
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	Initialize_LCD();
	LCD_ShowString(0,0,(INT8U *)"*PCF8583 Clock**");
	while (1)
	{
		GetDateTime();
		// month/day
		Format_DateTime(DateTime[4], buf1+6);
		Format_DateTime(DateTime[3], buf1+9);
		LCD_ShowString(1, 0, buf1);
		// hh-mm-ss
		Format_DateTime(DateTime[2], buf1+6);
		Format_DateTime(DateTime[1], buf1+9);
		Format_DateTime(DateTime[0], buf1+12);
		LCD_ShowString(2, 0, buf2);
		// WEEK: wkd
		sprintf(disp_buff, "WEEK: %3s", WEEK[DateTime[6] -1]);
		LCD_ShowString(3, 0, buff);
		delay_ms(50);
	}
}
