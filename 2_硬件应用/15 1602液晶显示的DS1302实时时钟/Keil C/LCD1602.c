//-----------------------------------------------------------------
// 液晶控制与显示程序
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit RS = P2^0;		//寄存器选择线
sbit RW = P2^1;		//读/写控制线
sbit EN = P2^2;		//使能控制线
//-----------------------------------------------------------------
// 延时
//-----------------------------------------------------------------
void delay_ms(INT16U ms)
{
	INT8U i; while(ms--) for(i = 0; i < 120; i++);
}

//-----------------------------------------------------------------
// 忙等待
//-----------------------------------------------------------------
void Busy_Wait()
{
	INT8U LCD_Status;						//液晶状态字节变量
	do
	{	

	} while (LCD_Status & 0x80);			//液晶忙继续循环
}

//-----------------------------------------------------------------
// 写LCD命令
//-----------------------------------------------------------------
void Write_LCD_Command(INT8U cmd)
{


}

//-----------------------------------------------------------------
// 发送数据
//-----------------------------------------------------------------
void Write_LCD_Data(INT8U dat)
{


}

//-----------------------------------------------------------------
// LCD初始化
//-----------------------------------------------------------------
void Initialize_LCD()
{
	Write_LCD_Command(0x38); delay_ms(1);	//置功能,8位,双行,5*7
	Write_LCD_Command(0x01); delay_ms(1);	//清屏
	Write_LCD_Command(0x06); delay_ms(1);	//字符进入模式:屏幕不动,字符后移
	Write_LCD_Command(0x0C); delay_ms(1);	//显示开,关光标
}

//-----------------------------------------------------------------
// 显示字符串
//-----------------------------------------------------------------
void LCD_ShowString(INT8U r, INT8U c,INT8U *str)
{
	INT8U i = 0;
	code INT8U DDRAM[] = {0x80,0xC0};		//1602LCD两行的起始DDRAM地址
	Write_LCD_Command(DDRAM[r] | c);		//设置显示起始位置
	for ( i = 0; i < 16 ;i++)				//输出字符串
	  Write_LCD_Data(str[i]);
}