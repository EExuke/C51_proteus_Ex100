//-----------------------------------------------------------------
//  名称: TIMER0控制交通指示灯
//-----------------------------------------------------------------
//  说明: 东西向绿灯亮5秒后,黄灯闪烁,闪烁5次后亮红灯,
//		红灯亮后,南北向由红灯变为绿灯,5秒后南北向黄灯闪烁, 
//		闪烁5次后亮红灯,东西向绿灯亮,如此往复.
//		本例将时间设得较短是为了调试的时候能较快的观察到运行效果.
//				
//-----------------------------------------------------------------
#include <reg51.h>
#define INT8U unsigned char
#define INT16U  unsigned int
sbit	RED_A		=  P0^0;	//东西向指示灯
sbit	YELLOW_A	=  P0^1;
sbit	GREEN_A		=  P0^2; 
sbit	RED_B		=  P0^3;	//南北向指示灯
sbit	YELLOW_B	=  P0^4;
sbit	GREEN_B		=  P0^5;
//延时倍数,闪烁次数,操作类型变量
INT8U Time_Count = 0, Flash_Count = 0, Operation_Type = 1; 
//-----------------------------------------------------------------
// T0中断子程序	 
//-----------------------------------------------------------------
void T0_INT () interrupt 1
{
	TH0	= - 50000 / 256;
	TL0 = - 50000 % 256;
	switch (Operation_Type)
	{
		case 1:  //东西向绿灯与南北向红灯亮5秒
			  	 RED_A = 0; YELLOW_A = 0; GREEN_A =1;
				 RED_B = 1; YELLOW_B = 0; GREEN_B =0;
				 //5s后切换操作（50ms * 100 = 5s）
				 if (++Time_Count != 100)
				 	return;
				 Time_Count = 0;
				 Operation_Type	= 2;	//下一操作类型
				 break;
		case 2:  //东西向黄灯开始闪烁,绿灯关闭
				 if (++Time_Count != 8)
				 	return;
				 Time_Count = 0;
				 YELLOW_A = !YELLOW_A; GREEN_A = 0;
				 //闪烁5次
				 if (++Flash_Count != 10)
				 	return;
				 Flash_Count = 0;
				 Operation_Type	= 3;	//下一操作类型
				 break;
		case 3:  //东西向红灯与南北向绿灯亮5秒
				 RED_A = 1; YELLOW_A = 0; GREEN_A =0;
				 RED_B = 0; YELLOW_B = 0; GREEN_B =1;
				 //5s后切换操作（50ms * 100 = 5s）
				 if (++Time_Count != 100)
				 	return;
				 Time_Count = 0;
				 Operation_Type	= 4;	//下一操作类型
				 break;
		case 4:  //南北向黄灯开始闪烁
				 if (++Time_Count != 8)
				 	return;
				 Time_Count = 0;
				 YELLOW_B = !YELLOW_B; GREEN_B = 0;
				 //闪烁5次
				 if (++Flash_Count != 10)
				 	return;
				 Flash_Count = 0;
				 Operation_Type	= 1;	//下一操作类型
	}
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	TMOD = 0x01;	//定时器0工作在方式1
	IE = 0x82;		//允许定时器0中断
	TR0 = 1;		//启动定时器0
	while(1);		//等待中断
}
