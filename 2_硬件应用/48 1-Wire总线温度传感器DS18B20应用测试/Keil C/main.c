//-----------------------------------------------------------------
//  ����: 1-Wire�����¶ȴ�����DS18B20Ӧ�ò���
//-----------------------------------------------------------------
//  ˵��: ���б���ʱ,����¶Ƚ�ʵʱˢ����ʾ��1602LCD��.
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
// ������
//-----------------------------------------------------------------
void main()
{
	float temp = 0.0;						//�����¶ȱ���
	LCD_Initialise(); 						//Һ����ʼ��
	LCD_ShowString(0,0,"  DS18B20 Test  ");	//��ʾ����
	LCD_ShowString(1,0,"  Waiting.....  ");	//��ʾ�ȴ���Ϣ
	Read_Temperature();						//Ԥ��ȡ�¶�
	delay_ms(1500);							//����ʱ
	while(1)								//ѭ����ȡ�¶Ȳ���ʾ
	{	



	}
}