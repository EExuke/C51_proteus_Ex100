//-----------------------------------------------------------------
//  名称: I2C接口8位精度多通道A／D与D／A转换器PCF8591件应用
//-----------------------------------------------------------------
//  说明: PCF8591是具有I2C总线接口的8位AD及DA转换器,有4路A/D转换输入
//	     和1路D/A转换模拟输出,本例中对4个通道进行递增A/D转换,转/换
//	     结果显示在LCD上,同时将转换后得到的值再逆向转换为模拟信号,
//	     经过Aout引脚输出到LED上,控制其亮度变化.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U unsigned char
#define INT16U  unsigned int
INT8U LCD_Line_1[] = {"0-0.00V  2-0.00V"};
INT8U LCD_Line_2[] = {"1-0.00V  3-0.00V"};
INT8U Recv_Buffer[4];			//数据接收缓冲(每通道一字节)
INT16U Voltage[]={'0','0','0'};	//数据分解为电压X.XX
extern void delay_ms(INT16U x);
extern void Initialize_LCD();
extern void LCD_ShowString(INT8U r, INT8U c,INT8U *str);
extern void ADC_PCF8591(INT8U CtrlByte,INT8U *R);
extern void DAC_PCF8591(INT8U CtrlByte,INT8U dat);
//-----------------------------------------------------------------
// 将模数转换后得到的值分解存入缓冲
//-----------------------------------------------------------------
void Convert_To_Voltage(INT8U val)
{	


}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	Initialize_LCD();
	while(1)
	{


	}
}