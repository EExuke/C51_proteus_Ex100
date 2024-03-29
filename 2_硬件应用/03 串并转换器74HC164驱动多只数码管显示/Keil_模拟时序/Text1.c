//-----------------------------------------------------------------
//  名称: 模拟时序控制串并转换器74HC164驱动多只数码管显示
//-----------------------------------------------------------------
//  说明: 本例运行时,5只独立数码管在串入并出转换器74HC164的驱动下
//        独立显示5位数字，数码管的显示仅占用单片机2只引脚.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U  unsigned char
#define INT16U unsigned int
//数码管段码表
const INT8U SEG_CODE[] = 
{ 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF };
//数位分解所用的权值表
const INT16U m[] = {10000,1000,100,10};
INT16U val = 42950; 		//所演示的起始值
INT8U Buf[5];				//分解以后的存放缓冲
//74HC164引脚定义
sbit DAT = P3^4; 			//串行数据线
sbit CLK = P3^7;			//串行时钟线
//-----------------------------------------------------------------
// 延时
//-----------------------------------------------------------------
void delay_ms(INT16U x)
{
	INT8U i; while(--x) for(i = 0;i < 120; i++) ;
}

//-----------------------------------------------------------------
// 将整数x分解为5个数位,存入数组d
//-----------------------------------------------------------------
void Decompose(INT16U x,INT8U d[])
{
    INT8U i;
    for(i=0; i<4; i++)
    {
        d[i] = 0;
        while(x >= m[i])
        {
            x -= m[i];
            d[i]++;
        }
    }
    d[4] = x;
}

//-----------------------------------------------------------------
// 模拟时序向74HC164串行输出1字节数据
//-----------------------------------------------------------------
void Serial_Output(INT8U d)
{
    INT8U i;
    for(i=0; i<8; i++)
    {
        CLK = 0;           //每字节8位
        d <<= 1;           //时钟置低电平
        DAT = CY;          //移出1位(高位优先)
        CLK = 1;           //上升沿数据移入74HC164
    }
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
    INT8U i;
    while(1)
    {
        Decompose(val, Buf);         //分解待显示数据val
        for(i=4; i!=0xFF; i--)       //串行发送各数字段码
            Serial_Output(SEG_CODE[Buf[i]]);
        delay_ms(500);
        ++val;
    }
}