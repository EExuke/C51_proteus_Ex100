//-----------------------------------------------------------------
//  ����: LCD1602Һ����������ͷ�ļ�
//-----------------------------------------------------------------
//LCD���Ŷ���
sbit RS = P2^0;			//LCD�Ĵ���ѡ��
sbit RW = P2^1;			//LCD��д����
sbit EN = P2^2;			//LCDʹ�ܿ���
//Һ���˿ڶ���
#define LCD_PORT P2		//Һ���˿�(P2��4λ)
//LCD��غ���
void LCD_Busy_Wait();					//æ�ȴ�
void Write_LCD_Data(INT8U dat);			//��LCDд����
void Write_LCD_Command(INT8U cmd);		//дLCDָ��
void Initialize_LCD();					//LCD��ʼ��
void LCD_ShowString(INT8U r, INT8U c,char *str);//��LCD����ʾ�ַ���