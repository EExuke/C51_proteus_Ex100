//-----------------------------------------------------------------
// ADC0832模数转换程序
//-----------------------------------------------------------------
#include <intrins.h>
#include <reg51.h>
#define INT8U unsigned char
#define INT16U unsigned int
sbit CS =	P2^5;
sbit CLK =	P2^6;
sbit DIO =	P2^7;
//-----------------------------------------------------------------
// 获取AD转换结果 ( 0通道 )
//-----------------------------------------------------------------
INT8U Get_CHx_AD_Value(INT8U ch)
{


}