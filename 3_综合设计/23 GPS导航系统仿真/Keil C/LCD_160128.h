//-----------------------------------------------------------------
// PG160128Һ����������ͷ�ļ�(T6963C)
//-----------------------------------------------------------------
#include <intrins.h>
#include <stdio.h>
#include <math.h>
#include <absacc.h>
#include <string.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit RESET = P3^3; //��λ���Ŷ���
//-----------------------------------------------------------------
// �����������ASCII����
//-----------------------------------------------------------------
#define STX   0x02
#define ETX   0x03
#define EOT   0x04
#define ENQ   0x05
#define BS    0x08
#define CR    0x0D
#define LF    0x0A
#define DLE   0x10
#define ETB   0x17
#define SPACE 0x20
#define COMMA 0x2C
//-----------------------------------------------------------------
// ��������
//-----------------------------------------------------------------
#define TRUE  1
#define FALSE 0
#define HIGH  1
#define LOW   0
//-----------------------------------------------------------------
// T6963C �˿ڶ���
//-----------------------------------------------------------------
#define LCMDW XBYTE[0x8000] //���ݿ�
#define LCMCW XBYTE[0x8100] //�����
//-----------------------------------------------------------------
// ��ʾ�ڴ����
//-----------------------------------------------------------------
#define DISRAM_SIZE 0X7FFF  //������ʾram�Ĵ�С
#define TXTSTART    0x0000  //�����ı�������ʼ��ַ
#define GRSTART     0x6800  //����ͼ��������ʼ��ַ
#define CGRAMSTART  0x7800  //����CGRAM����ʼ��ַ
//-----------------------------------------------------------------
// T6963C �����
//-----------------------------------------------------------------
#define LC_CUR_POS  0x21    //���λ������
#define LC_CGR_POS  0x22    //CGRAMƫ�õ�ַ����
#define LC_ADD_POS  0x24    //��ַָ��λ��
#define LC_TXT_STP  0x40    //�ı�����ַ
#define LC_TXT_WID  0x41    //�ı������
#define LC_GRH_STP  0x42    //ͼ������ַ
#define LC_GRH_WID  0x43    //ͼ�������
#define LC_MOD_OR   0x80    //��ʾ��ʽ:�߼���
#define LC_MOD_XOR  0x81    //��ʾ��ʽ:�߼����
#define LC_MOD_AND  0x82    //��ʾ��ʽ:�߼���
#define LC_MOD_TCH  0x83    //��ʾ��ʽ:�ı�����
#define LC_DIS_SW   0x90    //��ʾ����:
                            //D0=1/0:�����˸����/����;
					 	    //D1=1/0:�����ʾ����/���ã�
					 	    //D2=1/0:�ı���ʾ����/���ã�
					 	    //D3=1/0:ͼ����ʾ����/���ã�
#define LC_CUR_SHP  0xA0    //�����״ѡ��:0xA0-0xA7��ʾ���ռ������
#define LC_AUT_WR   0xB0    //�Զ�д����
#define LC_AUT_RD   0xB1    //�Զ�������
#define LC_AUT_OVR  0xB2    //�Զ���/д����
#define LC_INC_WR   0xC0    //����д,��ַ��1
#define LC_INC_RD   0xC1    //���ݶ�,��ַ��1
#define LC_DEC_WR   0xC2    //����д,��ַ��1
#define LC_DEC_RD   0xC3    //���ݶ�,��ַ��1
#define LC_NOC_WR   0xC4    //����д,��ַ����
#define LC_NOC_RD   0xC5    //���ݶ�,��ַ����
#define LC_SCN_RD   0xE0    //����
#define LC_SCN_CP   0xE8    //������
#define LC_BIT_OP   0xF0    //λ����:D0-D2������D0-D7λ��D3��1��λ��0�����
//-----------------------------------------------------------------
// LCD��ʾ��غ���
//-----------------------------------------------------------------
INT8U Status_BIT_01();   //״̬λSTA1,STA0�жϣ���дָ��Ͷ�д���ݣ�
INT8U Status_BIT_3();    //״̬λST3�жϣ������Զ�д״̬��
INT8U Status_BIT_01();   //״̬λSTA1,STA0�жϣ���дָ��Ͷ�д���ݣ�
INT8U Status_BIT_3();    //״̬λST3�жϣ������Զ�д״̬��
INT8U LCD_Write_Command(INT8U cmd);                              //д�޲�����ָ��
INT8U LCD_Write_Command_P1(INT8U cmd,INT8U para1);               //д��������ָ��
INT8U LCD_Write_Command_P2(INT8U cmd,INT8U para1,INT8U para2);   //д˫������ָ��
INT8U LCD_Write_Data(INT8U dat);                                 //д����
INT8U LCD_Read_Data();                                           //������
void  LCD_Initialise();                                          //LCD��ʼ��
void  Clear_Screen();                                            //����
void  Set_LCD_POS(INT8U row, INT8U col);                         //���õ�ǰ��ַ
void  OutToLCD(INT8U Dat,INT8U x,INT8U y);                       //�����Һ��
void  Line(INT8U x1, INT8U y1, INT8U x2, INT8U y2, INT8U Mode);  //����ֱ��
void  Pixel(INT8U x,INT8U y, INT8U Mode);                        //���
void  Draw_Image(INT8U *G_Buffer, INT8U Start_Row, INT8U Start_Col);//����ͼ��
void  Disp_Str_at_xy(INT8U x,INT8U y,char buf[]);                //��ָ��λ����ʾ�ַ���
