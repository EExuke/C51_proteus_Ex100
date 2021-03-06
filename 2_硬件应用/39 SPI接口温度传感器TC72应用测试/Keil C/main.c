//-----------------------------------------------------------------
//	名称: SPI接口温度传感器TC72应用测试
//-----------------------------------------------------------------
//	说明: 本例运行时,单片机将持续从TC72传感器读取温度数据并转换为
//		  浮点型字符串送LCD显示(内置SPI接口需要在实物电路测试)
//
//-----------------------------------------------------------------
#include "REG51RX2.H"
#include <intrins.h>
#include <stdio.h>
#include <math.h>
#define INT8U	unsigned char
#define INT16U	unsigned int
//SPI使能与禁用(注意TC72是高电平使能,低电平禁用)
#define SPI_EN() P1 |=	(1<<4)
#define SPI_DI() P1 &= ~(1<<4)
//TC72寄存器地址定义
#define TC72_CTRL		0x80	//控制寄存器
#define TC72_TEMP_LSB	0x01	//温度低字节
#define TC72_TEMP_MSB	0x02	//温度高字节
#define TC72_MANU_ID	0x03	//制造商ID
//SPI接口引脚定义(模拟方式)
sbit SCK = P3^4;				//串行时钟
sbit CE  = P3^5;				//片选
sbit SDI  = P3^6;				//串行数据输入
sbit SDO  = P3^7;				//串行数据输出
//内置SPI寄存器及寄存器位定义
//SPCON C3h SPI Control	SPR2 SPEN SSDIS MSTR CPOL CPHA SPR1 SPR0
//SPSTA C4h SPI Status	SPIF WCOL SSERR MODF - - - -
//SPDAT C5h SPI Data	SPD7 SPD6 SPD5  SPD4 SPD3 SPD2 SPD1 SPD0
sfr	SPCON	 =	0xC3;
sfr	SPSTA	 =	0xC4;
sfr	SPDAT	 =	0xC5;
extern void Initialize_LCD();
extern void LCD_ShowString(INT8U r, INT8U c,INT8U *str);
extern void delay_ms(INT16U x);
INT8U T[2];						//两字节原始温度数据
float TempX = 0.0;				//浮点温度值
//-----------------------------------------------------------------
// SPI主机初始化
//-----------------------------------------------------------------
void SPI_MasterInit()
{


}

//-----------------------------------------------------------------
// SPI数据传输
//-----------------------------------------------------------------
INT8U SPI_SendData(INT8U dat)

{
	




}

//-----------------------------------------------------------------
// 从当前地址读取一字节数据(模拟方式)
//-----------------------------------------------------------------
INT8U ReadByte()
{



}

//-----------------------------------------------------------------
// 向当前地址写入一字节数据(模拟方式)
//-----------------------------------------------------------------
void WriteByte(INT8U dat)
{


}

//-----------------------------------------------------------------
// 向TC72写入两字节(地址,数据)(模拟方式)
//-----------------------------------------------------------------
void Write_TC72(INT8U addr, INT8U dat)
{



}

//-----------------------------------------------------------------
// 写TC72配置数据
//-----------------------------------------------------------------
void Config_TC72()
{


}

//-----------------------------------------------------------------
// 从TC72读取两字节温度数据并转换为浮点温度值
//-----------------------------------------------------------------
void Read_TC72_Temperature()
{



}

//-----------------------------------------------------------------
// 主程序	 
//-----------------------------------------------------------------
void main()
{


}