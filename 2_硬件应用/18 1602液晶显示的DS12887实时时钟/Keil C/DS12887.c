//-----------------------------------------------------------------
// ����: DS12887����ʱ��оƬ��������
//-----------------------------------------------------------------
#define INT8U  unsigned char
#define INT16U unsigned int
#include <reg51.h>
#include <intrins.h>
#include <absacc.h>
//-----------------------------------------------------------------
//DS12887�Ĵ�����ַ����
#define DS_SECOND			XBYTE[0xFE00]	//��
#define DS_SECOND_ALARM		XBYTE[0xFE01]	//�뱨��
#define DS_MINUTE			XBYTE[0xFE02]	//��
#define DS_MINUTE_ALARM		XBYTE[0xFE03]	//�ֱ���
#define DS_HOUR				XBYTE[0xFE04]	//ʱ
#define DS_HOUR_ALARM		XBYTE[0xFE05]	//ʱ����
#define DS_WEEK				XBYTE[0xFE06]	//����
#define DS_DAY				XBYTE[0xFE07]	//��
#define DS_MONTH			XBYTE[0xFE08]	//��
#define DS_YEAR				XBYTE[0xFE09]	//��(���2λ)
#define DS_CENTURY			XBYTE[0xFE32]	//����(���2λ)
#define CTRL_REGA			XBYTE[0xFE0A]	//���ƼĴ���A
#define CTRL_REGB			XBYTE[0xFE0B]	//���ƼĴ���B
#define CTRL_REGC			XBYTE[0xFE0C]	//���ƼĴ���C
#define CTRL_REGD			XBYTE[0xFE0D]	//���ƼĴ���D
//-----------------------------------------------------------------
#define CENTURY				0
#define YEAR				1
#define MONTH				2
#define DAY					3
#define WEEKDAY				4
#define HOUR				5
#define MINUTE				6
#define SECOND				7
#define SECOND_ALARM 		8
#define MINUTE_ALARM 		9
#define HOUR_ALARM			10
//-----------------------------------------------------------------
//����:��(0),��(1),ʱ(2),��(3),��(4),��2λ(5),�͸�2λ(6),����(7)
INT8U DateTime[8];
//0,1,2,3,4,5,6�ֱ��Ӧ����,��һ����
code char WEEK[][4] = {"SUN","MON","TUS","WEN","THU","FRI","SAT"};
//һ����ÿ���µ�����,2�µ���������ݾ����Ƿ��1
//code INT8U MonthsDays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
extern void delay_ms(INT16U);
#define BCD_TO_DEC(x) (x >> 4) * 10 + (x & 0x0F) //BCD��ת��Ϊʮ������
//-----------------------------------------------------------------
// �ж��Ƿ�Ϊ����
//-----------------------------------------------------------------
INT8U isLeapYear(INT16U y)
{ 
	return (y % 4 == 0 && y % 100 != 0 ) || (y % 400 == 0) ;
}

//-----------------------------------------------------------------
// ����2000.1.1��ʼ���κ�һ�������ڼ�(��֪1999.12.31������: w = 5)
// ����û��ͨ��������������������ڼ�,
// ��Ϊ�����������ܻᳬ��INT16U�ķ�Χ
// �˺������ڵ�������ʱ,�������ڼ������ڲ�д��ʱʹ��.
//-----------------------------------------------------------------
//INT8U GetWeek()
//{ 
//	INT16U i,Y = 2000 + BCD_TO_DEC(DateTime[5]), d = 0, w = 5; 
//	//��2000.1.1��ʼ�������ǰ��-1��.12.31�����ڼ�(w)
//	for (i = 2000; i < Y; i++)
//	{	d = isLeapYear(i) ? 366 : 365; w = (w + d) % 7 ;
//	}	
//	//�������ǰ�����õ��������Ǹ���ĵڼ���(d).
//	for (d = 0, i = 1; i < BCD_TO_DEC(DateTime[4]); i++) 
//	{	d += MonthsDays[i]; if (i == 2 && isLeapYear(Y)) d += 1;
//	}
//	d += BCD_TO_DEC(DateTime[3]);	//���ϵ���
//	//����w��d�������ǰ��/��/�������ڼ�,0~6��ʾ������,����һ,��,...,��
//	return (w + d) % 7; 
//}

//-----------------------------------------------------------------
// ��ȡʵʱʱ��
//-----------------------------------------------------------------
INT8U Read_DS(INT8U item) 
{ 
	switch (item) 
	{	case CENTURY:	return DS_CENTURY;	break;
		case YEAR:		return DS_YEAR;		break; 
		case MONTH:		return DS_MONTH;	break; 
		case WEEKDAY:	return DS_WEEK;		break;
		case DAY:		return DS_DAY;		break; 
		case HOUR:		return DS_HOUR;		break; 
		case MINUTE:	return DS_MINUTE;	break; 
		case SECOND:	return DS_SECOND;	break; 
	}
}

//-----------------------------------------------------------------
// дʵʱʱ��
//-----------------------------------------------------------------
void Write_DS(INT8U item,INT8U dat) 
{ 
	switch (item)
	{	case CENTURY:		DS_CENTURY = dat;		break; 
		case YEAR:			DS_YEAR = dat;			break; 
		case MONTH:			DS_MONTH = dat;			break; 
		case DAY:			DS_DAY = dat;			break; 
		case HOUR:			DS_HOUR = dat;			break; 
		case MINUTE:		DS_MINUTE = dat;		break; 
		case SECOND:		DS_SECOND = dat;		break; 
		case SECOND_ALARM:	DS_SECOND_ALARM = dat;	break; 
		case MINUTE_ALARM:	DS_MINUTE_ALARM = dat;	break; 
		case HOUR_ALARM:	DS_HOUR_ALARM = dat;	break; 
	}
}

//-----------------------------------------------------------------
// ��DS12887����
//-----------------------------------------------------------------
void Get_DateTime()
{







}

//-----------------------------------------------------------------
// DS12887��ʼ��
//-----------------------------------------------------------------
void DS12887_Init() 
{ 
	CTRL_REGA = 0x20;				//DV2.1.0(������),32.768k
	CTRL_REGB = 0x00;				//PIE-AIE-UIE=000,DM-24/12=00
	CTRL_REGC = 0x00;				//IRQF-PF-AF-UF = 0000
	Write_DS(CENTURY,0x20);			//Ĭ�Ͻ���ĸ�2λ��Ϊ20
}