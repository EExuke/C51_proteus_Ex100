//-----------------------------------------------------------------
//  名称: 三端可调正电压稳压器LM317应用测试
//-----------------------------------------------------------------
//  说明: 本例运行时,通过两个按键可实现1.5V~9.0V的直流电压步进调节,
//		  步进值为0.5V,输出电压值将同时显示在7406驱动的数码管上.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit K1 = P1^0;
sbit K2 = P1^4;
//0-9的数码管段码,最后3位是黑屏及"dC"的段码,索引为10,11,12
code INT8U SEG_CODE[] =
{ 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF,0xA1,0xC6};
//显示缓冲(初始时显示DC 1.5V
INT8U Disp_Buff[] = {11,12,10,1,5,0};
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x) {INT8U t; while(x--) for(t = 0; t<120; t++);}
//------------------------------------------------------------------
// 主程序
//------------------------------------------------------------------
void main() 
{ 


} 

//-----------------------------------------------------------------
// T0定时器溢出中断控制数码管显示
//-----------------------------------------------------------------
void T0_Refresh_DSY()  interrupt 1
{


}