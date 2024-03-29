//-----------------------------------------------------------------
//  名称: 用数/模转换器DAC0808实现可选档位的数字步进调压
//-----------------------------------------------------------------
//  说明: 程序运行时,通过K1,K2按键可按照设定的步长,递增/递减调节电压.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U  unsigned char
#define INT16U unsigned int
//调压按键操作定义
#define K1_DOWN() (P3 & (1<<3)) == 0x00	//递增按键按下
#define K2_DOWN() (P3 & (1<<6)) == 0x00	//递减按键按下
//SW1步进档位0-4档所对应的步进值数组
float dw[] = {0.02, 0.50, 1.00, 1.50, 2.50};
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x){INT8U t; while(x--) for(t = 0; t < 120; t++);}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() 
{
	INT8U i,pre_Key = 0xFF; 		//上次按键历史记录
	INT8U SW1_Val,step;				//SW1所在位置值,当前步进值
	INT16U d = 0;  					//等待输出给DAC的值(低8位有效)
	P2 = 0x00;						//初始时输出0.00v
	while(1) 
	{





	}
}