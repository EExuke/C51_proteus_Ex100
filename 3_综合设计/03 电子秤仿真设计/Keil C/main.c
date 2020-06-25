//-----------------------------------------------------------------
//  名称: 电子秤仿真设计
//-----------------------------------------------------------------
//  说明: 本例运行时,LCD显示当前压力(未转换为重量),所输入的价格将
//		直接与该值相乘,LCD显示计算后的应付金额.		
//
//-----------------------------------------------------------------
#define INT8U	unsigned char
#define INT16U	unsigned int
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
extern void Sounder();						//蜂鸣器输出
extern void KeyBoard_Handle();				//键盘处理及金额计算与显示函数
extern void Compute_and_show_sum();
//液晶相关函数
extern void LCD_Initialize();
extern void LCD_ShowString(INT8U r, INT8U c,INT8U *str);
extern INT8U Get_CHx_AD_Value(INT8U ch); 	//ADC0832 A/D转换函数
extern void delay_ms(INT16U x);	  			//延时函数
extern char disp_buffer_W[];				//液晶显示缓冲(重量)
//模数转换结果,上次转换结果,压力换算结果
volatile int AD_Result, Pre_Result = 0, Pressure_Value = 0;
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	LCD_Initialize();					//初始化LCD
	//第一行显示P:W:标志(价格/重量),其中"P:"后面空8格
	LCD_ShowString(0,0,(char*)"P:        W:");
	LCD_ShowString(1,0,(char*)"SUM($):");//第二行显示SUM标志(金额)
	while(1)
	{	





	}
}
