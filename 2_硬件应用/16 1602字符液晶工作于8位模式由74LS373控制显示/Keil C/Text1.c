//-----------------------------------------------------------------
//  名称: 1602字符液晶工作于8位模式由74LS373控制显示
//-----------------------------------------------------------------
//  说明: LCD1602液晶通过扩展接口驱动显示,液晶屏上下两行分别滚动显示
//        指定的字符串.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <absacc.h>
#include <string.h>
#define INT8U  unsigned char
#define INT16U unsigned int
#define LCD_CMD_WR			0x00	//写命令(RW,RS=00)
#define LCD_DATA_WR			0x01	//写数据(RW,RS=01)
#define LCD_BUSY_RD			0x02	//读忙状态(RW,RS=10)
#define LCD_DATA_RD			0x03	//读数据
#define LCD_CLS				0x01	//清屏
#define LCD_HOME			0x02	//光标归位
#define LCD_SETMODE			0x04	//设置模式
#define LCD_SETVISIBLE		0x08	//开显示
#define LCD_SHIFT			0x10	//移位方式
#define LCD_SETFUNCTION		0x20	//功能设置
#define LCD_SETCGADDR		0x40	//设置CGRAM地址
#define LCD_SETDDADDR		0x80	//设置DDRAM地址
//待显示字符串,前面添加了若干空格
code char *s1 = "                 LCD1602 TEST....";
code char *s2 = "                 Port Extension..";
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// LCD忙等待
//-----------------------------------------------------------------
void Busy_Wait()
{
	INT8U LCD_Status;
	do
	{
		LCD_Status = XBYTE[LCD_BUSY_RD];
	} while (LCD_Status & 0x80);
	
}

//-----------------------------------------------------------------
// 写LCD命令
//-----------------------------------------------------------------
void Write_LCD_Command(INT8U cmd)
{
	XBYTE[LCD_CMD_WR] = cmd;
	Busy_Wait();
}

//-----------------------------------------------------------------
// 发送数据
//-----------------------------------------------------------------
void Write_LCD_Data(INT8U dat)
{
	XBYTE[LCD_DATA_WR] = dat;
	Busy_Wait();
}


//-----------------------------------------------------------------
// 在指定行列位置显示字符串
//-----------------------------------------------------------------
void LCD_Show_String(INT8U r, INT8U c, char *s)
{
	INT8U i = 0;
	INT8U DDRAM[] = {LCD_SETDDADDR,LCD_SETDDADDR|0x40}; //即0x80,0xC0
	Write_LCD_Command(DDRAM[r] | c);
	while (s[i] && i < 16) Write_LCD_Data(s[i++]);
	for (; i < 16; i++) Write_LCD_Data(' ');
}

//-----------------------------------------------------------------
// LCD初始化
//-----------------------------------------------------------------
void LCD_Initialise()
{
	Write_LCD_Command(0x38);	Write_LCD_Command(0x0C);
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	INT8U i;
	LCD_Initialise();					//LCD初始化
	while(1)
	{
		//line 1
		for (i = 0; i <= strlen(s1) - 16; i++)
		{
			LCD_Show_String(0, 0, s1+i);
			delay_ms(20);
		}
		//line 2
		for (i = 0; i <= strlen(s2) - 16; i++)
		{
			LCD_Show_String(1, 0, s2+i);
			delay_ms(100);
		}
	}
}
