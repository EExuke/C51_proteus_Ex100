//-----------------------------------------------------------------
//	名称: ADC0809模数转换与显示
//-----------------------------------------------------------------
//	说明: ADC0809采样通道3输入的模拟量,转换后的结果显示在数码管上.
//				
//-----------------------------------------------------------------
#include <reg51.h>
#define INT8U unsigned char
#define INT16U	unsigned int
//共阳数码管段码定义
INT8U code SEG_CODE[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90 };
//ADC0809引脚定义
sbit OE	= P1^0;			//输出使能
sbit EOC = P1^1;		//转换结束
sbit ST	= P1^2;			//启动转换
sbit CLK = P1^3;		//采样时钟
//-----------------------------------------------------------------
// 延时子程序
//-----------------------------------------------------------------
void delay_ms(INT16U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// 显示转换结果
//-----------------------------------------------------------------
void Display_Result(INT8U AD)
{	

}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{ 

}

//-----------------------------------------------------------------
// T0定时器中断给ADC0809提供时钟信号
//-----------------------------------------------------------------
void Timer0_INT() interrupt 1
{

}