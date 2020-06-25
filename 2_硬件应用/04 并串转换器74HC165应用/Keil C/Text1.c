//-----------------------------------------------------------------
//  名称: 并串转换器74HC165应用
//-----------------------------------------------------------------
//  说明:切换连接到并串转换器74HC165的拨码开关,该芯片将并行数据
//		 以串行方式发送到单片机,显示在P0端口.
//		 本例给出了:(1)通过模拟时序接收
//		 			(2)通过串口(RXD/TXD)接收
//		 两种方式的程序实现.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#define INT8U  unsigned char
#define INT16U unsigned int
//并串转换器相关引脚定义
sbit DAT = P3^0;			//74HC165串行数据输入引脚
sbit CLK = P3^1;			//74HC165移位时钟引脚
sbit SPL = P3^2;			//Shift/Load
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// 模拟时序串行读取1字节(高位优先)
//-----------------------------------------------------------------
INT8U Serial_Input()
{
	INT16U i, d = 0x00;
		for(i = 0x80; i != 0x00; i >>= 1)	//1个字节
		{
			if (DAT)
				d |= i;				//读取1位
			CLK = 0; CLK = 1;		//输出时钟脉冲
		}
		return d;
}

//-----------------------------------------------------------------
// 主程序 
//-----------------------------------------------------------------
void main()
{  
	//通过模拟时序读取串行数据的代码
	while(1)
	{ 
		SPL = 0;				//置数（Load），读入并行输入口的8位数据
		SPL = 1;				//移位（Shift），并口输入被封锁，串行转换开始
		P0 = Serial_Input();	//串行接收1字节，显示在P0端口（与拨码开关对应）
		delay_ms(20);
	}
	//通过串口读取串行数据的代码
	//	SCON = 0x10;		//设为串口模式0,允许串口接收
	//	while(1)
	//	{ 
	//		SPL = 0;		//置数(Load)，读入并行输入口的8位数据
	//		SPL = 1;		//移位(Shift)，并口输入被封锁，串行转换开始
	//		while (RI == 0);//等待接收中断标志位被硬件置位
	//		RI = 0;			//软件清0接收中断标志位
	//		P0 = SBUF;		//接收到的字节显示在P0端口(与拨码开关对应)
	//		delay_ms(20);	//延时
	//	}
}