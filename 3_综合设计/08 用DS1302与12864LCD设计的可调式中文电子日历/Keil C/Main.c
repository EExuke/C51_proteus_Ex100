//-----------------------------------------------------------------
//名称: 用DS1302与12864LCD设计的可调式电子日历与时钟
//-----------------------------------------------------------------
//说明: 本例运行时会以PC时间为默认时间开始,运行过程中可以通过K1
//		选择调节对象,所选中的调节对象会反色显示,K2,K3进行加减调节,
//		K4保存.
//		本例自动将日期时间调节控制在合法范围内,星期调节会在调整
//		年月日时自动完成,闰年问题也能自动处理. 
//								
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <string.h>
#define INT8U	unsigned char
#define INT16U	unsigned int
extern void LCD_Initialize();
extern void Disp_A_Char(INT8U P,INT8U L,INT8U *M) reentrant;
extern void Disp_A_Word(INT8U P,INT8U L,INT8U *M) reentrant;
//在调节日期时间时,用该位决定是否反白显示
extern bit Reverse_Display ;
sbit SDA = P1^0;		//DS1302数据线
sbit CLK = P1^1;		//DS1302时钟线
sbit RST = P1^2;		//DS1302复位线
sbit K1 = P3^4;			//选择 
sbit K2 = P3^5;			//加
sbit K3 = P3^6;			//减
sbit K4 = P3^7;			//确定
INT8U tCount = 0;
//一年中每个月的天数,2月的天数是否再加1由年份决定
code INT8U M_Days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
INT8U DateTime[7];			//所读取的日期时间
//当前调节的时间对象:秒,分,时,日,月,年(0,1,2,3,4,6)
//5对应星期,星期调节由年月日调节自动完成
char Adjust_Index = -1;
INT8U H_Offset = 10, V_P_Offset = 0;	//水平页偏移与垂直像素偏移
//"年、月、日、星、期、时、分、秒"的汉字点阵(16x16)-----------------------
INT8U code DATETIME_WORDS[] = 
{
/*---------------年----------------*/
0x40,0x20,0x10,0x0C,0xE3,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0x22,0x02,0x00,0x00,
0x04,0x04,0x04,0x04,0x07,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x04,0x04,0x00,
/*---------------月----------------*/
0x00,0x00,0x00,0x00,0x00,0xFF,0x11,0x11,0x11,0x11,0x11,0xFF,0x00,0x00,0x00,0x00,
0x00,0x40,0x20,0x10,0x0C,0x03,0x01,0x01,0x01,0x21,0x41,0x3F,0x00,0x00,0x00,0x00,
/*---------------日----------------*/
0x00,0x00,0x00,0xFE,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0xFE,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x3F,0x00,0x00,0x00,0x00,
/*---------------星----------------*/
0x00,0x00,0x00,0xBE,0x2A,0x2A,0x2A,0xEA,0x2A,0x2A,0x2A,0x2A,0x3E,0x00,0x00,0x00,
0x00,0x48,0x46,0x41,0x49,0x49,0x49,0x7F,0x49,0x49,0x49,0x49,0x49,0x41,0x40,0x00,
/*---------------期----------------*/
0x00,0x04,0xFF,0x54,0x54,0x54,0xFF,0x04,0x00,0xFE,0x22,0x22,0x22,0xFE,0x00,0x00,
0x42,0x22,0x1B,0x02,0x02,0x0A,0x33,0x62,0x18,0x07,0x02,0x22,0x42,0x3F,0x00,0x00,
/*---------------时----------------*/
0x00,0xFC,0x44,0x44,0x44,0xFC,0x10,0x90,0x10,0x10,0x10,0xFF,0x10,0x10,0x10,0x00,
0x00,0x07,0x04,0x04,0x04,0x07,0x00,0x00,0x03,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,
/*---------------分----------------*/
0x80,0x40,0x20,0x98,0x87,0x82,0x80,0x80,0x83,0x84,0x98,0x30,0x60,0xC0,0x40,0x00,
0x00,0x80,0x40,0x20,0x10,0x0F,0x00,0x00,0x20,0x40,0x3F,0x00,0x00,0x00,0x00,0x00,
/*---------------秒----------------*/
0x12,0x12,0xD2,0xFE,0x91,0x11,0xC0,0x38,0x10,0x00,0xFF,0x00,0x08,0x10,0x60,0x00,
0x04,0x03,0x00,0xFF,0x00,0x83,0x80,0x40,0x40,0x20,0x23,0x10,0x08,0x04,0x03,0x00
};
//星期"日、一、二、三、四、五、六"的汉字点阵(16x16)-----------------------
INT8U code WEEK_WORDS[] = 
{
/*---------------日----------------*/
0x00,0x00,0x00,0xFE,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0xFE,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x3F,0x00,0x00,0x00,0x00,
/*---------------一----------------*/
0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xC0,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*---------------二----------------*/
0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x06,0x04,0x00,0x00,0x00,
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x18,0x10,0x00,
/*---------------三----------------*/
0x00,0x04,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x84,0x04,0x00,0x00,
0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
/*---------------四----------------*/
0x00,0xFE,0x02,0x02,0x02,0xFE,0x02,0x02,0xFE,0x02,0x02,0x02,0x02,0xFE,0x00,0x00,
0x00,0x7F,0x28,0x24,0x23,0x20,0x20,0x20,0x21,0x22,0x22,0x22,0x22,0x7F,0x00,0x00,
/*---------------五----------------*/
0x00,0x02,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0xC2,0x82,0x02,0x00,0x00,0x00,
0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x30,0x20,0x00,
/*---------------六----------------*/
0x10,0x10,0x10,0x10,0x10,0x91,0x12,0x1E,0x94,0x10,0x10,0x10,0x10,0x10,0x10,0x00,
0x00,0x40,0x20,0x10,0x0C,0x03,0x01,0x00,0x00,0x01,0x02,0x0C,0x78,0x30,0x00,0x00
};

//半角数字"0~9"的点阵(8x16)------------------------------------------
INT8U code DIGITS[] = 
{
/*---------------0----------------*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,
/*---------------1----------------*/
0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,
/*---------------2----------------*/
0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,
/*---------------3----------------*/
0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,
/*---------------4----------------*/
0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,
/*---------------5----------------*/
0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,
/*---------------6----------------*/
0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,
/*---------------7----------------*/
0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,
/*---------------8----------------*/
0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,
/*---------------9----------------*/
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00
};

//-----------------------------------------------------------------
// 向DS1302写入一字节
//-----------------------------------------------------------------
void Write_one_byte(INT8U x)
{ 


}

//-----------------------------------------------------------------
// 从DS1302读取一字节
//-----------------------------------------------------------------
INT8U Get_one_byte()
{ 


}

//-----------------------------------------------------------------
// 从DS1302指定位置读数据
//-----------------------------------------------------------------
INT8U Read_Data(INT8U addr)
{


}

//-----------------------------------------------------------------
// 向DS1302某地址写入数据
//-----------------------------------------------------------------
void Write_DS1302(INT8U addr,INT8U dat)
{


}

//-----------------------------------------------------------------
// 设置时间
//-----------------------------------------------------------------
void SET_DS1302() 
{


}

//-----------------------------------------------------------------
// 读取当前日期时间
//-----------------------------------------------------------------
void GetTime() 
{


}

//-----------------------------------------------------------------
// 判断是否为闰年
//-----------------------------------------------------------------
INT8U isLeapYear(INT16U y)
{


}

//-----------------------------------------------------------------
// 求自2000.1.1开始的任何一天是星期几
// 函数没有通过求出总天数后再求星期几,
// 是因为求总天数可能会越出INT16U的范围
//-----------------------------------------------------------------
void RefreshWeekDay()
{ 


}

//-----------------------------------------------------------------
// 年月日时分秒递增/减调节(星期自动计算,不允许直接调节)
//-----------------------------------------------------------------
void DateTime_Adjust(char x)
{ 


}

//-----------------------------------------------------------------	
// 定时器0每秒刷新LCD显示	 
//-----------------------------------------------------------------
void T0_INT() interrupt 1 
{


}

//-----------------------------------------------------------------
// 键盘中断(INT0)
//-----------------------------------------------------------------
void EX_INT0() interrupt 0 
{


}

//-----------------------------------------------------------------
// 主程序	 
//-----------------------------------------------------------------
void main()
{


}
