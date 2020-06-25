//-----------------------------------------------------------------
//  名称: SHT75x温/湿度传感器应用测试程序
//-----------------------------------------------------------------
//  说明:本例演示了SHT75x温/湿度传感器的程序设计方法,包括:
//       器件连接复位,湿度检测(12bit),温度检测(14bit),温湿度计算,
//       露点计算及显示等.
//
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#include <math.h>
#include <stdio.h>
#define INT8U   unsigned char
#define INT16U  unsigned int
//为便于数据分解而定义的联合体类型value
typedef union { INT16U i;  float f;} value;
//外部定义的液晶函数声明
extern void Initialize_LCD();
extern void LCD_Show_String(INT8U,INT8U,INT8U *);
//枚举类型常量(温度,湿度)
enum { TEMP,HUMI };
//温湿度传感器引脚定义
sbit SCK = P2^6;
sbit SDA = P2^7;
//是否应答
#define NACK	0
#define ACK		1
//SHT75传感器命令集		地址		命令	读/写
#define MEASURE_TEMP	0x03	//000 0001  1
#define MEASURE_HUMI	0x05	//000 0010  1
#define STATUS_REG_W	0x06	//000 0011  0
#define STATUS_REG_R	0x07	//000 0011  1
#define RESET			0x1E	//000 1111  0
//-----------------------------------------------------------------
// 写一节到SHT75并检查应答
//-----------------------------------------------------------------
INT8U s_Write_Byte(INT8U dat)
{ 



}

//-----------------------------------------------------------------
// 从传感器读一字节(参数ack为1时发送应答)
//-----------------------------------------------------------------
INT8U s_Read_Byte(INT8U ack)
{ 



}

//-----------------------------------------------------------------
// 传输开始
//-----------------------------------------------------------------
void s_TransStart()
{  
	SDA = 1;							//初始状态
	SCK = 0; _nop_(); SCK = 1; _nop_(); SDA = 0; _nop_(); 
	SCK = 0; _nop_(); _nop_(); _nop_();
	SCK = 1; _nop_(); SDA = 1; _nop_(); SCK = 0;
}

//-----------------------------------------------------------------
// 传感器连接复位
//-----------------------------------------------------------------
void s_ConnectionReset()
{  
	INT8U i; 
	SDA = 1; SCK = 0;							//初始状态
	for(i = 0;i < 9; i++) { SCK = 1; SCK = 0; }	//9个时钟周期
	s_TransStart();								//传输开始
}

//-----------------------------------------------------------------
// 传感器软复位
//-----------------------------------------------------------------
INT8U s_SoftReset()
{ 
	INT8U error = 0;
	s_ConnectionReset();				//传感器连接复位
	error += s_Write_Byte(RESET);		//向传感器发送复位命令
	return error;						//无响应时返回1
}

//-----------------------------------------------------------------
// 写状态寄存器
//-----------------------------------------------------------------
INT8U s_Write_StatusReg(INT8U *p_value)
{ 
	INT8U error = 0;
	s_TransStart();						//传输开始
	error += s_Write_Byte(STATUS_REG_W);//向传感器发送命令STATUS_REG_W
	error += s_Write_Byte(*p_value);	//发送状态寄存器的值
	return error;						//无响应时返回1
}

//-----------------------------------------------------------------
// 读状态寄存器
//-----------------------------------------------------------------
INT8U s_Read_StatusReg(INT8U *p_value, INT8U *p_checksum)
{ 
	INT8U error = 0;
	s_TransStart();							//传输开始
	error		= s_Write_Byte(STATUS_REG_R);//向传感器发送读状态命令
	*p_value	= s_Read_Byte(ACK);			//读状态寄存器(8位)
	*p_checksum = s_Read_Byte(NACK);		//读取校验和(8位)
	return error;							//无响应时返回1
}

//-----------------------------------------------------------------
// 根据操作模式mode分别进行温度与湿度测量,并读取校验码
//-----------------------------------------------------------------
INT8U s_Measure(INT8U *p_value, INT8U *p_checksum, INT8U mode)
{ 
	INT16U i = 0, error = 0;
	s_TransStart();							//传输开始
	switch(mode)							//向传感器发送命令
	{	case TEMP : error += s_Write_Byte(MEASURE_TEMP); break;
		case HUMI : error += s_Write_Byte(MEASURE_HUMI); break;
		default   : break;	
	}
	//等待传感器完成温湿度数据检测
	for (i = 0;i < 65535; i++) if(SDA == 0) break;
	if(SDA) error += 1;						//2s后SDA为1则记为超时
	*(p_value)		= s_Read_Byte(ACK);		//读第一字节(应答)
	*(p_value + 1)	= s_Read_Byte(ACK);		//读第二字节(应答)
	*p_checksum		= s_Read_Byte(NACK);	//读校验码(不应答)
	return error;
}

//-----------------------------------------------------------------
// 计算温湿度
//-----------------------------------------------------------------
void Calc_STH75(float *p_humidity ,float *p_temperature)
{
	const float C1 = -4.0;				//12位,系数C1
	const float C2 = +0.0405;			//12位,系数C2
	const float C3 = -0.0000028;		//12位,系数C3
	const float T1 = +0.01;				//14位 @ 5V ,系数T1
	const float T2 = +0.00008;			//14位 @ 5V ,系数T2
	float rh = *p_humidity;				// rh:	  湿度 12 Bit 
	float t  = *p_temperature;			// t:	   温度 14 Bit
	float rh_lin;						// rh_lin:  线性湿度
	float rh_true;						// rh_true: 温度补偿湿度
	float t_C;							// t_C   :  温度(℃)
	t_C = t * 0.01 - 40;				//计算温度
	rh_lin = C3 * rh * rh + C2 * rh + C1;//计算湿度
	rh_true=(t_C - 25) * (T1 + T2 * rh) + rh_lin;//计算:温度补偿湿度
	if(rh_true > 100) rh_true = 100;	//将湿度数据限制在正常范围之内
	if(rh_true < 0.1) rh_true = 0.1;	//即0.1% ~ 100%
	*p_temperature = t_C;				//返回温度[℃]
	*p_humidity = rh_true;				//返回湿度[%RH]
}

//--------------------------------------------------------------------
// 根据输入的湿度与温度计算露点
//--------------------------------------------------------------------
float Calc_Dew_Point(float h, float t)
{ 
	float logEx,dew_point;
	logEx = 0.66077 + 7.5 * t / (237.3 + t) + (log10(h) - 2);
	dew_point = (logEx - 0.66077) * 237.3 / (0.66077 + 7.5 - logEx);
	return dew_point;
}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{








}