//-----------------------------------------------------------------
//  ����: 1602�ַ�Һ��������8λģʽֱ��������ʾ
//-----------------------------------------------------------------
//  ˵��: ����Һ��ʵ����������ʾ����,�ֱ�Ϊˮƽ����,�������ʾ���
//        ����ʽ,ȫ����ַ���ʾ,CGRAM�Զ����ַ���ʾ.
//	  
//-----------------------------------------------------------------
#include <reg51.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit SW1 = P3^0;		//ˮƽˮƽ������ʾ
sbit SW2 = P3^1;		//�������ʾ�������ʽ
sbit SW3 = P3^2;		//ȫ����ַ���ʾ
sbit SW4 = P3^3;		//CGRAM�Զ����ַ���ʾ
INT8U code msg[] =		//��������ʾ���ַ���(�ַ�����ǰ�����16���ո�)
"                you are going to spend even more time working on the schematic ?";
//-----------------------------------------------------------------
extern delay_ms(INT16U x);
extern void Initialize_LCD();
extern void Write_LCD_Data(INT8U dat);
extern void Write_LCD_Command(INT8U cmd);
extern void Busy_Wait();
extern void LCD_ShowString(INT8U,INT8U,INT8U *);
//-----------------------------------------------------------------
//�Զ���CGRAM�ַ���ͼ���������(������,ÿ���ַ�������8��)
INT8U code CGRAM_Dat1[][8] = //7��ͼ����ţ��߶���1~7������ľ��Σ�
{	{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00},	//1��
	{0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x00},	//2��
	{0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x00},	//3��
	{0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x00},	//4��
	{0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x00},	//5��
	{0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00},	//6��
	{0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00} 	//7��
};
INT8U code CGRAM_Dat2[][8] = //5�������ַ�
{	{0x08,0x0F,0x12,0x0F,0x0A,0x1F,0x02,0x00},	//��
	{0x0F,0x09,0x0F,0x09,0x0F,0x09,0x13,0x00},	//��
	{0x0F,0x09,0x09,0x0F,0x09,0x09,0x0F,0x00},	//��
	{0x1F,0x0A,0x1F,0x0A,0x0A,0x0A,0x12,0x00},	//��
	{0x0A,0x1F,0x04,0x1F,0x04,0x0A,0x11,0x00} 	//��
};
//-----------------------------------------------------------------
// ���Զ����ַ�����д��CGRAM
//-----------------------------------------------------------------
void Write_CGRAM(INT8U g[][8], INT8U n)
{
	INT8U i, j;
	Write_LCD_Command(0x04);			//����CGRAM��ַΪ0x40
	for (i = 0; i < n; i++)				//n���Զ����ַ�
		for(j = 0; j < 8; j++)			//ÿ���ַ�8�ֽڵ�������
			Write_LCD_Data(g[i][j]);	//д��CGRAM
}

//-----------------------------------------------------------------
// SW1: ˮƽ������ʾ�ַ���
//-----------------------------------------------------------------
void H_Scroll_Display()
{
	INT16U i;
	Write_LCD_Command(0x0C);					//����ʾ���ع��
	LCD_ShowString(0, 0, "LCD1602 DEMO - 1");	//��0����ʾ����
	LOOP1:
	for (i = 0; i < strlen(msg); i++)			//������������ַ�
	{	
		LCD_ShowString(1, 0, msg + i);			//msg+1ʵ��ȡ�ַ�ָ�����
		delay_ms(50);
		if (SW1)
			return;								//δ����SW1λ��ʱ��������
	}
	delay_ms(1000);								//��ʾ�������ַ�����ͣ1�룬Ȼ�����
	goto LOOP1;
}

//-----------------------------------------------------------------
// SW2: �������ʾ�������ʽ
//-----------------------------------------------------------------
void Cursor_Display()
{
	INT8U i;
	int a, b,;
	char disp_buff[17];
	
	Write_LCD_Command(0x0C);								//����ʾ���ع��
	LCD_ShowString(0, 0, "LCD1602 DEMO - 2");				//��0����ʾ����
	LCD_ShowString(1, 0, "               ");				//��յ�1�У����16���ո�
	Write_LCD_Command(0x0F);								//����ʾ������꣬�����˸
	srand(TH0);												//��TH0��Ϊ�������
	while(1)
	{
		if (SW2)			//δ����SW2λ��ʱ��������
			return;
		a = rand() % 100;	//����������100�������a, b
		b = rand() % 100;
		sprintf(disp_buff, "%2d + %2d = %2d", a, b, a+b);	//��������ʽ���������ַ���
		Write_LCD_Command(0xC0);							//��ʾλ�ö�λ�ڵ�1�п�ʼλ��
		for (i = 0; i < 16; i++)							//ѭ������������ʽ�ַ�
		{
			if (disp_buff[i])
				Write_LCD_Data(disp_buff[i]);
			else
				Write_LCD_Data(' ');
			delay_ms(100);
		}
		delay_ms(200);										//��ʾ��һ������ʽ����ͣ200ms
		LCD_ShowString(1, 0, "                ");			//��ո��У����16���ո�
	}
}

//-----------------------------------------------------------------
// SW3: ȫ����ַ���ʾ
//-----------------------------------------------------------------
void Show_All_Inter_Chars()
{
	INT8U i, j = 0;
	
	Write_LCD_Command(0x0C);					//����ʾ���ع��
	LCD_ShowString(0, 0, LCD1602 DEMO - 3");	//��0����ʾ����
	LCD_ShowString(1, 0, "                ");	//��һ�����
	LOOP3:
	Write_LCD_Command(0xC0);					//��ʾλ�ö�λ�ڵ�1�п�ʼλ��
	/* ��ȫ�����ʾ����ΧΪ0x20~0xFF������0xFF�����Ϊ0x00��ѭ������ */
	for (i = 0x20; i != 0x00; i++)
	{
		if (i >= 0x80 && i <= 0x9F)
			continue;					//�����հ����ַ�
		if ((++j) % 16 == 0)			//�ж��Ƿ���ʾ��һ��
		{
			delay_ms(500);
			LCD_ShowString(1, 0, "                ");
			Write_LCD_Command(0xC0);			//��ʾλ�ö�λ�ڵ�1�п�ʼλ��
			j = 0;								//��ʾ�ַ�������������
		}
		Write_LCD_Data(i);				//�ڵ�ǰλ����ʾ����Ϊi���ַ�
		delay_ms(500);			
		if (SW3)
			return;
	}
	delay_ms(500);
	goto LOOP3;
}

//-----------------------------------------------------------------
// SW4: CGRAM�Զ����ַ���ʾ
//-----------------------------------------------------------------
void Display_CGRAM_Chars()
{
	INT8U i, j = 0;
	
	Write_LCD_Command(0x0C);					//����ʾ���ع��
	LCD_ShowString(0, 0, "LCD1602 DEMO - 4");	//��0����ʾ����
	LOOP4:
	/* ��1���Զ���CGRAM�ַ���ʾ */
	LCD_ShowString(1, 0, "                ");	//��1�����
	Write_CGRAM(CGRAM_Dat1, 7);					//��1���Զ����ַ�����д��CGRAM
	Write_LCD_Command(0xC0 | 1);				//��ʾλ�ö�λ�ڵ�1�п�ʼλ��
	for (i = 6; i != 0xFF; i--)					//7��~1��ʽ���������ʾ
	{
		Write_LCD_Data(i);					//�ڵ�ǰλ����ʾ����Ϊi���ַ�
		delay_ms(50);
		if (SW4)
			return;
	}
	for (i = 0; i < 6; i++)						//1��~7��ʽ���������ʾ
	{
		Write_LCD_Data(i);					//�ڵ�ǰλ����ʾ����Ϊi���ַ�
		delay_ms(50);
		if (SW4)
			return;
	}	
	delay_ms(500);
	/* ��2���Զ���CGRAM�ַ���ʾ */
	LCD_ShowString(1, 0, "                ");
	Write_CGRAM(CGRAM_Dat2, 5);					//��2���Զ����ַ�����д��CGRAM
	Write_LCD_Command(0xC0 | 4);				//��ʾλ�ö�λ�ڵ�1��4��
	for (i = 0; i <= 4; i++)					//5���Զ��庺���ַ���ʾ
	{
		Write_LCD_Data(i);					//�ڵ�ǰλ����ʾ����Ϊi���ַ�
		Write_LCD_Data(' ');
		delay_ms(100);
		if (SW4)
			return;
	}
	delay_ms(1000);
	goto LOOP4;				//����
}

//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main()
{
	P3 = 0xFF;						//P3�˿���Ϊ0xFF
	Initialize_LCD();				//��ʼ��LCD
	TR0  = 1;						//������ʱ��,�ṩ�������
	while(1)						//��ѭ������ʵ�ָ�����ʾ
	{	if (SW1 == 0) H_Scroll_Display();
		if (SW2 == 0) Cursor_Display();
		if (SW3 == 0) Show_All_Inter_Chars();
		if (SW4 == 0) Display_CGRAM_Chars();
	}
}