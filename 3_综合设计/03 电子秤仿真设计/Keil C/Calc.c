//-----------------------------------------------------------------
// 名称: 电子秤价格输入与金额计算程序
//-----------------------------------------------------------------
#define INT8U  unsigned char
#define INT16U unsigned int
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//蜂鸣器定义
#define BEEP() 		P2 ^= (1<<3)
//按键判断及按键键值
#define Key_Pressed (P1 & (1<<4))	//DA(P1.4)为高电平时有键按下
#define Key_NO		(P1 & 0x0F)		//解码器输出线连接在P1低四位
//键盘字符表(其中注意2,5,8后各保留一个空格)
code char KEY_CHAR_TABLE[] = "012 345 678 9.C";
//液晶显示字符串函数
extern void LCD_ShowString(INT8U r, INT8U c,char *str);
//LCD显示输出缓冲(价格/重量/金额)的最大长度
//因为要预留结束标志,实际串长比定义少1位
#define PLEN	7
#define WLEN	4
#define SUMLEN  10
//LCD显示输出缓冲(价格/重量/金额)
char disp_buffer_P[PLEN];
char disp_buffer_W[WLEN];
char disp_buffer_SUM[SUMLEN];
//价格输入缓冲索引
INT8U NumberPtr = 0;
//-----------------------------------------------------------------
// 蜂鸣器输出
//-----------------------------------------------------------------
void Sounder()
{ 
	INT8U i,j;
	for (i = 0; i < 200; i++) { BEEP(); j = 70; while (--j); }
}

//-----------------------------------------------------------------
// 处理运算并显示金额
//-----------------------------------------------------------------
void Compute_and_show_sum()
{ 


}

//-----------------------------------------------------------------
// 处理键盘操作
//-----------------------------------------------------------------
void KeyBoard_Handle()
{


}