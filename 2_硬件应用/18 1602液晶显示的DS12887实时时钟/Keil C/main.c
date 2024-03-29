//-----------------------------------------------------------------
//  名称: 1602液晶显示DS12887实时时钟
//-----------------------------------------------------------------
//  说明: 主程序读取DS12887实时时钟,刷新显示在20*4LCD.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <absacc.h>
#include <string.h>
#define INT8U  unsigned char
#define INT16U unsigned int
//-----------------------------------------------------------------
#define LCD_CMD_WR			0xFF00	//写命令(RW,RS=00)
#define LCD_DATA_WR			0xFF01	//写数据(RW,RS=01)
#define LCD_BUSY_RD			0xFF02	//读忙状态
#define LCD_DATA_RD			0xFF03	//读数据
#define LCD_CLS				0xFF01	//清屏
#define LCD_HOME			0xFF02	//光标归位
#define LCD_SETMODE			0xFF04	//设置模式
#define LCD_SETVISIBLE		0xFF08	//开显示
#define LCD_SHIFT			0xFF10	//移位方式
#define LCD_SETFUNCTION		0xFF20	//功能设置
#define LCD_SETCGADDR		0xFF40	//设置CGRAM地址
#define LCD_SETDDADDR		0xFF80	//设置DDRAM地址
//-----------------------------------------------------------------
extern INT8U DateTime[];
extern code char WEEK[][4];
extern void DS12887_Init();
extern void Get_DateTime();
char buf1[] = "DATE: 0000-00-00";
char buf2[] = "TIME: 00-00-00 AM";
char buf3[] = "WEEK: XXX"; 
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
	do {
		LCD_Status = XBYTE[LCD_BUSY_RD];
	} while (LCD_Status);
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
// 在指定行列位置显示字节符
//-----------------------------------------------------------------
void LCD_ShowString(INT8U r, INT8U c, char *s)
{
	INT8U i = 0;
	INT8U DDRAM[] = {0x80,0xC0,0x94,0xD4}; //LM044L各行首地址(共4行)
	Write_LCD_Command(DDRAM[r] | c);
	while (s[i] && i < 20) Write_LCD_Data(s[i++]);
	for (; i < 20; i++) Write_LCD_Data(' ');
}

//-----------------------------------------------------------------
// LCD初始化
//-----------------------------------------------------------------
void LCD_Initialise()
{
	Write_LCD_Command(0x38);
	Write_LCD_Command(0x0C);
}

//-----------------------------------------------------------------
// 日期与时间值转换为数字字符(BCD->DEC)
//-----------------------------------------------------------------
void Format_DateTime(INT8U d, INT8U *a)
{
	*a = (d >> 4) + '0';
	*(a+1) = (d & 0x0F) + '0';
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	DS12887_Init();									//DS12887初始化
	LCD_Initialise();								//LCD初始化
	LCD_ShowString(0,0,"DS12887 Real Clock");
	while(1)
	{
		Get_DateTime();

		Format_DateTime(DateTime[6], buf1 + 6);
		Format_DateTime(DateTime[5], buf1 + 8);
		Format_DateTime(DateTime[4], buf1 + 11);
		Format_DateTime(DateTime[3], buf1 + 14);
		LCD_ShowString(1, 0, buf1);

		Format_DateTime(DateTime[2] & 0x7F, buf2 + 6);
		Format_DateTime(DateTime[1], buf2 + 9);
		Format_DateTime(DateTime[0], buf2 + 12);

		if (DateTime[2] & 0x80) {
			buf2[15] = 'P';
		} else {
			buf2[15] = 'A';
		}
		LCD_ShowString(2, 0, buf2);

		strcpy(buf3 + 6, WEEK[DateTime[7] - 1]);
		LCD_ShowString(3, 0, buf3);
		delay_ms(50);
	}
}

