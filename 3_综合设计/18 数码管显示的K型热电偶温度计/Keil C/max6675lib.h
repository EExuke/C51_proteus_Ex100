//-----------------------------------------------------------------
// ����: MAX6675ͷ�ļ�
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U   unsigned char
#define INT16U  unsigned int
#define INT32U  unsigned long
//MAX6675 SPI�ӿ����Ŷ���
sbit  CS  =  P1^0;			//Ƭѡ��������
sbit  CLK =  P1^1;			//����ʱ������
sbit  SO  =  P1^2;			//������������
extern INT8U K_Couple_ON;
//MAX6675��ʼ����������ȡ�¶����ݺ���
void   MAX6675_Init(); 
INT16U MAX6675_Read();