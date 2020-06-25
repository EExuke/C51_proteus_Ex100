//-----------------------------------------------------------------
// 名称：24C1024 IIC读写程序
//-----------------------------------------------------------------
#define INT8U  unsigned char
#define INT16U unsigned int
#define INT32U unsigned long
#include "89c51rd2.h"
#include <intrins.h>
sbit SCL = P3^2;		//串行时钟
sbit SDA = P3^3;		//串行数据
#include "I2C.h"		//IIC总线通用宏及函数
//-----------------------------------------------------------------
// 从24C1024读取多字节
//-----------------------------------------------------------------
INT8U IIC_ReadBytes(INT8U Slave,INT32U Mem_address,INT8U *Buf,INT8U N)
{

}