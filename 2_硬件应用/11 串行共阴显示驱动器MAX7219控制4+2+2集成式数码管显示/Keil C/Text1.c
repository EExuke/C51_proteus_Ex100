//-----------------------------------------------------------------
//  名称: 串行共阴显示驱动器MAX7219/7221控制集成式数码管显示
//-----------------------------------------------------------------
//  说明: 本例用MAX7219(MAX7221)控制两组8位数码管动态显示,大大减少了
//		  对单片机引脚和机器时间的占用.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit DIN = P2^0;		//数据线
sbit CLK = P2^2;		//时钟线
sbit CS7221 = P2^1;		//片选线
sbit CS7219 = P2^3;
//在非解码模式下MAX7219/7221对应的段码表,此表不同于直接驱动时所使用的段码表
//原来的各段顺序是：		DP,G,F,E,D,C,B,A
//MAX7219/7221的驱动顺序是：DP,A,B,C,D,E,F,G
//除小数点位未改变外，其他位是逆向排列的.
//下在前两行为0~F的段码,最后4位为"-(16)/°(17)/C(18)/黑屏(19)"的段码
code INT8U SEGCODE_72XX[] = 
{ 0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,	//0~7
  0x7F,0x7B,0x77,0x1F,0x4E,0x3D,0x4F,0x47,	//8~F
  0x01,0x63,0x4E,0x00						//16~19[ - °C 黑屏]
};
//7219待显示的内容为温度值:-32.75℃("-"前面的最高位黑屏)
//由于本例7219工作于非解码模式,在串行发送时,需要以下表为索引,
//发送SEGCODE_72XX中的对应段码
code INT8U Disp_Buffer0[] = {19,16,3,2,7,5,17,18};
//7221待显示的数字串"20150925"(由于本例7221工作于解码模式,故各数位直接发送)
code INT8U Disp_Buffer1[] = {2,0,1,5,0,9,2,5};
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// 向MAX7219/7221指定地址(寄存器)写入1字节数据
//-----------------------------------------------------------------
void Write(INT8U addr,INT8U dat,INT8U Chip_No)
{
	INT8U i;
	/*片选MAX7219或MAX7221*/
	if (Chip_No == 1)
		CS7221 = 0;
	else
		CS7219 = 0;
	/* 串行写入8位地址addr */
	for(i=0; i<8; i++)
	{
		CLK = 0;
		addr <<= 1;
		DIN = CY;
		CLK = 1;
		_nop_(); _nop_();
	}
	/* 串行写入8位数据dat */
	for(i=0; i<8; i++)
	{
		CLK = 0;
		dat <<= 1;
		DIN = CY;
		CLK = 1;
		_nop_(); _nop_();
	}
	/*禁止片选*/
	if (Chip_No == 1)
		CS7221 = 1;
	else
		CS7219 = 1;
}

//-----------------------------------------------------------------
// MAX7221/7219初始化
//-----------------------------------------------------------------
void Init_MAX72XX(INT8U i)
{
	/* 解码模式地址0x09(0x00为不解码,0xFF为全解码) */
	if (i == 0)
		Write(0x09, 0x00, i);
	else
		Write(0x09, 0xFF, i);
	Write(0x0A, 0x07, i);    //亮度地址0x0A(0x00~0x0F, 渐亮)
	Write(0x0B, 0x07, i);    //扫描数码管个数地址0x0B()
	Write(0x0C, 0x01, i);    //工作模式地址0x0C(0x00:关闭， 0x01:正常)
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	INT8U i;
	Init_MAX72XX(0);	delay_ms(5);    //MAX7219初始化
	Init_MAX72XX(1);	delay_ms(5);    //MAX7221初始化
	//MAX7219控制显示 Disp_Buffer0数组，全部非解码显示
	//以 Disp_Buffer0[i]为索引发送段码
	for(i=0; i<8; i++)
	{
		if (i == 3)
			Write(i+1, SEGCODE_72XX[Disp_Buffer0[i]] | 0x80, 0);
		else
			Write(i+1, SEGCODE_72XX[Disp_Buffer0[i]], 0);
	}
	delay_ms(100);
	//7221控制显示  Disp_Buffer1数组，全部解码显示
	//直接发送 Disp_Buffer1[i]
	for(i=0; i<8; i++)
		Write(i+1, Disp_Buffer1[i], 1);
	while(1);
}