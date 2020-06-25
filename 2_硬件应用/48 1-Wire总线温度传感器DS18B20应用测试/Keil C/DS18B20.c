//-----------------------------------------------------------------
//  名称: DS18B20驱动程序
//  (源代码中所标延时值均为11.0592MHz晶振下的延时)
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit DQ = P3^4;						//DS18B20 DQ引脚定义
INT8U Temp_Value[] = {0x00,0x00};	//从DS18B20读取的温度值
//-----------------------------------------------------------------
// 延时宏定义及函数定义
//-----------------------------------------------------------------
#define delay4us(); 	{ _nop_();_nop_();_nop_();_nop_(); } 
void delay_ms(INT16U x)	{ INT8U i; while( x-- ) for(i = 0; i<120; i++);}
void DelayX(INT16U x)	{ while (--x); }
//-----------------------------------------------------------------
// 初始化DS18B20(注意在选定的振荡器频率11.0592MHz下设置符合时序规定的延时)
//-----------------------------------------------------------------
INT8U Init_DS18B20()
{


}

//-----------------------------------------------------------------
// 读一字节 
//-----------------------------------------------------------------
INT8U ReadOneByte()
{


}

//-----------------------------------------------------------------
// 写一字节 
//-----------------------------------------------------------------
void WriteOneByte(INT8U dat)
{


}

//-----------------------------------------------------------------
// 读取温度值 
//-----------------------------------------------------------------
INT8U Read_Temperature()
{


}