//-----------------------------------------------------------------
// 名称: DS12887日历时钟芯片驱动程序
//-----------------------------------------------------------------
#define INT8U  unsigned char
#define INT16U unsigned int
#include <reg51.h>
#include <intrins.h>
#include <absacc.h>
//-----------------------------------------------------------------
//DS12887寄存器地址定义
#define DS_SECOND			XBYTE[0xFE00]	//秒
#define DS_SECOND_ALARM		XBYTE[0xFE01]	//秒报警
#define DS_MINUTE			XBYTE[0xFE02]	//分
#define DS_MINUTE_ALARM		XBYTE[0xFE03]	//分报警
#define DS_HOUR				XBYTE[0xFE04]	//时
#define DS_HOUR_ALARM		XBYTE[0xFE05]	//时报警
#define DS_WEEK				XBYTE[0xFE06]	//星期
#define DS_DAY				XBYTE[0xFE07]	//日
#define DS_MONTH			XBYTE[0xFE08]	//月
#define DS_YEAR				XBYTE[0xFE09]	//年(年低2位)
#define DS_CENTURY			XBYTE[0xFE32]	//世纪(年高2位)
#define CTRL_REGA			XBYTE[0xFE0A]	//控制寄存器A
#define CTRL_REGB			XBYTE[0xFE0B]	//控制寄存器B
#define CTRL_REGC			XBYTE[0xFE0C]	//控制寄存器C
#define CTRL_REGD			XBYTE[0xFE0D]	//控制寄存器D
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
//保存:秒(0),分(1),时(2),日(3),月(4),年2位(5),低高2位(6),星期(7)
INT8U DateTime[8];
//0,1,2,3,4,5,6分别对应周日,周一至六
code char WEEK[][4] = {"SUN","MON","TUS","WEN","THU","FRI","SAT"};
//一年中每个月的天数,2月的天数由年份决定是否加1
//code INT8U MonthsDays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
extern void delay_ms(INT16U);
#define BCD_TO_DEC(x) (x >> 4) * 10 + (x & 0x0F) //BCD码转换为十进制数
//-----------------------------------------------------------------
// 判断是否为闰年
//-----------------------------------------------------------------
INT8U isLeapYear(INT16U y)
{ 
	return (y % 4 == 0 && y % 100 != 0 ) || (y % 400 == 0) ;
}

//-----------------------------------------------------------------
// 求自2000.1.1开始的任何一天是星期几(已知1999.12.31是周五: w = 5)
// 函数没有通过求出总天数后再求星期几,
// 因为求总天数可能会超出INT16U的范围
// 此函数仅在调整日期时,根据日期计算星期并写入时使用.
//-----------------------------------------------------------------
//INT8U GetWeek()
//{ 
//	INT16U i,Y = 2000 + BCD_TO_DEC(DateTime[5]), d = 0, w = 5; 
//	//从2000.1.1开始推算出当前年-1年.12.31是星期几(w)
//	for (i = 2000; i < Y; i++)
//	{	d = isLeapYear(i) ? 366 : 365; w = (w + d) % 7 ;
//	}	
//	//计算出当前所设置的年月日是该年的第几天(d).
//	for (d = 0, i = 1; i < BCD_TO_DEC(DateTime[4]); i++) 
//	{	d += MonthsDays[i]; if (i == 2 && isLeapYear(Y)) d += 1;
//	}
//	d += BCD_TO_DEC(DateTime[3]);	//加上当日
//	//根据w与d计算出当前年/月/日是星期几,0~6表示星期日,星期一,二,...,六
//	return (w + d) % 7; 
//}

//-----------------------------------------------------------------
// 读取实时时钟
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
// 写实时时钟
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
// 读DS12887数据
//-----------------------------------------------------------------
void Get_DateTime()
{







}

//-----------------------------------------------------------------
// DS12887初始化
//-----------------------------------------------------------------
void DS12887_Init() 
{ 
	CTRL_REGA = 0x20;				//DV2.1.0(开振荡器),32.768k
	CTRL_REGB = 0x00;				//PIE-AIE-UIE=000,DM-24/12=00
	CTRL_REGC = 0x00;				//IRQF-PF-AF-UF = 0000
	Write_DS(CENTURY,0x20);			//默认将年的高2位设为20
}