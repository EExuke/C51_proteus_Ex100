//-----------------------------------------------------------------
//	名称: 高度仿真的可调式数码管电子钟
//-----------------------------------------------------------------
//	说明: 本例在Proteus中选用了高度仿真的电子钟元器件,并添加了
//		时分调整功能,闪烁显示,AM/PM切换,12/24小时制选择等.
//				
//-----------------------------------------------------------------
#include <reg51.h> 
#include <intrins.h>
#define INT8U unsigned char
#define INT16U	unsigned int
//时钟设置开关及按键
sbit K1 = P0^0;		//12/24小时
sbit K2 = P0^1;		//设置
sbit K3 = P0^2;		//小时加
sbit K4 = P0^3;		//分钟加
//当前时间:时分秒
INT8U current_Time[] = {12,59,40};
//时分秒显示缓冲(各占两位),最后的0x00控制AM,PM及发光管闪烁等.
INT8U disp_Buffer[] = {0,0,0,0,0,0,0x00};
//12,24小时,AM,PM 及SET 控制标志
INT8U f_24 = 0, f_AM = 0, f_set = 0;
//-----------------------------------------------------------------
// 延时
//-----------------------------------------------------------------
void delay_ms(INT16U x){ INT8U i; while (--x) for (i = 0; i<120 ; i++);}
//-----------------------------------------------------------------
// 小时数累加处理
//-----------------------------------------------------------------
void Add_Hour()
{

	
}

//-----------------------------------------------------------------
// 分钟数累加处理
//-----------------------------------------------------------------
void Add_Miniute()
{


}

//-----------------------------------------------------------------
// 根据当前时间刷新时分秒显示缓冲
//-----------------------------------------------------------------
void Refresh_Disp_Buffer()
{


}

//-----------------------------------------------------------------
// 外部中断0,中断源为50Hz时基,由P3.2(INT0)引入,每0.02s生产一个下降沿
//-----------------------------------------------------------------
void EX0_INT() interrupt 0
{


}

//-----------------------------------------------------------------
// 显示时间(共输出7字节,前6字节为时/分/秒的BCD码(各占2字节)
// 第7字节为指示屏及"："号的控制码)
//-----------------------------------------------------------------
void Display_Time()
{


}

//-----------------------------------------------------------------
// 时钟调整与设置
//-----------------------------------------------------------------
void Adjust_and_Set_Clock()
{


}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main( )
{


}