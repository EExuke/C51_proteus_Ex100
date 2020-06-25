//-----------------------------------------------------------------
//  名称: IIC存储器设计的中文硬件字库应用
//-----------------------------------------------------------------
//  说明: 本例将262K的16*16点阵中文字库文件HZK16拆分为两个128K文件,
//		分别保存到两片24C1024中,多余6K字节被删除,运行本例时,对于
//		任意输入的汉字或中文标题符号,程序会直接从24C1024所保存的
//		字库中提取点阵并转换为液晶格式,显示在中文液晶屏上.
//
//-----------------------------------------------------------------
#include "89c51rd2.h"
#include <intrins.h>
#include <string.h>	
#define INT8U	unsigned char
#define INT16U  unsigned int
#define INT32U  unsigned long
//12864LCD相关函数
void LCD_Initialize();
void Display_A_Char(INT8U,INT8U,INT8U *);
void Display_A_WORD_String(INT8U,INT8U,INT8U,INT8U *); 
void Display_Image(INT8U,INT8U,INT8U,INT8U,INT8U * );
//I2C相关函数
void IICInit();
INT8U IIC_ReadBytes(INT8U Slave,INT32U Mem_address,INT8U *Buf,INT8U N);
//从汉字库取得的一个汉字的点阵存放区
INT8U Word_Dot_Matrix[32];
//转换为LCD显示格式的汉字点阵存放区
INT8U LCD_Dot_Matrix[32];
//下面可以任意输入诗文,注意标题符号使用中文全角方式输入
//编译时中文字符串可能出现乱码，此时可将所有内容或部分内容用"内码"混合表示
//例如下面诗词中的最后一句："三军过后尽开颜。"
code char Poem[9][17] = 
{	"红军不怕远征难，","万水千山只等闲。","五岭逶迤腾细浪，","乌蒙磅礴走泥丸。",
	"金沙水拍云崖暖，","大渡桥横铁索寒。","更喜岷山千里雪，",//"三军过后尽开颜。"
	"\xC8\xFD\xBE\xFC\xB9\xFD\xBA\xF3\xBE\xA1\xBF\xAA\xD1\xD5\xA1\xA3"
};
//中文信息还可以用下面的形式表示（下面是另外一首词）
//char code Poem[][17] = 
//{	"饮茶粤海未能忘，","索句渝州叶正黄。","三十一年还旧国，","落花时节读华章。",
//	"牢骚太盛防肠断，","风物长宜放眼量。","莫道昆明池水浅，","观鱼胜过富春江。"
//}
//char code Poem[][17] = {
//"\xD2\xFB\xB2\xE8\xD4\xC1\xBA\xA3\xCE\xB4\xC4\xDC\xCD\xFC\xA3\xAC",
//"\xCB\xF7\xBE\xE4\xD3\xE5\xD6\xDD\xD2\xB6\xD5\xFD\xBB\xC6\xA1\xA3",
//"\xC8\xFD\xCA\xAE\xD2\xBB\xC4\xEA\xBB\xB9\xBE\xC9\xB9\xFA\xA3\xAC",
//"\xC2\xE4\xBB\xA8\xCA\xB1\xBD\xDA\xB6\xC1\xBB\xAA\xD5\xC2\xA1\xA3",
//"\xC0\xCE\xC9\xA7\xCC\xAB\xCA\xA2\xB7\xC0\xB3\xA6\xB6\xCF\xA3\xAC",
//"\xB7\xE7\xCE\xEF\xB3\xA4\xD2\xCB\xB7\xC5\xD1\xDB\xC1\xBF\xA1\xA3",
//"\xC4\xAA\xB5\xC0\xC0\xA5\xC3\xF7\xB3\xD8\xCB\xAE\xC7\xB3\xA3\xAC",
//"\xB9\xDB\xD3\xE3\xCA\xA4\xB9\xFD\xB8\xBB\xB4\xBA\xBD\xAD\xA1\xA3"};
//或采用下面的字节数组形式
//char code Poem[][17] = {
//{0xD2,0xFB,0xB2,0xE8,0xD4,0xC1,0xBA,0xA3,0xCE,0xB4,0xC4,0xDC,0xCD,0xFC,0xA3,0xAC,0x00},
//{0xCB,0xF7,0xBE,0xE4,0xD3,0xE5,0xD6,0xDD,0xD2,0xB6,0xD5,0xFD,0xBB,0xC6,0xA1,0xA3,0x00},
//{0xC8,0xFD,0xCA,0xAE,0xD2,0xBB,0xC4,0xEA,0xBB,0xB9,0xBE,0xC9,0xB9,0xFA,0xA3,0xAC,0x00},
//{0xC2,0xE4,0xBB,0xA8,0xCA,0xB1,0xBD,0xDA,0xB6,0xC1,0xBB,0xAA,0xD5,0xC2,0xA1,0xA3,0x00},
//{0xC0,0xCE,0xC9,0xA7,0xCC,0xAB,0xCA,0xA2,0xB7,0xC0,0xB3,0xA6,0xB6,0xCF,0xA3,0xAC,0x00},
//{0xB7,0xE7,0xCE,0xEF,0xB3,0xA4,0xD2,0xCB,0xB7,0xC5,0xD1,0xDB,0xC1,0xBF,0xA1,0xA3,0x00},
//{0xC4,0xAA,0xB5,0xC0,0xC0,0xA5,0xC3,0xF7,0xB3,0xD8,0xCB,0xAE,0xC7,0xB3,0xA3,0xAC,0x00},
//{0xB9,0xDB,0xD3,0xE3,0xCA,0xA4,0xB9,0xFD,0xB8,0xBB,0xB4,0xBA,0xBD,0xAD,0xA1,0xA3,0x00}};
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x) {INT8U t; while(x--) for(t = 0; t<120; t++);}
//-----------------------------------------------------------------
// 读取汉字点阵并将字库点阵格式转换为本例的液晶屏汉字取模格式
//-----------------------------------------------------------------
void Read_HZ_dot_Matrix_AND_Convert_TO_LCD_Fmt(INT8U c[])
{  



}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{



}
