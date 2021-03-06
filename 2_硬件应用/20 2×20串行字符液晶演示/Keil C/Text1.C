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

}

//-----------------------------------------------------------------
// 从虚拟终端读取一字节数据
//-----------------------------------------------------------------
INT8U Getc_from_Terminal()
{

}

//-----------------------------------------------------------------
// 写LCD命令
//-----------------------------------------------------------------
void Write_LCD_Command(INT8U comm)
{

} 

//-----------------------------------------------------------------
// 在液晶上显示字符串
//-----------------------------------------------------------------
void LCD_Show_String(INT8U r, INT8U c, char *s)
{

} 

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{

}