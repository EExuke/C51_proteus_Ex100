//-----------------------------------------------------------------
//  名称: MMC存储卡测试
//-----------------------------------------------------------------
//  说明: 本例运行时,按下K1将向MMC卡第0块写入512个有序字节,按下K2时
//		将向第1块写入512个随机字节,按下K3与K4时将分别读取并通过
//		虚拟终端显示这些字节数据.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <absacc.h>
#define INT8U  unsigned char
#define INT16U unsigned int
#define INT32U unsigned long
//定义按键操作
#define K1_DOWN() !(P1 & (1<<0))
#define K2_DOWN() !(P1 & (1<<2))
#define K3_DOWN() !(P1 & (1<<4))
#define K4_DOWN() !(P1 & (1<<6))
//MMC相关函数
extern void OpenSPI();
extern INT8U MMC_Initialise();
extern INT8U MMC_Read_Block(INT32U address);
extern INT8U MMC_Write_Block(INT32U address);
//串口相关函数
extern void Init_USART();
extern void PutChar(char c);
extern void PutStr(char *s);
INT8U OP = 0;			//当前按键操作代号
INT8U ERROR_Flag = 1;	//MMC卡操作错误标识(为1表示正常,为0表示出错)
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x) {INT8U t; while(x--) for(t = 0; t<120; t++);}
//-----------------------------------------------------------------
// 以十六进制形式显示所读取的字节
//-----------------------------------------------------------------
void Show_Byte_by_HEX(INT32U Len)
{
	INT32U i; char s[] = "   ";//字符串初始为三个空格
	for (i = 0; i < Len; i++)
	{




	}
	PutStr("\r--------Finished!--------\r");
}

//-----------------------------------------------------------------
// 向串口输出一个字符
//-----------------------------------------------------------------
void PutChar(INT8U c) { SBUF = c; while (TI == 0); TI = 0; }
//------------------------------------------------------------------
// 串口输出字符串
//------------------------------------------------------------------
void PutStr(char *s) { while (*s) PutChar(*s++); }
//-----------------------------------------------------------------
// 串口配置
//-----------------------------------------------------------------
void Init_USART()
{


}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	INT32U i,j;
	//SPI,USART初始化
	OpenSPI(); Init_USART(); delay_ms(100);
	//初始化MMC
	PutStr("Initialise MMC, Please Waiting.....");
	ERROR_Flag = MMC_Initialise();
	if (ERROR_Flag) PutStr("OK!\r\r"); else PutStr("ERROR!\r\r");
	//提示进行K1-K4操作
	PutStr("Plase Press K1,K2,K3 or K4 to Play MMC Test...\r\r");
	//设置随机种子
	srand(300);
	while(1)
	{	while (P1 == 0xFF); //未按键则等待-------------------------
		if		(K1_DOWN()) { delay_ms(10); if (K1_DOWN()) OP = 1; }
		else if (K2_DOWN()) { delay_ms(10); if (K2_DOWN()) OP = 2; }
		else if (K3_DOWN()) { delay_ms(10); if (K3_DOWN()) OP = 3; }
		else if (K4_DOWN()) { delay_ms(10); if (K4_DOWN()) OP = 4; }
		//如果上次MMC出错则重新初始化SPI接口与MMC卡
		if (ERROR_Flag == 0) //------------------------------------
		{


		}
		//根据按键操作代号分别进行操作,因为上述可能的重新初始化会耗费较多时间,
		//如果在这里仍用K1~K4的DOWN判断,按键可能已经释放,从而导致判断失效.
		//因此这里使用的是提前获取的按键操作代号
		if (OP == 1) //--------------------------------------------
		{


		}
		else if (OP == 2) //---------------------------------------
		{


		}
		else if (OP == 3) //---------------------------------------
		{


		}
		else if (OP == 4) //---------------------------------------
		{


		}
		next: while (P1 != 0xFF); 		//等待释放按键-----------------
	}
}