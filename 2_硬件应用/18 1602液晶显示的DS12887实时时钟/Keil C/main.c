//-----------------------------------------------------------------
//  ����: 1602Һ����ʾDS12887ʵʱʱ��
//-----------------------------------------------------------------
//  ˵��: �������ȡDS12887ʵʱʱ��,ˢ����ʾ��20*4LCD.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <absacc.h>
#include <string.h>
#define INT8U  unsigned char
#define INT16U unsigned int
//-----------------------------------------------------------------
#define LCD_CMD_WR			0xFF00	//д����(RW,RS=00)
#define LCD_DATA_WR			0xFF01	//д����(RW,RS=01)
#define LCD_BUSY_RD			0xFF02	//��æ״̬
#define LCD_DATA_RD			0xFF03	//������
#define LCD_CLS				0xFF01	//����
#define LCD_HOME			0xFF02	//����λ
#define LCD_SETMODE			0xFF04	//����ģʽ
#define LCD_SETVISIBLE		0xFF08	//����ʾ
#define LCD_SHIFT			0xFF10	//��λ��ʽ
#define LCD_SETFUNCTION		0xFF20	//��������
#define LCD_SETCGADDR		0xFF40	//����CGRAM��ַ
#define LCD_SETDDADDR		0xFF80	//����DDRAM��ַ
//-----------------------------------------------------------------
extern INT8U DateTime[];
extern code char WEEK[][4];
extern void DS12887_Init();
extern void Get_DateTime();
char buf1[] = "DATE: 0000-00-00";
char buf2[] = "TIME: 00-00-00 AM";
char buf3[] = "WEEK: XXX"; 
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
	do {
		LCD_Status = XBYTE[LCD_BUSY_RD];
	} while (LCD_Status);
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
// ��ָ������λ����ʾ�ֽڷ�
//-----------------------------------------------------------------
void LCD_ShowString(INT8U r, INT8U c, char *s)
{
	INT8U i = 0;
	INT8U DDRAM[] = {0x80,0xC0,0x94,0xD4}; //LM044L�����׵�ַ(��4��)
	Write_LCD_Command(DDRAM[r] | c);
	while (s[i] && i < 20) Write_LCD_Data(s[i++]);
	for (; i < 20; i++) Write_LCD_Data(' ');
}

//-----------------------------------------------------------------
// LCD��ʼ��
//-----------------------------------------------------------------
void LCD_Initialise()
{
	Write_LCD_Command(0x38);
	Write_LCD_Command(0x0C);
}

//-----------------------------------------------------------------
// ������ʱ��ֵת��Ϊ�����ַ�(BCD->DEC)
//-----------------------------------------------------------------
void Format_DateTime(INT8U d, INT8U *a)
{
	*a = (d >> 4) + '0';
	*(a+1) = (d & 0x0F) + '0';
}

//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main()
{
	DS12887_Init();									//DS12887��ʼ��
	LCD_Initialise();								//LCD��ʼ��
	LCD_ShowString(0,0,"DS12887 Real Clock");
	while(1)
	{
		Get_DateTime();

		Format_DateTime(DateTime[6], buf1 + 6);
		Format_DateTime(DateTime[5], buf1 + 8);
		Format_DateTime(DateTime[4], buf1 + 11);
		Format_DateTime(DateTime[3], buf1 + 14);
		LCD_ShowString(1, 0, buf1);

		Format_DateTime(DateTime[2] & 0x7F, buf2 + 6);
		Format_DateTime(DateTime[1], buf2 + 9);
		Format_DateTime(DateTime[0], buf2 + 12);

		if (DateTime[2] & 0x80) {
			buf2[15] = 'P';
		} else {
			buf2[15] = 'A';
		}
		LCD_ShowString(2, 0, buf2);

		strcpy(buf3 + 6, WEEK[DateTime[7] - 1]);
		LCD_ShowString(3, 0, buf3);
		delay_ms(50);
	}
}

