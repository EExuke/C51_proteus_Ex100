//-----------------------------------------------------------------
// 名称: PCF8583实时时钟驱动程序
//-----------------------------------------------------------------
#define INT8U  unsigned char
#define INT16U unsigned int
#include <reg51.h>
#include <intrins.h>
#include <string.h>
sbit SCL = P2^6;					//IIC时钟线
sbit SDA = P2^7;					//IIC数据线
#include "I2C.h"					//IIC总线通用宏及函数
#include "PCF8583.h"				//日期时钟芯片驱动程序头文件

//0,1,2,3,4,5,6分别对应周日,周一至六
char WEEK[][4] = {"SUN","MON","TUS","WEN","THU","FRI","SAT"};
//所读取的PCF8583数据及转换后的日期时间数据
INT8U PCF8583_DATA[5],DateTime[7];

//-----------------------------------------------------------------
// 从PCF8583指定地址读多字节到buf缓冲
//-----------------------------------------------------------------
void Read_PCF8583(INT8U addr,INT8U *buf,INT8U n)
{
	INT8U i=0;

	IIC_Start();
	IIC_WriteByte(PCF8583_ADDR_WR);
	IIC_WriteByte(addr);

	IIC_Start();
	IIC_WriteByte(PCF8583_ADDR_RD);
	for (i=0; i<n-1; i++) {
		buf[i] = IIC_ReadByte(); //主机读一字节
		IIC_Ack();    //主机发送应答
	}
	buf[n-1] = IIC_ReadByte(); //主机读取最后一字节
	IIC_NAck(); //主机发送非应答位
	IIC_Stop(); //IIC停止
}

//-----------------------------------------------------------------
// 读取7字节PCF8583时钟数据并整理到DateTime数组
//-----------------------------------------------------------------
void GetDateTime()
{
	//skip control byte 0x00 and 1/100s byte 0x01
	//read 5 byte from 0x02(sec) to PCF8583_DATA
	Read_PCF8583(0x02, PCF8583_DATA, 5);
	//format date data
	DateTime[0] = PCF8583_DATA[0]; //sec
	DateTime[1] = PCF8583_DATA[1]; //min
	DateTime[2] = PCF8583_DATA[2]; //hour
	DateTime[3] = PCF8583_DATA[3]; //day
	DateTime[4] = PCF8583_DATA[4]; //month
	DateTime[5] = PCF8583_DATA[3]; //year
	DateTime[6] = PCF8583_DATA[4]; //week
}
