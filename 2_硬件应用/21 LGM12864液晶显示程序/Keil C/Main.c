//-----------------------------------------------------------------
//  名称:LGM12864(KS0108)液晶显示程序
//-----------------------------------------------------------------
//  说明:开机时系统从EPROM 2764中读取画面并显示到12864LCD	
//			
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <absacc.h>
#define INT8U 	unsigned char
#define INT16U	unsigned int
//12864LCD相关函数
void LCD_Initialize();
void Display_A_Char(INT8U,INT8U,INT8U *);
void Display_A_WORD(INT8U,INT8U,INT8U *);
void Display_A_WORD_String(INT8U,INT8U,INT8U,INT8U *); 
void Display_Image(INT8U,INT8U,INT8U,INT8U,INT8U * );
//汉字点阵,Zimo软件取模设置:黑体小四号,黑反相,纵向取模,字节倒序
INT8U code Word_String[] = 	//"开机画面测试程序"的点阵数据
{
/*--  文字:  开  --*/
0xC0,0xC6,0xC6,0xC6,0xFE,0xFE,0xC6,0xC6,0xC6,0xFE,0xFE,0xC6,0xC6,0xC6,0xC0,0x00,
0x00,0x20,0x60,0x38,0x1F,0x07,0x00,0x00,0x00,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,
/*--  文字:  机  --*/
0x18,0x98,0xFF,0xFF,0x98,0x18,0x00,0xFE,0xFE,0x06,0x06,0xFE,0xFE,0x00,0x00,0x00,
0x06,0x03,0x7F,0x7F,0x01,0x23,0x70,0x3F,0x0F,0x00,0x00,0x3F,0x7F,0x60,0x70,0x00,
/*--  文字:  画  --*/
0x00,0xE6,0xE6,0x06,0xF6,0xF6,0x96,0xF6,0x96,0xF6,0xF6,0x06,0xE6,0xE6,0x00,0x00,
0x00,0x3F,0x3F,0x30,0x37,0x37,0x34,0x37,0x34,0x37,0x37,0x30,0x7F,0x7F,0x00,0x00,
/*--  文字:  面  --*/
0x06,0xF6,0xF6,0x36,0xF6,0xF6,0xBE,0xBE,0xF6,0xF6,0x36,0x36,0xF6,0xF6,0x06,0x00,
0x00,0x7F,0x7F,0x30,0x3F,0x3F,0x34,0x34,0x3F,0x3F,0x30,0x30,0x7F,0x7F,0x00,0x00,
/*--  文字:  测  --*/
0x00,0x66,0xCC,0x00,0xFE,0x06,0xF6,0x06,0xFE,0x00,0xFC,0x00,0xFF,0xFF,0x00,0x00,
0x00,0x70,0x1E,0x00,0x63,0x38,0x0F,0x00,0x1B,0x30,0x07,0x60,0x7F,0x3F,0x00,0x00,
/*--  文字:  试  --*/
0x60,0x62,0xEE,0xEC,0x00,0xD8,0xD8,0xD8,0xD8,0xFF,0xFF,0x18,0x1B,0x1E,0x18,0x00,
0x00,0x00,0x3F,0x3F,0x18,0x30,0x3F,0x1F,0x18,0x18,0x07,0x1F,0x30,0x78,0x38,0x00,
/*--  文字:  程  --*/
0x64,0x64,0xFC,0xFE,0x66,0x66,0x00,0xBE,0xBE,0xB6,0xB6,0xB6,0xBE,0xBE,0x00,0x00,
0x0C,0x06,0x7F,0x7F,0x03,0x06,0x60,0x6D,0x6D,0x7F,0x7F,0x6D,0x6D,0x6D,0x60,0x00,
/*--  文字:  序  --*/
0x00,0xFE,0xFE,0x06,0x06,0x36,0x36,0x77,0xF7,0xB6,0xF6,0x76,0x36,0x06,0x00,0x00,
0x60,0x3F,0x1F,0x00,0x03,0x03,0x63,0x63,0x7F,0x3F,0x03,0x03,0x07,0x07,0x00,0x00
};

//-----------------------------------------------------------------
// 烧写到EPROM2764的屏幕图像数据,宽度x高度=128x40 (共128*40/8 = 640字节)
// (在ZIMO软件中取模时,注意纵向取模,字节倒序)
//-----------------------------------------------------------------
////INT8U code Start_Screen_Image[] = {
//0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
//0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
//0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
//0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
//0x03,0x03,0x03,0x03,0x03,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFC,0x02,0x02,
//0xE2,0x12,0x0A,0x4A,0xEA,0x0A,0x0A,0x12,0xE2,0x02,0x02,0x02,0x82,0xC2,0xE2,0xC2,
//0x82,0x02,0x02,0x02,0xFC,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,
//0x00,0x00,0xFF,0x00,0xFF,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x0F,0x00,0x00,0xFF,
//0xFF,0xC0,0xE0,0x40,0xE0,0xA0,0x44,0x04,0x90,0xF0,0xE0,0x00,0xC0,0xFC,0xFE,0xFE,
//0x27,0x23,0x21,0x61,0x21,0x22,0x3E,0x00,0x00,0x00,0xF8,0xF8,0x9C,0x8C,0x0C,0x0C,
//0x0C,0x98,0x00,0x00,0x7C,0xFA,0x63,0xE1,0x80,0x00,0x00,0x00,0x1C,0x00,0x00,0x80,
//0x40,0x40,0x40,0xC0,0x80,0x80,0x00,0x00,0x00,0xC0,0xF0,0xFC,0xFE,0xBE,0xBE,0x3E,
//0xBE,0xBC,0x1C,0x40,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x7F,0x80,0x90,
//0xAB,0x94,0x88,0x88,0x8B,0x88,0x88,0x94,0xAB,0x90,0x80,0x81,0x81,0x8F,0x8F,0x8F,
//0x81,0x81,0x80,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x3F,0x00,
//0x00,0x00,0x03,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0xFB,
//0xFF,0xFF,0xFF,0xF1,0xF2,0xF2,0xE4,0xFE,0xFD,0xFF,0xFF,0xFC,0xFF,0xFF,0xFF,0xF7,
//0xC4,0x08,0x08,0x00,0x00,0x88,0xFC,0xFF,0xFC,0xF2,0xC7,0xFF,0x61,0xE1,0xC4,0xC0,
//0x41,0xC1,0xF0,0xF8,0xF8,0xE7,0x8F,0x8F,0xCD,0x8C,0xC4,0xE0,0xF8,0x68,0x07,0x00,
//0x08,0x08,0x00,0xF8,0x08,0xFF,0xE0,0xE0,0xF0,0xFF,0xFF,0xFF,0xFF,0xF9,0xDC,0x54,
//0xC1,0xE1,0xC8,0x80,0x80,0xFF,0x00,0x00,0x00,0x03,0xC0,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,
//0xE0,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,
//0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,
//0xFF,0x7C,0xF8,0xF8,0xF8,0xFF,0xFF,0xFF,0xFF,0x3F,0x7F,0xFF,0xFF,0xFC,0xF8,0xF9,
//0xFF,0x7F,0x3F,0x3F,0x7F,0x7F,0x7B,0x7B,0xF9,0xF9,0xF8,0x38,0xB8,0x78,0x78,0x78,
//0x78,0xFC,0xFC,0xFE,0x7F,0x7F,0x3F,0x3F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,
//0x00,0xFF,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0xE0,0x00,0x00,0xFC,0x00,0x00,0xFF,0x00,
//0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,
//0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF1,0xE0,0xEE,0xDF,0xDF,0xFF,0xEE,
//0xC5,0xF4,0xF5,0xF0,0xFF,0xFF,0xFF,0xDF,0xCF,0xE7,0xF8,0xF8,0xF1,0xE7,0xCF,0xFF,
//0xFF,0xC0,0xFF,0xFF,0xFF,0xFF,0x9F,0x80,0xFF,0xFF,0xF6,0xF1,0xE4,0xD3,0xD5,0xC6,
//0xD6,0xD1,0xFF,0x97,0x90,0xD5,0xF0,0xF0,0xF0,0xD0,0xD7,0xFF,0xFF,0xFF,0xFF,0xFF,
//0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,
//0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,
//0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,
//0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF
//} ;
 
//显示缓冲,因本例中RAM限制,仅定义为64字节
INT8U DisplayBuffer[64];
//-----------------------------------------------------------------
// 从2764EPROM中读取数据填充显示缓冲
//-----------------------------------------------------------------
void Read_Image_Data_From_EPROM(INT16U offset)
{

}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{

}