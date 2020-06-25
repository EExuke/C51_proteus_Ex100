//-----------------------------------------------------------------
//  名称: ULN2803驱动点阵屏仿电梯数字滚动显示
//-----------------------------------------------------------------
//  说明: 本例模拟了电梯显示屏上下滚动显示楼层的效果,当目标楼层大于
//   	  当前楼层时将向上滚动显示,反之则向下滚动显示.目标楼层到达时
//	 点阵保持稳定显示.
//
//-----------------------------------------------------------------
#include <reg51.h> 
#include <intrins.h>
#define INT8   signed   char
#define INT8U  unsigned char
#define INT16U unsigned int
//数字0~9的点阵字节(每个数字8字节)
INT8U code Table_OF_Digits[]=
{  
	0x00,0x3C,0x66,0x42,0x42,0x66,0x3C,0x00,	//0
	0x00,0x08,0x38,0x08,0x08,0x08,0x3E,0x00,	//1
	0x00,0x3C,0x42,0x04,0x08,0x32,0x7E,0x00,	//2
	0x00,0x3C,0x42,0x1C,0x02,0x42,0x3C,0x00,	//3
	0x00,0x0C,0x14,0x24,0x44,0x3C,0x0C,0x00,	//4
	0x00,0x7E,0x40,0x7C,0x02,0x42,0x3C,0x00,	//5
	0x00,0x3C,0x40,0x7C,0x42,0x42,0x3C,0x00,	//6
	0x00,0x7E,0x44,0x08,0x10,0x10,0x10,0x00,	//7
	0x00,0x3C,0x42,0x24,0x5C,0x42,0x3C,0x00,	//8
	0x00,0x38,0x46,0x42,0x3E,0x06,0x3C,0x00 	//9
};
INT8 offset = 0;		//用于产生滚动效果的取点阵字节偏移变量
INT8U Current_Level = 1;//当前楼层号
INT8U Dest_Level = 1;	//目标楼层号
INT8U r = 0, x = 0;		//点阵显示取字节索引及刷新遍数控制变量
//------------------------------------------------------------------
// 主程序
//------------------------------------------------------------------
void main() 
{  


 
} 

//------------------------------------------------------------------
// T0中断
//------------------------------------------------------------------
void LED_Screen_Display() interrupt 1 
{


}