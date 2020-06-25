//-----------------------------------------------------------------
//  ����: LGM12864Һ��ͷ�ļ�
//-----------------------------------------------------------------
#define INT8U   unsigned char
#define INT16U  unsigned int
//LCD��ʼ��/ҳ/��ָ���
#define LCD_START_ROW	0xC0		//��ʼ��
#define LCD_PAGE		0xB8		//ҳָ��
#define LCD_COL			0x40		//��ָ��
//Һ����������
sbit E 	=  P3^0;					//ʹ�ܿ�����
sbit R_W = P3^1;					//��д������
sbit D_I = P3^2;					//����/ָ��ѡ����
sbit CS1 = P3^3;					//�Ұ���ѡ��
sbit CS2 = P3^4;					//�Ұ���ѡ��
sbit RST = P3^5;					//��λ
//æ��־λ
sbit BUSY_STATUS = P1^7;			//æ��־λ
//Һ���˿�
#define LCD_PORT  P1				//Һ�����ݶ˿�
//-----------------------------------------------------------------
// ��������
//-----------------------------------------------------------------
void LCD_Initialize();
void Wait_LCD_Ready();
void ClearScreen();
void LCD_Write_Command(INT8U cmd);
void LCD_Write_Data(INT8U dat);
void Common_Show(INT8U P,INT8U L,INT8U W,INT8U *r);
void Display_A_Char_8X16(INT8U P,INT8U L,INT8U *M);
void Display_A_WORD(INT8U P,INT8U L,INT8U *M);
void Display_A_WORD_String(INT8U P,INT8U L,INT8U C,INT8U *M);