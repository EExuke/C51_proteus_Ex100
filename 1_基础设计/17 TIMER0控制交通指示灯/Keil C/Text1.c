//-----------------------------------------------------------------
//  ����: TIMER0���ƽ�ָͨʾ��
//-----------------------------------------------------------------
//  ˵��: �������̵���5���,�Ƶ���˸,��˸5�κ������,
//		�������,�ϱ����ɺ�Ʊ�Ϊ�̵�,5����ϱ���Ƶ���˸, 
//		��˸5�κ������,�������̵���,�������.
//		������ʱ����ý϶���Ϊ�˵��Ե�ʱ���ܽϿ�Ĺ۲쵽����Ч��.
//				
//-----------------------------------------------------------------
#include <reg51.h>
#define INT8U unsigned char
#define INT16U  unsigned int
sbit	RED_A		=  P0^0;	//������ָʾ��
sbit	YELLOW_A	=  P0^1;
sbit	GREEN_A		=  P0^2; 
sbit	RED_B		=  P0^3;	//�ϱ���ָʾ��
sbit	YELLOW_B	=  P0^4;
sbit	GREEN_B		=  P0^5;
//��ʱ����,��˸����,�������ͱ���
INT8U Time_Count = 0, Flash_Count = 0, Operation_Type = 1; 
//-----------------------------------------------------------------
// T0�ж��ӳ���	 
//-----------------------------------------------------------------
void T0_INT () interrupt 1
{
	TH0	= - 50000 / 256;
	TL0 = - 50000 % 256;
	switch (Operation_Type)
	{
		case 1:  //�������̵����ϱ�������5��
			  	 RED_A = 0; YELLOW_A = 0; GREEN_A =1;
				 RED_B = 1; YELLOW_B = 0; GREEN_B =0;
				 //5s���л�������50ms * 100 = 5s��
				 if (++Time_Count != 100)
				 	return;
				 Time_Count = 0;
				 Operation_Type	= 2;	//��һ��������
				 break;
		case 2:  //������Ƶƿ�ʼ��˸,�̵ƹر�
				 if (++Time_Count != 8)
				 	return;
				 Time_Count = 0;
				 YELLOW_A = !YELLOW_A; GREEN_A = 0;
				 //��˸5��
				 if (++Flash_Count != 10)
				 	return;
				 Flash_Count = 0;
				 Operation_Type	= 3;	//��һ��������
				 break;
		case 3:  //�����������ϱ����̵���5��
				 RED_A = 1; YELLOW_A = 0; GREEN_A =0;
				 RED_B = 0; YELLOW_B = 0; GREEN_B =1;
				 //5s���л�������50ms * 100 = 5s��
				 if (++Time_Count != 100)
				 	return;
				 Time_Count = 0;
				 Operation_Type	= 4;	//��һ��������
				 break;
		case 4:  //�ϱ���Ƶƿ�ʼ��˸
				 if (++Time_Count != 8)
				 	return;
				 Time_Count = 0;
				 YELLOW_B = !YELLOW_B; GREEN_B = 0;
				 //��˸5��
				 if (++Flash_Count != 10)
				 	return;
				 Flash_Count = 0;
				 Operation_Type	= 1;	//��һ��������
	}
}

//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main()
{
	TMOD = 0x01;	//��ʱ��0�����ڷ�ʽ1
	IE = 0x82;		//����ʱ��0�ж�
	TR0 = 1;		//������ʱ��0
	while(1);		//�ȴ��ж�
}
