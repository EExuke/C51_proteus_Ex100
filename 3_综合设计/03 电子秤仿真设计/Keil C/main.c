//-----------------------------------------------------------------
//  ����: ���ӳӷ������
//-----------------------------------------------------------------
//  ˵��: ��������ʱ,LCD��ʾ��ǰѹ��(δת��Ϊ����),������ļ۸�
//		ֱ�����ֵ���,LCD��ʾ������Ӧ�����.		
//
//-----------------------------------------------------------------
#define INT8U	unsigned char
#define INT16U	unsigned int
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
extern void Sounder();						//���������
extern void KeyBoard_Handle();				//���̴�������������ʾ����
extern void Compute_and_show_sum();
//Һ����غ���
extern void LCD_Initialize();
extern void LCD_ShowString(INT8U r, INT8U c,INT8U *str);
extern INT8U Get_CHx_AD_Value(INT8U ch); 	//ADC0832 A/Dת������
extern void delay_ms(INT16U x);	  			//��ʱ����
extern char disp_buffer_W[];				//Һ����ʾ����(����)
//ģ��ת�����,�ϴ�ת�����,ѹ��������
volatile int AD_Result, Pre_Result = 0, Pressure_Value = 0;
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main()
{
	LCD_Initialize();					//��ʼ��LCD
	//��һ����ʾP:W:��־(�۸�/����),����"P:"�����8��
	LCD_ShowString(0,0,(char*)"P:        W:");
	LCD_ShowString(1,0,(char*)"SUM($):");//�ڶ�����ʾSUM��־(���)
	while(1)
	{	





	}
}
