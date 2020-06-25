//-----------------------------------------------------------------
//  名称:DS1302时钟芯片驱动程序头文件
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit IO   = P1^0;						//DS1302数据线
sbit SCLK = P1^1;						//DS1302时钟线
sbit RST  = P1^2;						//DS1302复位线
//-----------------------------------------------------------------
// 相关函数声明
//-----------------------------------------------------------------
INT8U DateTime[7];	 					//所读取的日期时间
void Write_A_Byte_TO_DS1302(INT8U x);	//向DS1302写入一字节
INT8U Get_A_Byte_FROM_DS1302(); 		//从DS1302读取一字节
INT8U Read_Data(INT8U addr);			//从DS1302指定位置读数据
void GetDateTime() ;					//读取当前日期时间