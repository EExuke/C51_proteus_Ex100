//-----------------------------------------------------------------
// ����:��8051+1601LCD��Ƶ����ͼ�����
//-----------------------------------------------------------------
// ˵��: ������LABCENTER ELECTRONICS��˾�ṩ,ԭʼ������C������
//		��д,���������д���ȫ���ı����C������벢�������.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"
#define INT8U  unsigned char
#define INT16U unsigned int
static long a,b;			//��ǰ�������ǰ������������
static char CurrKeyChar;	//��ǰ�����ַ�
static char Last_OP;		//�������Ĳ�����
static char Last_Char;		//�������ǰһ�ַ�
static char result;			//��ǰ����Ľ��״̬
//��ʾ����,�������뻺�弰�������뻺������������
static char xdata outputbuffer[MAX_DISPLAY_CHAR+1];
static char xdata NumberStr[MAX_DISPLAY_CHAR+1];
static char xdata NumberIdx;
//-----------------------------------------------------------------
// ������ʾ�����Ƿ�Խ��
//-----------------------------------------------------------------
int calc_chkerror(long num) { return labs(num) <= 9999999? OK : ERROR;}
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main() 
{  


}	

//-----------------------------------------------------------------
// ��������������������㴦��
//-----------------------------------------------------------------
void Operator_Process(char OP)
{ 



}