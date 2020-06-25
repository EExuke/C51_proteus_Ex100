//-----------------------------------------------------------------
// 名称: MAX6675头文件
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U   unsigned char
#define INT16U  unsigned int
#define INT32U  unsigned long
//MAX6675 SPI接口引脚定义
sbit  CS  =  P1^0;			//片选控制引脚
sbit  CLK =  P1^1;			//串行时钟引脚
sbit  SO  =  P1^2;			//串行数据引脚
extern INT8U K_Couple_ON;
//MAX6675初始化函数及读取温度数据函数
void   MAX6675_Init(); 
INT16U MAX6675_Read();