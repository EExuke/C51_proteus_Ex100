//-----------------------------------------------------------------
//  名称: DS1302 实时时钟显示程序
//-----------------------------------------------------------------
//  说明: 从DS1302中读取时钟数据,在LCD上显示日期和时间.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <string.h>
#define INT8U  unsigned char
#define INT16U unsigned int
//0~6分别对应周日,周一至周六
INT8U *WEEK[] = {"SUN","MON","TUS","WEN","THU","FRI","SAT"};
//LCD显示缓冲
INT8U LCD_DSY_BUFFER1[] = {"DATE 00-00-00   "};
INT8U LCD_DSY_BUFFER2[] = {"TIME 00:00:00   "};
extern void GetTime() ;							//读取当前日期时间
extern void Initialize_LCD();					//LCD初始化
extern void LCD_ShowString(INT8U ,INT8U,char*);	//在LCD上显示字符串
extern INT8U DateTime[7];	 					//所读取的日期时间
//-----------------------------------------------------------------
// 日期与时间值转换为数字字符 
//-----------------------------------------------------------------
void Format_DateTime(INT8U d, INT8U *a)
{
	a[0] = d / 10 + '0';
	a[1] = d % 10 + '0';
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	Initialize_LCD();
	while (1)
	{
		GetTime();
		//year-month-day
		Format_DateTime(DateTime[6], LCD_DSY_BUFFER1 + 5);
		Format_DateTime(DateTime[5], LCD_DSY_BUFFER1 + 8);
		Format_DateTime(DateTime[4], LCD_DSY_BUFFER1 + 11);
		//week
		strcpy(LCD_DSY_BUFFER1 + 13, WEEK[DateTime[5] - 1]);
		//hour-min-sec
		Format_DateTime(DateTime[2], LCD_DSY_BUFFER2 + 5);
		Format_DateTime(DateTime[1], LCD_DSY_BUFFER2 + 8);
		Format_DateTime(DateTime[0], LCD_DSY_BUFFER2 + 11);
		//show date time
		LCD_ShowString(0, 0, LCD_DSY_BUFFER1);
		LCD_ShowString(0, 0, LCD_DSY_BUFFER2);
	}
}





