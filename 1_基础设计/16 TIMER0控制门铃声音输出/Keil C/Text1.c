//-----------------------------------------------------------------
//  名称: TIMER0控制门铃声音输出
//-----------------------------------------------------------------
//  说明: 按下按键时蜂鸣器发出叮咚的门铃声
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit Key = P1^7;
sbit DoorBell =  P3^0; 
INT16U p = 0; 
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//------------------------------------------------------------------
// T0中断
//------------------------------------------------------------------
void Timer0_ISR() interrupt 1
{
	DoorBell = ~DoorBell;
	p++;
	//如果需要声音拖得更长，可调整400和800，频率可调整700和1000
	//高音
	if (p < 800)
	{
		TH0 = (8192 - 380)/32;
		TL0 = (8192 - 380)%32;
	}
	//低音
	else if (p < 1200)
	{
		TH0 = (8192 - 1200)/32;
		TL0 = (8192 - 1200)%32;
	}	
	//关闭
	else
	{
		TR0 = 0;
		p = 0;
	}
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() 
{ 
	IE = 0x82;					//使能T0中断
	TMOD = 0x00;				//T0工作于方式0
	TH0 = (8192 - 380)/32;		//初始时定时700μs
	TL0 = (8192 - 380)%32;
	while(1)
	{
		if (Key == 0)			//按下K1时启动定时器
		{
			delay_ms(10);		//延时消抖
			if (Key == 0)
			{
				while(!Key);
				TR0 = 1;		//启动T0
			}
		}
	}
}