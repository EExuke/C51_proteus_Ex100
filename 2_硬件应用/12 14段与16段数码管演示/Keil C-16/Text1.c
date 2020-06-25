//-----------------------------------------------------------------
//  名称: 74HC595驱动16段数码管演示
//-----------------------------------------------------------------
//  说明: 本例运行时,8只集成式16段数码管在按键控制下依次显示几组英文
//		与数字字符串.案例中16段数码管段码表编码规则见程序内说明.
//  
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit K1 = P1^7;	//按键定义
//595引脚定义
sbit SH_CP	= P2^0;	//移位时钟脉冲
sbit DS	 = P2^1;	//串行数据输入
sbit ST_CP	= P2^2;	//输出锁存器控制脉冲
sbit OE		= P2^3;	//使能输出
//本例编码按数码管各段字母顺序设计编码(先外框循环,后内部米字循环):
//A1 A2 B C D2 D1 E F H I J G2 K L M G1 DP(编码时注意逆向)
//16段共阳数码管段码表(本例用的是共阴数码管,输出时要取反)
code INT16U SEG_CODE16[] = 
{ 0xEE00,0xFFF3,0x7788,0x77C0,0x7773,0x7744,0x7704,0xFFF0,0x7700,
  0x7740,0x7730,0x7304,0xFF0C,0xDDC0,0x770C,0x773C,0xF704,0x7733,
  0xDDCC,0xDD9C,0x6B3F,0xFF0F,0xFA33,0xEE33,0xFF00,0x7738,0xEF00,
  0x6738,0x6F4C,0xDDFC,0xFF03,0xBB3F,0xAF33,0xAAFF,0xDAFF,0xBBCC
};
//待显示字符串
code char str_buffer[] = "DEMO 313abcdefghijKLMNOPQRSTUVWXYZ 0123456789";
//上次按键状态
INT8U pre_key_status = 1;

//595并行输出宏定义(上升沿将数据送到输出锁存器)

//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT8U x) 
{
	INT8U t; while (--x)  for (t = 0; t < 120; t++);
}

//------------------------------------------------------------------
// 获取字符的16位段码
//------------------------------------------------------------------
INT16U get_16_segcode(char c)
{
	if (isdigit(c))						//取得数字段码
	{
		c = c - '0';
		return SEG_CODE16[(INT8U)c];
	}
	else if (isalpha(c))				//取得字母段码
	{
		c = toupper(c) - 'A' + 10;
		return SEG_CODE16[(INT8U)c];
	}
	else
		return 0xFFFF;					//其他字符返回黑屏
}

//-----------------------------------------------------------------
// 串行输入595子程序
//-----------------------------------------------------------------
void Serial_Input_595(INT8U dat)
{
	INT8U i;
	for(i = 0x80; i != 0x00; i >>= 1)
	{
		if (dat & i)				//发送高位
			DS = 1;
		else
			DS = 0;
		SH_CP = 0;					//移位时钟脉冲上升沿移位
		_nop_();
		SH_CP = 1;					//移位时钟置低电平
	}		
}

//------------------------------------------------------------------
// 主程序
//------------------------------------------------------------------
void main() 
{ 
	INT8U i, j, len = strlen(str_buffer), n = ceil(len / 8.0);
	INT16U sCode = 0x0000;
	while(1)
	{
		i = 0;						//组索引，每组显示8个字符
		while (i < n)				//小于数组
		{
			for (j = 0; j < 8 && (8 * i + j) < len; j++)
			{
				/* 取得当前字符段码 */
				sCode = ~get_16_segcode(str_buffer[8 * i + j]);
				/* 串行输出3字节数据：位码，段码低字节，段码高字节 */
				Serial_Input_595(~(1 << j));		//发送位扫描码
				Serial_Input_595(sCode >> 8);		//发送段码高8位
				Serial_Input_595(sCode);			//发送段码低8位
				/* 74HC595移位寄存数据传输到存储寄存器并出现在输出端 */
				OE = 1;
				Parallel_Output();
				_nop_();
				OE = 0;
				delay_ms(2);
			}
			if (pre_key_status != K1)		//判断按键状态是否发生改变
			{
				if (K1 == 0)				//如果有按键按下则显示下一组
					i++;
				pre_key_status = K1;		//保存当前按键状态
			}
		}
	}
}