//-----------------------------------------------------------------
// LM041Һ����������ʾ����
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit RS = P2^0;  //�Ĵ���ѡ����
sbit RW = P2^1;	 //��/д������
sbit EN = P2^2;	 //ʹ�ܿ�����
//-----------------------------------------------------------------
// ��ʱ
//-----------------------------------------------------------------
void delay_ms(INT16U ms)
{
	INT8U i; while(ms--) for(i = 0; i < 120; i++);
}

//-----------------------------------------------------------------
// æ���
//-----------------------------------------------------------------
INT8U Busy_Check()
{


}

//-----------------------------------------------------------------
// дLCD����
//-----------------------------------------------------------------
void Write_LCD_Command(INT8U cmd)
{


}

//-----------------------------------------------------------------
// ��������
//-----------------------------------------------------------------
void Write_LCD_Data(INT8U dat)
{


}

//-----------------------------------------------------------------
// LCD��ʼ��
//-----------------------------------------------------------------
void LCD_Initialize()
{


}
//-----------------------------------------------------------------
// ��ʾ�ַ���
//-----------------------------------------------------------------
void LCD_ShowString(INT8U r, INT8U c,INT8U *str)
{


}