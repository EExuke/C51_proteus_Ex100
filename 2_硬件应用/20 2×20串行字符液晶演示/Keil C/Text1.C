//-----------------------------------------------------------------
//  名称: 2×20串行液晶演示
//-----------------------------------------------------------------
//  说明: 程序执行时串行液晶上显示:Serial LCD DEMO
//        当光标在第二行产闪烁时,虚拟终端中输入的字符将显示在
//        LCD上,按下退格键时光标左移,按下回车时清屏.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U  unsigned char
#define INT16U unsigned int
INT8U code prompts[] = "  Serial LCD DEMO  ";
INT8U i, c;
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT8U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// 通过串口向LCD写入一字节
//-----------------------------------------------------------------
void putc_to_LCD(INT8U c)
{
	SBUF = c;
	while (TI == 0);
	TI = 0;
}

//-----------------------------------------------------------------
// 从虚拟终端读取一字节数据
//-----------------------------------------------------------------
INT8U Getc_from_Terminal()
{
	while (RI == 0);
	RI = 0;
	return SBUF;
}

//-----------------------------------------------------------------
// 写LCD命令
//-----------------------------------------------------------------
void Write_LCD_Command(INT8U comm)
{
	putc_to_LCD(0xFE); //前导字节
	putc_to_LCD(comm); //命令字节
}

//-----------------------------------------------------------------
// 在液晶上显示字符串
//-----------------------------------------------------------------
void LCD_Show_String(INT8U r, INT8U c, char *s)
{
	INT8U code DDRAM[] = {0x08, 0xC0};
	Write_LCD_Command(DDRAM[r] | c);
	i = 0;
	while (s[i] && i<20) {
		putc_to_LCD(s[i++]);
		delay_ms(5);
	}
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	TMOD = 0x20;    //timer 1 work on mode 2
	TH1 = 0xFD;    //bord rate 9600b/s, 11.0592MHz
	TL1 = 0xFD;
	SCON = 0x50;   //Serial work on mode 1, allow recv
	RI = 0; TI = 0;    //clear flags
	TR1 = 1;    //timer 1 enable
	delay_ms(200);
	LCD_Show_String(0, 0, prompts);
	Write_LCD_Command(0xC0); //光标定位到第2行
	Write_LCD_Command(0x0D); //show cursor
	delay_ms(120);
	while (1) {
		c = Getc_from_Terminal();
		if (c == 0x0D) {    //回车
			Write_LCD_Command(0x01);
			continue;
		}
		if (c == 0x08) {    //退格
			Write_LCD_Command(0x10);
			continue;
		}
		putc_to_LCD(c);
		delay_ms(200);
	}
}
