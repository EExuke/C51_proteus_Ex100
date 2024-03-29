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
//LCD显示缓冲(注意串长均为16,两个字符串中DATE和TIME后各有一个空格
//字符串的最后面各有3个空格.
INT8U LCD_BUF_1[] = "DATE 00-00-00   ";
INT8U LCD_BUF_2[] = "TIME 00:00:00   ";
extern void GetDateTime() ;							//读取当前日期时间
extern void Initialize_LCD();						//LCD初始化
extern void LCD_ShowString(INT8U, INT8U,INT8U *);	//在LCD上显示字符串
extern INT8U DateTime[7];							//所读取的日期时间
//-----------------------------------------------------------------
// 日期与时间值转换为数字字符
// 输入的参数d为BCD码时，使用语句[1]、[2]之一
// 输入的参数d为10进制数时，使用语句[3]
// 建议DS1302.c内的函数GetDateTime直接返回BCD码,这样可节省一次转换.
// 如果在GetDateTime内转换为10进制数返回,本函数内再转换为字符,
// 这将影响运行速度.
//-----------------------------------------------------------------
void Format_DateTime(INT8U d, INT8U *a)
{ 
	//如果GetDateTime函数直接返回BCD码返回则使用下面的语句
	*a = (d >> 4) + '0'; *(a+1) = (d & 0x0F) + '0';	//[1]
	//或者使用下面的语句,更优的写法显然是上面含有位运算符(>>,&)的语句
	//*a = d / 16 + '0';  *(a+1) = d % 16 + '0';	//[2]
	//--------------------------------------------------
	//如果GetDateTime函数将BCD码转换为10进制数以后再返回
	//则应使用下面的语句
	//*a = d / 10 + '0'; *(a+1) = d % 10 + '0';		//[3]
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	Initialize_LCD();		//液晶初始化
	while(1)
	{
		GetDateTime();
		//year,month,day
		Format_DateTime(DateTime[6], LCD_BUF_1 + 5);
		Format_DateTime(DateTime[4], LCD_BUF_1 + 8);
		Format_DateTime(DateTime[3], LCD_BUF_1 + 11);
		//week
		strcpy(LCD_BUF_1 + 13, WEEK[DateTime[5] -1]);
		//hour,min,sec
		Format_DateTime(DateTime[2], LCD_BUF_1 + 5);
		Format_DateTime(DateTime[1], LCD_BUF_1 + 8);
		Format_DateTime(DateTime[0], LCD_BUF_1 + 11);
		//show time
		LCD_ShowString(0, 0, LCD_BUF_1);
		LCD_ShowString(1, 0, LCD_BUF_2);
	}
}
