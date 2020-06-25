//-----------------------------------------------------------------
//  名称:T6963C LCD图形滚动演示
//-----------------------------------------------------------------
//  说明:本例综合演示了T6963C液晶的图文显示功能: 包括图像显示,滚动,
//		反白.合上"图文"开关时显示一幅条形统计图.
//
//-----------------------------------------------------------------
#include <T6963C.h>
#include <stdio.h>
#define INT8U  unsigned char
#define INT16U unsigned int
extern void cls();								//清屏
extern INT8U LCD_Initialise();					//LCD初始化
extern INT8U LCD_Write_Command(INT8U cmd);		//写无参数的命令
extern INT8U LCD_Write_Command_P2(INT8U cmd,INT8U para1,INT8U para2); //写双参数命令
extern INT8U LCD_Write_Data(INT8U dat);			//写数据
extern void Set_LCD_POS(INT8U row, INT8U col);	//设置当前地址
extern void Line(INT8U x1,INT8U y1, INT8U x2,INT8U y2, bit Mode);//绘制线条
extern INT8U Display_Str_at_xy(INT8U x,INT8U y,char *fmt);	//显示字符串
extern INT8U code LCD_WIDTH;
extern INT8U code LCD_HEIGHT;
//按键定义
sbit S1 = P1^0 ;	//正常显示
sbit S2 = P1^1 ;	//反白
sbit S3 = P1^2 ;	//滚动
sbit S4 = P1^3 ;	//图文
//显示在LCD上的图像
INT8U code ImageX[] = { 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xF3,0xF9,0x8E,0x30,
0x1F,0xF8,0x00,0x00,0x00,0x30,0x38,0x70,0x00,0x30,0x78,0x78,0xC0,0x78,0xF0,0xCC,
0x31,0xB3,0x87,0xFF,0x00,0x00,0x00,0x00,0x00,0xF0,0x6C,0xD8,0x30,0xF0,0xCC,0xCC,
0xC0,0xCC,0xD8,0xCF,0xB1,0xB7,0x01,0x83,0x00,0x00,0x00,0x00,0x00,0x30,0xC1,0x8C,
0xFC,0x30,0xCC,0xCC,0xC1,0x8C,0xCC,0xDF,0xB1,0xBE,0x0D,0xFC,0x3F,0xFC,0x00,0x00,
0x00,0x30,0xF9,0x8C,0x78,0x30,0x0C,0xCC,0xC1,0x80,0xCC,0xFF,0x31,0xB1,0x86,0x30,
0x01,0x80,0x00,0x00,0x00,0x30,0xCD,0x8C,0x78,0x30,0x18,0x78,0xC1,0x80,0xCC,0xDF,
0xB3,0xFF,0x01,0xFE,0x01,0x80,0x00,0x00,0x00,0x30,0xCD,0x8C,0xFC,0x30,0x30,0xCC,
0xC1,0x80,0xCC,0xF6,0xF1,0xB6,0x00,0xFE,0x0D,0xB0,0x00,0x00,0x00,0x30,0xCD,0x8C,
0x30,0x30,0x60,0xCC,0xC1,0x8C,0xCC,0xC3,0x31,0xB0,0xC7,0xB6,0x1D,0xB8,0x00,0x00,
0x00,0x30,0xCC,0xD8,0x00,0x30,0xC0,0xCC,0xC0,0xCC,0xD8,0xCF,0x31,0xB3,0x86,0xFE,
0x19,0x9C,0x00,0x00,0x00,0x30,0x78,0x70,0x00,0x30,0xFC,0x78,0xFC,0x78,0xF0,0xC0,
0x33,0xB7,0x0C,0x6C,0x31,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0xF3,0x3C,0x0D,0xC7,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0x7F,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE3,0xBF,0xFF,0xFD,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,
0xE3,0xCE,0x7F,0xB5,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0x9E,0xFB,0xF5,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,
0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xFD,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFC,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0xFF,0xFF,0xFD,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x78,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xBF,0xFF,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x3F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xE7,0xFF,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFB,0xFE,0x7F,0xFE,0xFD,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFD,0xFB,0xFE,0x7F,0xFF,0xFD,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xF2,
0xFE,0x7F,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x0F,0xFF,
0xFF,0xFC,0xFF,0xF2,0x64,0x6F,0xFE,0x79,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0x00,0x00,0x07,0xFF,0xFF,0x80,0x00,0x00,0x38,0x7C,0xFC,0x1D,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x07,0xFF,0xFF,0x00,0x00,0x00,0x08,0x7C,0x7C,0x11,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x07,0xFF,0xFE,0x03,0x00,0x00,
0x00,0x3C,0x7C,0x1D,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x01,0xFD,
0x00,0x03,0x00,0x00,0x00,0x76,0x8F,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,
0x00,0x00,0x00,0x7F,0x01,0x88,0x00,0x00,0x00,0x30,0xFF,0xDD,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFB,0xFF,0xE0,0x00,0x00,0x00,0x7F,0x01,0xBC,0x00,0x00,0x00,0x20,0x1F,0xFD,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x7E,0x01,0xBC,0x00,0x00,
0x00,0x27,0x0F,0xFD,0xBF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x03,0x3E,
0x0C,0x3F,0x00,0x00,0x00,0x67,0xDF,0xFD,0xBF,0xFF,0xF7,0xDF,0xFF,0xFF,0xFF,0x80,
0x00,0x00,0x44,0x3E,0x21,0xFA,0x10,0x00,0x84,0x7F,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFE,0x00,0x00,0x0F,0xF0,0x7E,0x23,0xFF,0xE2,0x0C,0x04,0xFF,0xFF,0x7D,
0xBF,0xFF,0xFF,0xFD,0xFF,0xFF,0xFF,0xFF,0xC0,0x1F,0xFB,0x1F,0xEF,0xFF,0xFF,0x07,
0xBC,0xFF,0xFF,0xED,0xBF,0xFF,0xFF,0xFD,0xFF,0xFF,0xFF,0xFF,0xC0,0x1F,0xFC,0x0F,
0xE7,0xFF,0xFC,0x17,0xBC,0xFF,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF8,0x00,0x0E,0x9F,0xFF,0xFF,0xFC,0x7F,0xFE,0xFF,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0x80,0xD8,0x0F,0xF8,0xDE,0xFF,0xF7,0xFF,0xFF,0xFB,0xF9,0xFF,0xFD,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x88,0x0D,0xF8,0x4C,0xFF,0xFF,0xFF,0xFF,
0xFB,0x9F,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF8,0x00,0x0C,0x0D,
0x3F,0xFF,0xFF,0xFF,0xFF,0x1F,0x3F,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,
0x78,0x00,0x00,0x6C,0x3F,0xFF,0xFF,0xFF,0xCF,0x1E,0x7F,0xFD,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xE0,0x38,0x00,0x00,0x68,0x2F,0xFF,0xFC,0x7F,0xC0,0x9D,0xFF,0xFD,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x18,0x00,0x00,0x78,0x2F,0xFF,0xFF,0xFE,
0xC0,0xD9,0xFF,0xED,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x18,0x00,0x00,0x38,
0x2F,0xFF,0xFF,0xFE,0xF9,0xE9,0xFF,0xE9,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
0x18,0x00,0x00,0x08,0x2F,0xDF,0xFF,0xFF,0xF9,0xBF,0x0F,0xFD,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFE,0x00,0x18,0x00,0x00,0x08,0x2F,0x9F,0xFF,0xDF,0xA0,0x9F,0x0F,0xFD,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x18,0x00,0x00,0x08,0x20,0x9F,0xF9,0x9B,
0x00,0x9F,0x1F,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x78,0x00,0x00,0x08,
0x00,0x00,0x00,0x0F,0xB8,0xD8,0x1E,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,
0xF8,0x00,0x00,0x08,0x00,0x00,0x00,0x0F,0xB9,0x98,0x32,0xDD,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFC,0x03,0x10,0x00,0x00,0x08,0x00,0x00,0x1F,0xF0,0x79,0x1B,0xF3,0xFD,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x07,0x08,0x0C,0x00,0x08,0x00,0x80,0x3F,0x3C,
0x78,0x1B,0xB3,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x07,0xF8,0x20,0x10,0x08,
0x0D,0xE2,0xEE,0x78,0x38,0x07,0xBB,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFB,0xFE,0x03,
0xFF,0x00,0x18,0x18,0x81,0xE6,0x8C,0x01,0xE0,0x9F,0x93,0xED,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFE,0x03,0xF8,0x00,0x0C,0x18,0x01,0xC4,0x0C,0xC0,0xC0,0x18,0x03,0xFD,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x0F,0xF0,0x00,0x04,0x18,0x02,0xC0,0x0D,0xC0,
0x00,0x38,0x13,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x1F,0xF0,0x00,0x00,0x18,
0x00,0x42,0xE4,0x00,0x00,0x70,0x93,0xDD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDE,0xBF,
0xFC,0x3F,0xC0,0x30,0x21,0x00,0xE7,0x80,0xB8,0x13,0x93,0xCD,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x9E,0xBF,0xFE,0x67,0xE0,0x30,0x20,0x4C,0x6F,0x80,0x81,0x23,0xBB,0xFD,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFE,0x1E,0x3F,0xFF,0x00,0x60,0x34,0x00,0x0C,0x2C,0x00,
0xC1,0x63,0x9B,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFD,0x4E,0x1F,0x90,0x00,0x40,0x74,
0x00,0x3C,0xD0,0x08,0x44,0x60,0x07,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0x05,0x2F,
0x80,0x03,0x80,0xC0,0x00,0x00,0x17,0x00,0x00,0x04,0x00,0x09,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xAF,0x83,0xF8,0x0C,0x03,0x80,0x0E,0x1E,0x02,0x40,0x00,0x00,0x00,0x01,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xAF,0x83,0xF8,0x00,0x03,0x80,0x0E,0x00,0x8B,0x40,
0x00,0x00,0x00,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xC5,0xF8,0x00,0x03,0x80,
0x00,0x1C,0xF3,0xC0,0x00,0x00,0x02,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC1,0xEE,
0xF8,0x00,0x07,0x80,0x00,0x70,0xEF,0xF0,0x00,0x00,0x20,0x01,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xDD,0xFF,0xF0,0x00,0x07,0x80,0x10,0x70,0xEF,0xF0,0x00,0x00,0x20,0x01,
0xBF,0xFF,0xFF,0xFF,0xFF,0xF7,0x9D,0xFF,0x70,0x00,0x0F,0x00,0x10,0x40,0xEF,0xE0,
0x00,0x00,0x02,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xF1,0xD5,0xF7,0xC0,0x00,0x0E,0x00,
0x08,0x03,0xFF,0x60,0x00,0x00,0x00,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xF0,0x1D,0xFB,
0xC0,0x00,0x1D,0x00,0x00,0x00,0x1F,0xE0,0x00,0x00,0x00,0x01,0xBF,0xFF,0xFF,0xFF,
0xFF,0xF8,0x0F,0xFF,0x80,0x00,0x38,0x00,0x0E,0x0F,0x1F,0xC0,0x00,0x60,0x00,0x01,
0xBF,0xFF,0xFF,0xFF,0xFF,0xF9,0x8F,0xFF,0x80,0x00,0x38,0x60,0x0C,0x0F,0x1F,0x40,
0x00,0x60,0x00,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFB,0x8F,0xFF,0x80,0x00,0x30,0x30,
0x00,0x0D,0x3F,0x68,0x00,0x60,0x00,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFB,0x9D,0xFF,
0x80,0x00,0x40,0x31,0x26,0x07,0x3E,0x08,0x00,0x70,0x01,0x01,0xBF,0xFF,0xFF,0xFF,
0xFF,0xF8,0x1E,0xFF,0xF0,0x00,0x80,0x18,0x30,0x00,0x1F,0x8C,0x40,0x60,0x02,0x01,
0xBF,0xFF,0xFF,0xFF,0xFF,0xF9,0xFF,0xFF,0xF8,0x01,0x80,0x0C,0x0C,0x00,0x1F,0x8E,
0x00,0x60,0x02,0x41,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x07,0x00,0x0C,
0x00,0x00,0x1F,0x84,0x08,0x60,0x02,0x61,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,
0xFF,0xF8,0x00,0x1F,0xC3,0x73,0x08,0x14,0x00,0x30,0x00,0x41,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xBF,0xFF,0xF0,0x00,0x1F,0xF1,0x4B,0x00,0x06,0x00,0x30,0x00,0x01,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0xFF,0xE0,0x00,0x1F,0xFC,0x73,0x10,0x0E,
0x40,0x70,0x00,0x09,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE5,0x9F,0xFF,0x80,0x00,0x1F,
0xFF,0x84,0x00,0x7F,0x80,0x10,0x02,0x11,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0x8F,
0xFF,0x80,0x00,0x3F,0xFF,0xE0,0x00,0x7F,0x80,0x18,0x02,0x1D,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0x8F,0xFF,0x00,0x00,0x3F,0xFF,0xF0,0x03,0xFF,0x80,0x18,0x00,0x1D,
0xBF,0xFF,0xFF,0xFF,0xFF,0xDF,0xE7,0x83,0xF8,0x00,0x00,0x3F,0xFF,0xFF,0x01,0xFB,
0x40,0x38,0x03,0x11,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x81,0xF8,0x00,0x00,0x7F,
0xFF,0xFF,0xE3,0xFF,0x40,0x78,0x00,0x09,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,
0xF8,0x00,0x00,0x7F,0xFF,0xFF,0xE7,0xF4,0xC0,0x78,0x00,0x39,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x40,0x18,0x00,0x01,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x80,0x1E,0x00,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC0,0x18,0x00,0x01,0xBF,0xFF,0xFF,0xF7,0xFF,0xFD,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x18,0x00,0x01,0x80,0xFF,0xFF,0xF3,
0xFC,0x09,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x01,
0x80,0xFF,0xFF,0xF3,0xF9,0x89,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF8,0x18,0x00,0x01,0x8C,0xFF,0xFF,0xF3,0xF9,0xC9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFC,0x18,0x00,0x01,0x80,0xC8,0xC2,0x72,0xF3,0xE9,0x95,0x80,
0x90,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8C,0x00,0x01,0x80,0x19,0xE2,0xF1,
0xF3,0xE9,0x99,0x93,0x98,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9C,0x00,0x01,
0x8E,0x49,0xC2,0xF1,0xF3,0xC9,0x85,0x93,0x94,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF0,0x00,0x01,0x80,0xC9,0xC2,0x72,0xF9,0xC9,0x81,0x93,0x80,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x01,0x81,0x09,0xC0,0x12,0x7C,0x18,0x30,0x93,
0x90,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x01,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x01,
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x80,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x01,0xBF,0xAF,0xFF,0xC7,
0xCF,0xFE,0x51,0xFC,0x7F,0xFF,0xDF,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x01,
0xBF,0xA5,0xFF,0xC3,0xCB,0xFE,0x51,0xBD,0x7F,0xFF,0xF7,0xFB,0xF7,0xFF,0xFF,0xFF,
0xFF,0xFF,0x80,0x01,0xB0,0xB2,0x00,0xD4,0x01,0x1E,0x01,0x8F,0x01,0xE2,0x68,0x04,
0xF4,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x01,0x80,0xB2,0x80,0xD0,0x01,0x06,0x01,0xBD,
0x11,0x80,0x68,0x04,0xC0,0x7F,0xFF,0xFF,0xFF,0xFF,0xC2,0x01,0xBF,0xFF,0xFF,0xFF,
0xFF,0xCF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xE0,0x01,
0xBF,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xFF,0xF8,0x00,0x03,0xEF,0x3F,0xFF,0xFF,0xFF,
0xFF,0xFF,0xF0,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x01,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xF8,0x0F,0xFF,0xC0,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x01,
0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
INT8U Current_Operation = 0;						//当前操作序号
INT8U Statistics_Data[] = {20,70,80,40,90,65,30};	//待显示的统计数据
//-----------------------------------------------------------------
// 绘制条形图
//-----------------------------------------------------------------
void Draw_Bar_Graph(INT8U d[])
{
	INT8U i,h;
	Line(4,2,4,100,1);			//纵轴
	Line(4,100,158,100,1);		//横轴
	Line(4,2,1,10,1);			//横轴箭头
	Line(4,2,7,10,1);	
	Line(158,100,152,98,1);		//纵轴箭头
	Line(158,100,152,102,1);
	for (i = 0; i < 7; i++)		//输出条形图
	{	h = 100 - d[i];
		Line(10 + i * 20, h,	10 + i * 20,	 100, 1);
		Line(10 + i * 20, h,	10 + i * 20 + 15,  h, 1);
		Line(10 + i * 20 + 15,h,10 + i * 20 + 15,100, 1);
	}
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	INT8U i,j,m,c = 0;  INT16U k,x;
	LCD_Initialise();			//初始化LCD
	Set_LCD_POS(0,0); cls();	//从LCD左上角开始清屏
	while(1)
	{	if (S1 == 0) Current_Operation = 1;//正常
		if (S2 == 0) Current_Operation = 2;//反白
		if (S3 == 0) Current_Operation = 3;//滚动
		if (S4 == 0) Current_Operation = 4;//图文
		//如果操作类型未改变则仅执行延时.
		if ( c == Current_Operation) goto delayx;
		c = Current_Operation; 
		switch (Current_Operation)
		{	case 1: //正常或反白显示
			case 2: LCD_Write_Command_P2( LCD_GRH_STP,0x00,0x00);




			case 3: //滚动显示,每次向下移动一行GFXHOME地址(20字节)





			case 4: //图文显示



		}
		delayx:for (x = 0; x < 20000; x++); 	//延时
	}
}