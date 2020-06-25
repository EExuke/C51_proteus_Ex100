//-----------------------------------------------------------------
//  ����: Nokia7110Һ��ͷ�ļ�(SED1565)
//-----------------------------------------------------------------
#define INT8U   unsigned char
#define INT16U  unsigned int
#define _XTAL_FREQ 4000000UL
//-----------------------------------------------------------------
// SEG1565��ʾ��ַ��������
//-----------------------------------------------------------------
#define PAGE    0xB0  //ҳ��ַ
//SED1565���ֱ���Ϊ132*65,������Nokia7710ʱ,����ʼ��Ϊ��18��,������0��
//����SED1565���е�ַ��4λ����Ϊ0001XXXX,��3λ����Ϊ0000XXXX
//����ʼ��(18->0x12)��ϵ��е�ַ��4λ���4λ�����,�ɵ�:0001-0001��0000-0010
//��0x11��0x02,�������¶���
#define COL_H4  0x11  //�е�ַ����λ
#define COL_L4  0x02  //�е�ַ����λ
#define LINE    0x40  //�е�ַ
//-----------------------------------------------------------------
// ��������
//-----------------------------------------------------------------
void SPI_MasterInit();
void Nokia_Reset();
void Nokia_Init();
void Nokia_CLS();
void Write_Norkia_Command(INT8U cmd);
void Write_Nokia_Data(INT8U cd);
void Set_Nokia_LCD_POS(INT8U page, INT8U col) ;
void Show_Char(INT8U c, INT8U reverse); 
void Show_String(INT8U *str,INT8U reverse);	