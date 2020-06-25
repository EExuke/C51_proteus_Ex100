//-----------------------------------------------------------------
// 名称: LED模拟交通灯
//-----------------------------------------------------------------
// 说明: 东西向绿灯亮若干秒后,黄灯闪烁,闪烁5次后亮红灯,
//		红灯亮后,南北向由红灯变为绿灯,若干秒后南北向黄灯闪烁, 
//		闪烁5次后亮红灯,东西向绿灯亮,如此往复.
//		本例将时间设得较短是为了调试的时候能较快的观察到运行效果.
//	
//-----------------------------------------------------------------
#include <reg51.h>
#define INT8U	unsigned char
#define INT16U	unsigned int
sbit	RED_A = P0^0;	//东西向指示灯
sbit	YELLOW_A = P0^1;
sbit	GREEN_A = P0^2; 
sbit	RED_B = P0^3;	//南北向指示灯
sbit	YELLOW_B = P0^4;
sbit	GREEN_B = P0^5;
//闪烁次数及操作类型变量定义
INT8U Flash_Count = 0, Operation_Type = 1;
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// 交通灯切换子程序
//-----------------------------------------------------------------
void Traffic_Light()
{
    switch (Operation_Type)
    {
        case 1://东西向绿灯与南北向红灯亮
               RED_A = 1; YELLOW_A = 1; GREEN_A = 0;
               RED_B = 0; YELLOW_B = 1; GREEN_B = 1;
               delay_ms(2000);        //延时；
               Operation_Type = 2;     //下一操作；
               break;
        case 2://东西向黄灯开始闪烁,绿灯关闭
               delay_ms(300);                   //黄闪烁延时；
               YELLOW_A = ~YELLOW_A;GREEN_A = 1;
               if(++Flash_Count != 10) return;    //闪烁5；
               Flash_Count = 0;
               Operation_Type = 3;     //下一操作；
               break;
        case 3://东西向红灯与南北向绿灯亮
               RED_A = 0; YELLOW_A = 1; GREEN_A = 1;
               RED_B = 1; YELLOW_B = 1; GREEN_B = 0;
               delay_ms(2000);        //延时；
               Operation_Type = 4;     //下一操作；
               break;
        case 4://南北向黄灯开始闪烁,绿灯关闭；
               delay_ms(300);                   //黄闪烁延时；
               YELLOW_B = ~YELLOW_B;GREEN_B = 1;
               if(++Flash_Count != 10) return;    //闪烁5；
               Flash_Count = 0;
               Operation_Type = 1;     //回到第一操作；
     }
}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
    while(1)
    {
        Traffic_Light();
    }
}