//-----------------------------------------------------------------
// 名称: MMC卡块读写程序
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <absacc.h>
#define INT8U  unsigned char
#define INT16U unsigned int
#define INT32U unsigned long
//SPI接口存储器引脚定义
sbit CS  = P3^2;				//片选
sbit DI  = P3^3;				//串行数据输入
sbit DO  = P3^4;				//串行数据输出
sbit CLK = P3^5;				//串行时钟控制脚
//MMC卡使能与禁止操作
#define MMC_CS_EN() CS = 0
#define MMC_CS_DI() CS = 1
//MMC卡操作命令帧(6字节,48位)
INT8U cmd[6] = { 0x00,0x00,0x00,0x00,0x00,0x00 };
extern void delay_ms(INT16U);
//块字节读写缓冲
#define Block_Date &XBYTE[0x0000]
#define delay_10us() {_nop_();_nop_();_nop_();_nop_();_nop_();\
						_nop_();_nop_();_nop_();_nop_();_nop_();}
//-----------------------------------------------------------------
// 打开SPI
//-----------------------------------------------------------------
void OpenSPI() { CS = 1; CLK = 0; }
//-----------------------------------------------------------------
// 从当前地址读取一字节数据
//-----------------------------------------------------------------
INT8U getcSPI()
{


}

//-----------------------------------------------------------------
// 向当前地址写入一字节数据
//-----------------------------------------------------------------
void putcSPI(INT8U dat)
{


}

//-----------------------------------------------------------------
// MMC命令帧清0
//-----------------------------------------------------------------
void clear_cmd_frame()
{


}

//-----------------------------------------------------------------
// 写MMC命令
//-----------------------------------------------------------------
INT8U MMC_Write_Command(INT8U *cmd_frame)
{


}

//-----------------------------------------------------------------
// MMC初始化
//-----------------------------------------------------------------
INT8U MMC_Initialise()
{


}

//-----------------------------------------------------------------
// 从指定的块地址读取单个块字节数据
//-----------------------------------------------------------------
INT8U MMC_Read_Block(INT32U address)
{
	INT16U i;
	clear_cmd_frame();						//命令帧清0
	cmd[0] = 0x51;							//设置CMD17(0x51....0xFF)(读单个块)
	cmd[5] = 0xFF;
	address = address<<9;					//地址<<9位,取512的整数倍
	cmd[1]  = address>>24;					//将address分解到
	cmd[2]  = address>>16;					//四字节的命令帧参数中
	cmd[3]  = address>>8;
	cmd[4]  = address>>0;
	if(MMC_Write_Command(cmd) != 0x00) return 0; //发送CMD17
	while(getcSPI() != 0xFE) _nop_();		//等待数据接受开始(0xFE)
	for(i = 0;i < 512; i++)					//读取块数据(512字节)
	  XBYTE[i] = getcSPI();
	getcSPI();getcSPI();					//取走2字节的CRC
	return 1; 
}
	
//-----------------------------------------------------------------
// 向指定的块地址开始写入单个块字节数据
//-----------------------------------------------------------------
INT8U MMC_Write_Block(INT32U address)
{
	INT16U i,Dout;
	clear_cmd_frame();						//命令帧清0
	cmd[0] = 0x58;							//设置CMD24(0x58....0xFF)(写单个块)
	cmd[5] = 0xFF;
	address = address<<9;					//地址<<9位,取512的整数倍
	cmd[1]  = address>>24;					//将address分解到
	cmd[2]  = address>>16;					//四字节的命令帧参数中
	cmd[3]  = address>>8;
	cmd[4]  = address>>0;
	if(MMC_Write_Command(cmd) != 0x00) return 0; //发送CMD24
	putcSPI(0xFF);							//发送填冲字节
	putcSPI(0xFE);							//发送数据开始标志0xFE
	//将块读写缓冲Block_bytes中的512字节数据写入MMC
	for(i = 0;i < 512; i++) putcSPI(XBYTE[i]);
	putcSPI(0xFF);							//写入2字节CRC(未计算)
	putcSPI(0xFF);
	Dout = getcSPI() & 0x1F;				//读取返回数据中的低5位
	if(Dout != 0x05) return 0;				//如果未能读到XXX0 0101则写入失败
	while(getcSPI() == 0x00) _nop_(); 		//忙等待
	return 1;
}