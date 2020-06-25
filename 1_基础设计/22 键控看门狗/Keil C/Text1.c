//-----------------------------------------------------------------
//	名称: 键控看门狗
//-----------------------------------------------------------------
//	说明: 激活看门狗后喂狗,LED1点亮,LED2闪烁,如果不喂狗则复位,LED1闪烁.
//			本例单片机内置看门狗,启动看门狗只需对0xA6地址(WDTRST)写入
//			0x1E和0xE1,看门狗一旦启动将无法关闭,必需在16.3ms内重置,
//			否则会引起系统复位.
//-----------------------------------------------------------------
#include "89c51rd2.h"
#include <intrins.h>
#define INT8U	unsigned char
#define INT16U unsigned int
sbit LED1 = P0^0;	//LED1
sbit LED2 = P0^5;	//LED2
/*
mode X1 12 clock periods per peripheral clock cycle.
mode X2 6 clock periods per peripheral clock cycle.
WDTPRG|=0x00 (2^14 - 1) machine cycles,	16. 3 ms	@ FOSCA=12 MHz
WDTPRG|=0x01 (2^15 - 1) machine cycles,	32.7 ms		@ FOSCA=12 MHz
WDTPRG|=0x02 (2^16 - 1) machine cycles, 65. 5 ms	@ FOSCA=12 MHz
WDTPRG|=0x03 (2^17 - 1) machine cycles, 131 ms		@ FOSCA=12 MHz
WDTPRG|=0x04 (2^18 - 1) machine cycles, 262 ms		@ FOSCA=12 MHz
WDTPRG|=0x05 (2^19 - 1) machine cycles, 542 ms		@ FOSCA=12 MHz
WDTPRG|=0x06 (2^20 - 1) machine cycles, 1.05 s 		@ FOSCA=12 MHz
WDTPRG|=0x07 (2^21 - 1) machine cycles, 2.09 s 		@ FOSCA=12 MHz
*/
//-----------------------------------------------------------------
// 延时
//-----------------------------------------------------------------
void delay_ms(INT16U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// 主程序	 
//-----------------------------------------------------------------
void main()
{
	WDTPRG = 0x00;	 //看门狗编程：0x00；设S2，1，0 = 000 （16.3ms - 12MHZ）
	LED1 = 0;		 //启动时LED1点亮
	LED2 = 1;
	delay_ms(2000);
	TMOD = 0x01;	 //定时器模式1
	TH0	= (-15000 / 256);		//15ms定时
	TL0	= (-15000 % 256);
	TR0 = 1;		//启动定时器
	IT0 = 1;		//INT0下降沿触发
	IE = 0x83;		//使能INT0，T0中断并开总中断
	WDTRST = 0x1E;		//在程序初始化时激活WD
	WDTRST = 0xE1;
	while(1)
	{
		ET0 = 1;			//允许T0中断
		LED1 = 1;			//正常运行，关闭LED1
		LED2 = ~LED2; 		//LED2闪烁
		delay_ms(200);
	}
}

//-----------------------------------------------------------------
// INT0中断程序
//-----------------------------------------------------------------
void INT0_ISR() interrupt 0
{
	//用K1停止喂狗,观察系统是否重启,LED1是否又被点亮一次
	ET0 = 0;		//T0定时器中断禁止，即停止喂狗

}

//-----------------------------------------------------------------
// 定时器0中断程序
//-----------------------------------------------------------------
void TIMER0_ISR() interrupt 1
{
	TH0	= (-15000 / 256); 		//重置15ms定时
	TL0 = (-15000 % 256);
	WDTRST = 0x1E;			//喂狗指令（复位看门狗）
	WDTRST = 0xE1;
}