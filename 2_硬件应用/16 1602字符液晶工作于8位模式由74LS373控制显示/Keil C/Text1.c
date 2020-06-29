//-----------------------------------------------------------------
//  ����: 1602�ַ�Һ��������8λģʽ��74LS373������ʾ
//-----------------------------------------------------------------
//  ˵��: LCD1602Һ��ͨ����չ�ӿ�������ʾ,Һ�����������зֱ������ʾ
//        ָ�����ַ���.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <absacc.h>
#include <string.h>
#define INT8U  unsigned char
#define INT16U unsigned int
#define LCD_CMD_WR			0x00	//д����(RW,RS=00)
#define LCD_DATA_WR			0x01	//д����(RW,RS=01)
#define LCD_BUSY_RD			0x02	//��æ״̬(RW,RS=10)
#define LCD_DATA_RD			0x03	//������
#define LCD_CLS				0x01	//����
#define LCD_HOME			0x02	//����λ
#define LCD_SETMODE			0x04	//����ģʽ
#define LCD_SETVISIBLE		0x08	//����ʾ
#define LCD_SHIFT			0x10	//��λ��ʽ
#define LCD_SETFUNCTION		0x20	//��������
#define LCD_SETCGADDR		0x40	//����CGRAM��ַ
#define LCD_SETDDADDR		0x80	//����DDRAM��ַ
//����ʾ�ַ���,ǰ����������ɿո�
code char *s1 = "                 LCD1602 TEST....";
code char *s2 = "                 Port Extension..";
//-----------------------------------------------------------------
// ��ʱ����
//-----------------------------------------------------------------
void delay_ms(INT16U x) 
{
	INT8U t; while(x--) for(t = 0; t < 120; t++);
}

//-----------------------------------------------------------------
// LCDæ�ȴ�
//-----------------------------------------------------------------
void Busy_Wait()
{
	INT8U LCD_Status;
	do
	{
		LCD_Status = XBYTE[LCD_BUSY_RD];
	} while (LCD_Status & 0x80);
	
}

//-----------------------------------------------------------------
// дLCD����
//-----------------------------------------------------------------
void Write_LCD_Command(INT8U cmd)
{
	XBYTE[LCD_CMD_WR] = cmd;
	Busy_Wait();
}

//-----------------------------------------------------------------
// ��������
//-----------------------------------------------------------------
void Write_LCD_Data(INT8U dat)
{
	XBYTE[LCD_DATA_WR] = dat;
	Busy_Wait();
}


//-----------------------------------------------------------------
// ��ָ������λ����ʾ�ַ���
//-----------------------------------------------------------------
void LCD_Show_String(INT8U r, INT8U c, char *s)
{
	INT8U i = 0;
	INT8U DDRAM[] = {LCD_SETDDADDR,LCD_SETDDADDR|0x40}; //��0x80,0xC0
	Write_LCD_Command(DDRAM[r] | c);
	while (s[i] && i < 16) Write_LCD_Data(s[i++]);
	for (; i < 16; i++) Write_LCD_Data(' ');
}

//-----------------------------------------------------------------
// LCD��ʼ��
//-----------------------------------------------------------------
void LCD_Initialise()
{
	Write_LCD_Command(0x38);	Write_LCD_Command(0x0C);
}

//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main()
{
	INT8U i;
	LCD_Initialise();					//LCD��ʼ��
	while(1)
	{
		//line 1
		for (i = 0; i <= strlen(s1) - 16; i++)
		{
			LCD_Show_String(0, 0, s1+i);
			delay_ms(20);
		}
		//line 2
		for (i = 0; i <= strlen(s2) - 16; i++)
		{
			LCD_Show_String(1, 0, s2+i);
			delay_ms(100);
		}
	}
}
