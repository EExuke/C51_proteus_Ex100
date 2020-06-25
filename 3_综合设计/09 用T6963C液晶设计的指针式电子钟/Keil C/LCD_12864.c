//-----------------------------------------------------------------
// LCD显示控制程序
//-----------------------------------------------------------------
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <intrins.h>
#include <absacc.h>
#include <string.h>
#include <LCD_12864.h>
INT8U code LCD_WIDTH  = 16;	//宽128像素(即16字节 * 8 = 128像素)
INT8U code LCD_HEIGHT = 64;	//高64像素
INT8U gCurRow,gCurCol;	// 图形当前行、列存储，行高16点，列宽8点
INT8U tCurRow,tCurCol;	// 文本当前行、列存储，行高8点 ，列宽8点
INT8U ShowModeSW;		// 当前显示模式
INT16U  txthome,grhome;
//-----------------------------------------------------------------
// LCD控制相关函数
//-----------------------------------------------------------------
INT8U Status_BIT_01();	// 状态位STA1,STA0判断（读写指令和读写数据）
INT8U Status_BIT_3();	// 状态位ST3判断（数据自动写状态）
INT8U LCD_Write_Command(INT8U cmd);							//写无参数的指令
INT8U LCD_Write_Command_P1(INT8U cmd,INT8U para1);			//写单参数的指令
INT8U LCD_Write_Command_P2(INT8U cmd,INT8U para1,INT8U para2);//写双参数的指令
INT8U LCD_Write_Data(INT8U dat);							//写数据
INT8U LCD_Read_Data();										//读数据
void cls();													//清屏
char LCD_Initialise();										//LCD初始化
void SetShowMode(INT8U mode);								//设置显示模式
void Set_LCD_POS(INT8U row, INT8U col) reentrant;			//设置当前地址
void Line(INT8U x1, INT8U y1, INT8U x2, INT8U y2, bit Mode);//绘制直线
void Pixel(INT8U x,INT8U y, INT8U Mode) reentrant;			//绘点
INT8U gCurRow,gCurCol;										//图形当前行,列
INT8U tCurRow,tCurCol;										//文本当前行,列
INT16U  txthome,grhome;
//-----------------------------------------------------------------
// 状态位STA1,STA0判断(读写指令和读写数据)
//-----------------------------------------------------------------
INT8U Status_BIT_01() 
{


}

//-----------------------------------------------------------------
// 状态位ST3判断(数据自动写状态)
//-----------------------------------------------------------------
INT8U Status_BIT_3() 
{


}

//-----------------------------------------------------------------
// 写双参数的指令
//-----------------------------------------------------------------
INT8U LCD_Write_Command_P2(INT8U cmd,INT8U para1,INT8U para2) 
{


}

//-----------------------------------------------------------------
// 写单参数的指令
//-----------------------------------------------------------------
INT8U LCD_Write_Command_P1(INT8U cmd,INT8U para1) 
{


}

//-----------------------------------------------------------------
// 写无参数的指令
//-----------------------------------------------------------------
INT8U LCD_Write_Command(INT8U cmd) 
{


}

//-----------------------------------------------------------------
// 写数据
//-----------------------------------------------------------------
INT8U LCD_Write_Data(INT8U dat) 
{


}

//-----------------------------------------------------------------
// 设置当前地址
//-----------------------------------------------------------------
void Set_LCD_POS(INT8U row, INT8U col) reentrant
{
	INT16U Pos;	
	Pos = row * LCD_WIDTH + col;
	LCD_Write_Command_P2(LC_ADD_POS,Pos % 256, Pos / 256);
	gCurRow = row;
	gCurCol = col;
}

//-----------------------------------------------------------------
// 清屏
//-----------------------------------------------------------------
void cls()
{
	INT16U i;	
	LCD_Write_Command_P2(LC_ADD_POS,0x00,0x00);	//置地址指针
	LCD_Write_Command(LC_AUT_WR);				//自动写
	for(i = 0;i < 0x2000; i++)
	{	Status_BIT_3();
		LCD_Write_Data(0x00);					//写数据
	}
	LCD_Write_Command(LC_AUT_OVR);				//自动写结束
	LCD_Write_Command_P2(LC_ADD_POS,0x00,0x00);	//重置地址指针
	gCurRow = 0;
	gCurCol = 0;
}

//-----------------------------------------------------------------
// LCD初始化
//-----------------------------------------------------------------
char LCD_Initialise()
{
	RESET = 0;
	RESET = 1;
	LCD_Write_Command_P2(LC_TXT_STP,0x00,0x00);		//文本显示区首地址
	LCD_Write_Command_P2(LC_TXT_WID,LCD_WIDTH,0x00);//文本显示区宽度
	LCD_Write_Command_P2(LC_GRH_STP,0x00,0x00);		//图形显示区首地址
	LCD_Write_Command_P2(LC_GRH_WID,LCD_WIDTH,0x00);//图形显示区宽度
	LCD_Write_Command_P1(LC_CGR_POS, CGRAMSTART >> 11);
	LCD_Write_Command(LC_CUR_SHP | 0x01);			//光标形状
	LCD_Write_Command(LC_MOD_OR);					//显示方式设置
	LCD_Write_Command(LC_DIS_SW  | 0x08);
	grhome = GRSTART;
	txthome = TXTSTART;
	return 0;
}

//-----------------------------------------------------------------
// 绘点函数
// 参数:点的坐标,模式1/0分别为显示与清除点
//-----------------------------------------------------------------
void Pixel(INT8U x,INT8U y, INT8U Mode) reentrant
{
	INT8U start_addr, dat;
	start_addr = 7 - ( x & 7);
	dat = LC_BIT_OP | start_addr;			//生成位操作命令绘点数据
	if (Mode) dat |= 0x08;
	Set_LCD_POS(y, x >> 3);
	LCD_Write_Command(LC_BIT_OP | dat);		// 写数据
}

//-----------------------------------------------------------------
// 两数交换
//-----------------------------------------------------------------
void Exchange(INT8U *a, INT8U *b)
{
	INT8U t;  t = *a; *a = *b; *b = t;
}

//-----------------------------------------------------------------
// 绘制直线函数
// 参数:起点与终点坐标,模式为显示(1)或清除(0),点阵不超过255*255)
//-----------------------------------------------------------------
void Line(INT8U x1,INT8U y1, INT8U x2,INT8U y2, bit Mode)
{
	INT8U x,y;		//绘点坐标
	float k,b;		//直线斜率与偏移	
	if( abs(y1 - y2) <= abs( x1 - x2) ) 
	{	k = ((float)y2 - y1) / ((float)x2 - x1) ; 
		b = y1 - k * x1; 
		if( x1 > x2 ) Exchange(&x1, &x2);
		for(x = x1;x <= x2; x++)
		{	y = (INT8U)(k * x + b);	Pixel(x, y, Mode);
		}
	}
	else 
	{	k = ((float)x2 - x1) / ((float)y2 - y1) ;
		b = x1 - k * y1; 
		if( y1 > y2 ) Exchange(&y1, &y2);
		for(y = y1;y <= y2; y++)
		{	x = (INT8U)(k * y + b);	Pixel( x , y,Mode );
		}
	}
}