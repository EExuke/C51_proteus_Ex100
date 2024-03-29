//-----------------------------------------------------------------
//	名称：74HC595串入并出芯片控制数码管显示四位数字
//-----------------------------------------------------------------
//	说明：4片74HC595串入并出芯片控制四位数码管循环显示指定的四组数据.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U	unsigned char
#define INT16U unsigned int
sbit SH_CP = P2^0;		//移位时钟脉冲
sbit DS	= P2^1;			//串行数据输入
sbit ST_CP = P2^2;		//输出锁存器控制脉冲
code INT8U SEG_CODE[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
INT16U myData[4] = {2938,1234,1509,3506};
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// 1字节数据串行输入595子程序
//-----------------------------------------------------------------
void Serial_Input_595(INT8U d)
{
    INT8U i;
    for(i=0; i<8; i++)
    {
        d <<= 1;
        DS = CY;     //高位移出到CY，并写入数据线
        SH_CP = 0; _nop_(); _nop_(); //时钟线输出低电平
        SH_CP = 1; _nop_(); _nop_(); //时钟线上升沿移位
    }
    SH_CP = 0;  //移位时钟线最后置为低电平
}

//-----------------------------------------------------------------
// 595并行输出子程序
//-----------------------------------------------------------------
void Parallel_Output_595()
{
    ST_CP = 0; _nop_(); _nop_();    //先置低电平
    ST_CP = 1; _nop_(); _nop_();    //上升沿将数据送到输出锁存器
    ST_CP = 0; _nop_(); _nop_();    //置低电平
}

//-----------------------------------------------------------------
//主程序
//-----------------------------------------------------------------
void main()
{
	INT8U i,t;
	while (1)
	{
    	//循环输出四组数据
		for( i = 0; i < 4; i++ )
		{
            //分解出每组数据中的0~3位，串行输出到595
            t = SEG_CODE[myData[i] % 10];
            Serial_Input_595(t);
            t = SEG_CODE[myData[i] / 10 % 10] & 0x7F;   //倒数第二位附加小数点
            Serial_Input_595(t);
            t = SEG_CODE[myData[i] % 1000 / 100];
            Serial_Input_595(t);
            t = SEG_CODE[myData[i] / 1000];
            Serial_Input_595(t);
            //4片595同时并行输出到数码管显示
            Parallel_Output_595();
            delay_ms(1000);
		}
	}
}