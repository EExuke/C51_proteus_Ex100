//-----------------------------------------------------------------
//  名称: 用8255实现接口扩展
//-----------------------------------------------------------------
//  说明: 8255的PA、PB端口分别连接8位数码管的段码和位码,
//		 程序控制数码管滚动显示一串数字.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <absacc.h>
#define INT8U  unsigned char
#define INT16U unsigned int 
//PA,PB,PC端口及命令端口地址定义
#define PA	XBYTE[0x0000]  
#define PB	XBYTE[0x0001] 
#define PC	XBYTE[0x0002] 
#define COM  XBYTE[0x0003]
//上述定义也可写成:
//#define PA	*(XBYTE + 0x0000)
//#define PB	*(XBYTE + 0x0001)
//#define PC	*(XBYTE + 0x0002)
//#define COM  *(XBYTE + 0x0003) 
//0-9的共阳数码管段码表,最后的0xBF表示"-"
code INT8U SEG_CODE[] =
{ 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xBF };
//待显示信息缓冲12-39-59
INT8U Disp_Buf[] = {1,2,10,3,9,10,5,9};
//-----------------------------------------------------------------
// 延时函数
//-----------------------------------------------------------------
void delay_ms(INT16U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// 8255PC端口按键处理
//-----------------------------------------------------------------
void Key_Process()
{
	static INT8U Pre_Key_State = 0x00;	//上次按键状态（静态变量！）
	INT8U Key_State,t;
	Key_State = PC;					 //读8255PC端口按键状态；
	if(Key_State == Pre_Key_State)	 //按键状态未改变则返回；
		return;	
	Pre_Key_State = Key_State;		//保存当前按键状态；
	switch (Key_State)
	{
		case ~(1 << 0):					   //K1:小时递增；
			t = Disp_Buf[0] * 10 + Disp_Buf[1];
			if( ++t == 24 )
				t = 0;
			Disp_Buf[0] = t/10;
			Disp_Buf[1] = t%10;
			break;
		case ~(1 << 2):					   //K2:分钟递增；
			t = Disp_Buf[3] * 10 + Disp_Buf[4];
			if( ++t == 60 )
				t = 0;
			Disp_Buf[3] = t/10;
			Disp_Buf[4] = t%10;
			break;
		case ~(1 << 4):					   //K3：秒数递增；
			t = Disp_Buf[6] * 10 + Disp_Buf[7];
			if( ++t == 60 )
				t = 0;
			Disp_Buf[6] = t/10;
			Disp_Buf[7] = t%10;
			break;
		default:
			break;
	}
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() 
{ 
	INT8U i;
	COM = 0x89;	   //设置8255工作方式为 模式0（PA、PB输出，PC输入）
	while(1)
	{
		for(i=0;i<8;i++)					//8个数码管动态循环扫描显示；
		{
			PA = 0xFF;						//暂时关闭段位（黑屏）；
			PB = 1 << i;					//发送位码；
			PA = SEG_CODE[Disp_Buf[i]];		//发送段码；
			delay_ms(4);					//换位按时约4ms；
			Key_Process();					//按键处理；
		}
	} 
}
