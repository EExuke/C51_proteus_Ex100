//-----------------------------------------------------------------
// 名称: DS1621驱动程序
//-----------------------------------------------------------------
#define INT8U  unsigned char
#define INT16U unsigned int
#define INT32U unsigned long
#include <reg51.h>
#include <intrins.h>
#include <string.h>
#include <stdio.h>
sbit SCL = P2^6;					//IIC时钟线
sbit SDA = P2^7;					//IIC数据线
#include "I2C.h"					//IIC总线通用宏及函数
INT8U d[2] = {0x00,0x00};			//读取两字节温度数据
INT8U SET_CONFIG[] = { 0xAC,0x02 };	//写配置字节(命令及数据序列)
INT8U SET_TH[] =	 { 0xA1,0,0 };	//设置TH	(命令及数据序列)
INT8U SET_TL[] =	 { 0xA2,0,0 };	//设置TL	(命令及数据序列)
INT8U IIC_Start_CONV[]=  { 0xEE };	//启动转换	(命令,定义为数组以便统一编程)
//-----------------------------------------------------------------
// 向DS1621写入多字节
//-----------------------------------------------------------------
void Write_DS1621(INT8U Slave_Addr,INT8U *Buff, INT8U n)
{



}

//-----------------------------------------------------------------
// 读取温度
//-----------------------------------------------------------------
void Read_Temp(INT8U Slave_Addr)
{



}