//-----------------------------------------------------------------
//  名称: LCD1602液晶驱动程序头文件
//-----------------------------------------------------------------
//LCD引脚定义
sbit RS = P2^0;			//LCD寄存器选择
sbit RW = P2^1;			//LCD读写控制
sbit EN = P2^2;			//LCD使能控制
//液晶端口定义
#define LCD_PORT P2		//液晶端口(P2高4位)
//LCD相关函数
void LCD_Busy_Wait();					//忙等待
void Write_LCD_Data(INT8U dat);			//向LCD写数据
void Write_LCD_Command(INT8U cmd);		//写LCD指令
void Initialize_LCD();					//LCD初始化
void LCD_ShowString(INT8U r, INT8U c,char *str);//在LCD上显示字符串