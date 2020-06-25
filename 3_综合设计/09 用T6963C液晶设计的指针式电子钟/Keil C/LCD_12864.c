//-----------------------------------------------------------------
// LCD��ʾ���Ƴ���
//-----------------------------------------------------------------
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <intrins.h>
#include <absacc.h>
#include <string.h>
#include <LCD_12864.h>
INT8U code LCD_WIDTH  = 16;	//��128����(��16�ֽ� * 8 = 128����)
INT8U code LCD_HEIGHT = 64;	//��64����
INT8U gCurRow,gCurCol;	// ͼ�ε�ǰ�С��д洢���и�16�㣬�п�8��
INT8U tCurRow,tCurCol;	// �ı���ǰ�С��д洢���и�8�� ���п�8��
INT8U ShowModeSW;		// ��ǰ��ʾģʽ
INT16U  txthome,grhome;
//-----------------------------------------------------------------
// LCD������غ���
//-----------------------------------------------------------------
INT8U Status_BIT_01();	// ״̬λSTA1,STA0�жϣ���дָ��Ͷ�д���ݣ�
INT8U Status_BIT_3();	// ״̬λST3�жϣ������Զ�д״̬��
INT8U LCD_Write_Command(INT8U cmd);							//д�޲�����ָ��
INT8U LCD_Write_Command_P1(INT8U cmd,INT8U para1);			//д��������ָ��
INT8U LCD_Write_Command_P2(INT8U cmd,INT8U para1,INT8U para2);//д˫������ָ��
INT8U LCD_Write_Data(INT8U dat);							//д����
INT8U LCD_Read_Data();										//������
void cls();													//����
char LCD_Initialise();										//LCD��ʼ��
void SetShowMode(INT8U mode);								//������ʾģʽ
void Set_LCD_POS(INT8U row, INT8U col) reentrant;			//���õ�ǰ��ַ
void Line(INT8U x1, INT8U y1, INT8U x2, INT8U y2, bit Mode);//����ֱ��
void Pixel(INT8U x,INT8U y, INT8U Mode) reentrant;			//���
INT8U gCurRow,gCurCol;										//ͼ�ε�ǰ��,��
INT8U tCurRow,tCurCol;										//�ı���ǰ��,��
INT16U  txthome,grhome;
//-----------------------------------------------------------------
// ״̬λSTA1,STA0�ж�(��дָ��Ͷ�д����)
//-----------------------------------------------------------------
INT8U Status_BIT_01() 
{


}

//-----------------------------------------------------------------
// ״̬λST3�ж�(�����Զ�д״̬)
//-----------------------------------------------------------------
INT8U Status_BIT_3() 
{


}

//-----------------------------------------------------------------
// д˫������ָ��
//-----------------------------------------------------------------
INT8U LCD_Write_Command_P2(INT8U cmd,INT8U para1,INT8U para2) 
{


}

//-----------------------------------------------------------------
// д��������ָ��
//-----------------------------------------------------------------
INT8U LCD_Write_Command_P1(INT8U cmd,INT8U para1) 
{


}

//-----------------------------------------------------------------
// д�޲�����ָ��
//-----------------------------------------------------------------
INT8U LCD_Write_Command(INT8U cmd) 
{


}

//-----------------------------------------------------------------
// д����
//-----------------------------------------------------------------
INT8U LCD_Write_Data(INT8U dat) 
{


}

//-----------------------------------------------------------------
// ���õ�ǰ��ַ
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
// ����
//-----------------------------------------------------------------
void cls()
{
	INT16U i;	
	LCD_Write_Command_P2(LC_ADD_POS,0x00,0x00);	//�õ�ַָ��
	LCD_Write_Command(LC_AUT_WR);				//�Զ�д
	for(i = 0;i < 0x2000; i++)
	{	Status_BIT_3();
		LCD_Write_Data(0x00);					//д����
	}
	LCD_Write_Command(LC_AUT_OVR);				//�Զ�д����
	LCD_Write_Command_P2(LC_ADD_POS,0x00,0x00);	//���õ�ַָ��
	gCurRow = 0;
	gCurCol = 0;
}

//-----------------------------------------------------------------
// LCD��ʼ��
//-----------------------------------------------------------------
char LCD_Initialise()
{
	RESET = 0;
	RESET = 1;
	LCD_Write_Command_P2(LC_TXT_STP,0x00,0x00);		//�ı���ʾ���׵�ַ
	LCD_Write_Command_P2(LC_TXT_WID,LCD_WIDTH,0x00);//�ı���ʾ�����
	LCD_Write_Command_P2(LC_GRH_STP,0x00,0x00);		//ͼ����ʾ���׵�ַ
	LCD_Write_Command_P2(LC_GRH_WID,LCD_WIDTH,0x00);//ͼ����ʾ�����
	LCD_Write_Command_P1(LC_CGR_POS, CGRAMSTART >> 11);
	LCD_Write_Command(LC_CUR_SHP | 0x01);			//�����״
	LCD_Write_Command(LC_MOD_OR);					//��ʾ��ʽ����
	LCD_Write_Command(LC_DIS_SW  | 0x08);
	grhome = GRSTART;
	txthome = TXTSTART;
	return 0;
}

//-----------------------------------------------------------------
// ��㺯��
// ����:�������,ģʽ1/0�ֱ�Ϊ��ʾ�������
//-----------------------------------------------------------------
void Pixel(INT8U x,INT8U y, INT8U Mode) reentrant
{
	INT8U start_addr, dat;
	start_addr = 7 - ( x & 7);
	dat = LC_BIT_OP | start_addr;			//����λ��������������
	if (Mode) dat |= 0x08;
	Set_LCD_POS(y, x >> 3);
	LCD_Write_Command(LC_BIT_OP | dat);		// д����
}

//-----------------------------------------------------------------
// ��������
//-----------------------------------------------------------------
void Exchange(INT8U *a, INT8U *b)
{
	INT8U t;  t = *a; *a = *b; *b = t;
}

//-----------------------------------------------------------------
// ����ֱ�ߺ���
// ����:������յ�����,ģʽΪ��ʾ(1)�����(0),���󲻳���255*255)
//-----------------------------------------------------------------
void Line(INT8U x1,INT8U y1, INT8U x2,INT8U y2, bit Mode)
{
	INT8U x,y;		//�������
	float k,b;		//ֱ��б����ƫ��	
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