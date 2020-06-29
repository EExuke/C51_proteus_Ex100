//-----------------------------------------------------------------
//	名称: LCD1602液晶驱动程序
//-----------------------------------------------------------------
#include "LCD1602-4bit.h"
#define delay5us() {_nop_();_nop_();_nop_();_nop_();_nop_();}
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT8U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// 液晶忙等待
//-----------------------------------------------------------------
void LCD_Busy_Wait()
{
	INT8U Hi,Lo ;
	do
	{
		LCD_PORT |= 0xF0;
		RS = 0; RW = 1;
		EN = 1; delay5us(); Hi = LCD_PORT; delay5us(); EN = 0; delay5us();
		EN = 1; delay5us(); Lo = LCD_PORT; delay5us(); EN = 0; delay5us();
	} while( Hi & 0x80);
}

//-----------------------------------------------------------------
// 写液晶命令
//-----------------------------------------------------------------
void Write_LCD_Command(INT8U cmd)
{
	LCD_Busy_Wait();
	LCD_PORT = cmd & 0xF0 | 0x04;
	delay5us(); EN = 0; delay5us();
	LCD_PORT = cmd << 4 | 0x04;
	delay5us(); EN = 0; delay5us();
}

//-----------------------------------------------------------------
// 向液晶写数据
//-----------------------------------------------------------------
void Write_LCD_Data(INT8U dat)
{
	LCD_Busy_Wait();
	LCD_PORT = dat & 0xF0 | 0x05;
	delay5us(); EN = 0; delay5us();
	LCD_PORT = dat << 4 | 0x05;
	delay5us(); EN = 0; delay5us();
}

//-----------------------------------------------------------------
// 液晶初始化
//-----------------------------------------------------------------
void Initialize_LCD()
{
	LCD_PORT = 0xFF;//初始时液晶端口全部置为高电平
	LCD_PORT = 0x24;//设置4位模式,并置EN,RW,RS = 100(4),准备写命令寄存器
	EN = 0;			//上一行EN已置为1,完成了控制命令写入,此行EN重置为低电平
	//以下每条命令都需要通过分别发送高4位与低四位完成
	Write_LCD_Command(0x28); delay_ms(15);	//功能设置(4Bit,双行,5x7点阵)
	Write_LCD_Command(0x0C); delay_ms(15);	//开显示
	Write_LCD_Command(0x06); delay_ms(15);	//模式设置
	Write_LCD_Command(0x01); delay_ms(15);	//清屏
	Write_LCD_Command(0x02); delay_ms(15);	//光标定位于右上角
}

//-----------------------------------------------------------------
// 在指定位置显示字符串
//-----------------------------------------------------------------
void LCD_ShowString(INT8U r, INT8U c,char *str)
{
	INT8U i = 0;
	code INT8U DDRAM[] = {0x80, 0xC0};
	Write_LCD_Command(DDRAM[r] | c);
	for (i = 0; i < 16 && str[i] != '\0'; i++)
	{
		Write_LCD_Data(str[i]);
	}
	
}

