//-----------------------------------------------------------------
//  名称: 1-Wire总线温度传感器DS18B20应用测试
//-----------------------------------------------------------------
//  说明: 运行本例时,外界温度将实时刷新显示在1602LCD上.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#define INT8U  unsigned char
#define INT16U unsigned int
INT8U Temp_Disp_Buff[17];
extern INT8U Temp_Value[];
extern void LCD_Initialise();
extern void LCD_ShowString(INT8U r, INT8U c,INT8U *str);
extern void delay_ms(INT16U);
extern INT8U Read_Temperature();
//-----------------------------------------------------------------
// 主函数
//-----------------------------------------------------------------
void main()
{
	float temp = 0.0;						//浮点温度变量
	LCD_Initialise(); 						//液晶初始化
	LCD_ShowString(0,0,"  DS18B20 Test  ");	//显示标题
	LCD_ShowString(1,0,"  Waiting.....  ");	//显示等待信息
	Read_Temperature();						//预读取温度
	delay_ms(1500);							//长延时
	while(1)								//循环读取温度并显示
	{	



	}
}