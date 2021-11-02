//-----------------------------------------------------------------
// ����: PCF8583ʵʱʱ����������
//-----------------------------------------------------------------
#define INT8U  unsigned char
#define INT16U unsigned int
#include <reg51.h>
#include <intrins.h>
#include <string.h>
sbit SCL = P2^6;					//IICʱ����
sbit SDA = P2^7;					//IIC������
#include "I2C.h"					//IIC����ͨ�ú꼰����
#include "PCF8583.h"				//����ʱ��оƬ��������ͷ�ļ�

//0,1,2,3,4,5,6�ֱ��Ӧ����,��һ����
char WEEK[][4] = {"SUN","MON","TUS","WEN","THU","FRI","SAT"};
//����ȡ��PCF8583���ݼ�ת���������ʱ������
INT8U PCF8583_DATA[5],DateTime[7];

//-----------------------------------------------------------------
// ��PCF8583ָ����ַ�����ֽڵ�buf����
//-----------------------------------------------------------------
void Read_PCF8583(INT8U addr,INT8U *buf,INT8U n)
{
	INT8U i=0;

	IIC_Start();
	IIC_WriteByte(PCF8583_ADDR_WR);
	IIC_WriteByte(addr);

	IIC_Start();
	IIC_WriteByte(PCF8583_ADDR_RD);
	for (i=0; i<n-1; i++) {
		buf[i] = IIC_ReadByte(); //������һ�ֽ�
		IIC_Ack();    //��������Ӧ��
	}
	buf[n-1] = IIC_ReadByte(); //������ȡ���һ�ֽ�
	IIC_NAck(); //�������ͷ�Ӧ��λ
	IIC_Stop(); //IICֹͣ
}

//-----------------------------------------------------------------
// ��ȡ7�ֽ�PCF8583ʱ�����ݲ�����DateTime����
//-----------------------------------------------------------------
void GetDateTime()
{
	//skip control byte 0x00 and 1/100s byte 0x01
	//read 5 byte from 0x02(sec) to PCF8583_DATA
	Read_PCF8583(0x02, PCF8583_DATA, 5);
	//format date data
	DateTime[0] = PCF8583_DATA[0]; //sec
	DateTime[1] = PCF8583_DATA[1]; //min
	DateTime[2] = PCF8583_DATA[2]; //hour
	DateTime[3] = PCF8583_DATA[3]; //day
	DateTime[4] = PCF8583_DATA[4]; //month
	DateTime[5] = PCF8583_DATA[3]; //year
	DateTime[6] = PCF8583_DATA[4]; //week
}
