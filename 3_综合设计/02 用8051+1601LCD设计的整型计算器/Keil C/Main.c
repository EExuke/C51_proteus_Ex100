//-----------------------------------------------------------------
// 名称:用8051+1601LCD设计的整型计算器
//-----------------------------------------------------------------
// 说明: 本例由LABCENTER ELECTRONICS公司提供,原始程序由C与汇编混合
//		编写,本例将所有代码全部改编成了C程序代码并简化了设计.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"
#define INT8U  unsigned char
#define INT16U unsigned int
static long a,b;			//当前运算符的前后两个操作数
static char CurrKeyChar;	//当前按键字符
static char Last_OP;		//最近输入的操作符
static char Last_Char;		//所输入的前一字符
static char result;			//当前运算的结果状态
//显示缓冲,数字输入缓冲及数字输入缓冲区索引定义
static char xdata outputbuffer[MAX_DISPLAY_CHAR+1];
static char xdata NumberStr[MAX_DISPLAY_CHAR+1];
static char xdata NumberIdx;
//-----------------------------------------------------------------
// 检查待显示数据是否越界
//-----------------------------------------------------------------
int calc_chkerror(long num) { return labs(num) <= 9999999? OK : ERROR;}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() 
{  


}	

//-----------------------------------------------------------------
// 根据运算符按键进行运算处理
//-----------------------------------------------------------------
void Operator_Process(char OP)
{ 



}