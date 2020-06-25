//-----------------------------------------------------------------
//  名称:12864LCD显示驱动程序 (不带字库)
//-----------------------------------------------------------------
#include "89c51rd2.h"
#include <intrins.h>
#define INT8U unsigned char
#define INT16U  unsigned int
#define	LCD_DB_PORT    P0     //液晶DB0-DB7
#define LCD_START_ROW  0xC0	  //起始行
#define LCD_PAGE       0xB8	  //页指令
#define LCD_COL        0x40	  //列指令
//液晶引脚定义
sbit	DI  = P2^0 ;
sbit	RW  = P2^1 ;
sbit	E   = P2^2 ;
sbit	CS1 = P2^3 ;
sbit	CS2	= P2^4 ;
sbit	RST = P2^5 ;
//-----------------------------------------------------------------
// 检查LCD是否忙
//-----------------------------------------------------------------
bit LCD_Check_Busy()
{


}

//-----------------------------------------------------------------
// 向LCD发送命令
//-----------------------------------------------------------------
void LCD_Write_Command( INT8U c)
{


}

//-----------------------------------------------------------------
// 向LCD发送数据
//-----------------------------------------------------------------
void LCD_Write_Data(INT8U d )
{


}

//-----------------------------------------------------------------
// 初始化LCD
//-----------------------------------------------------------------
void LCD_Initialize()
{


}

//-----------------------------------------------------------------
//
// 通用显示函数
// 
// 从第P页第L列开始显示W个字节数据,数据在r所指向的缓冲
// 每字节8位是垂直显示的,高位在下,低位在上
// 每个8*128的矩形区域为一页
// 整个LCD又由64x64的左半屏和64x64的右半屏构成
//-----------------------------------------------------------------
void Common_Show(INT8U P,INT8U L,INT8U W,INT8U *r)
{








}

//-----------------------------------------------------------------
// 显示一个16×16点阵汉字
//-----------------------------------------------------------------
void Display_A_WORD(INT8U P,INT8U L,INT8U *M)
{


}

//-----------------------------------------------------------------
// 显示一串16×16点阵汉字
//-----------------------------------------------------------------
void Display_A_WORD_String(INT8U P,INT8U L,INT8U C,INT8U *M)
{



}