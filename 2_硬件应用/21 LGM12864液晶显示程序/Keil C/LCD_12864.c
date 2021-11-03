//-----------------------------------------------------------------
//  名称:12864LCD(KS0108)显示驱动程序 (不带字库)
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U	unsigned char
#define INT16U	unsigned int
#define	LCD_DB_PORT		P1			//液晶DB0-DB7
#define LCD_START_ROW	0xC0		//起始行
#define LCD_PAGE		0xB8		//页指令
#define LCD_COL			0x40		//列指令

//液晶引脚定义
sbit	DI  = P3^0 ;				//数据/命令选择线
sbit	RW  = P3^1 ;				//读/写控制线
sbit	E   = P3^2 ;				//使能控制线
sbit	CS1 = P3^3 ;				//片选1
sbit	CS2	= P3^4 ;				//片选2
sbit	RST = P3^5 ;				//复位
//-----------------------------------------------------------------
// LCD忙等待
//-----------------------------------------------------------------
void LCD_Busy_Wait()
{
	do {
		LCD_DB_PORT = 0xff;
		RW = 1; _nop_(); DI = 0; //设置为读，选择状态寄存器
		E = 1; _nop_op_(); E = 0; //E置高电平读取，随后置为低电平
	} while (P0 & 0x80);
}

//-----------------------------------------------------------------
// 向LCD发送命令
//-----------------------------------------------------------------
void LCD_Write_Command( INT8U c)
{
	LCD_Busy_Wait();
	LCD_DB_PORT = 0xff;
	RW = 0; _nop_(); DI = 0;
	LCD_DB_PORT = c;
	E = 1; _nop_(); E = 0;
}

//-----------------------------------------------------------------
// 向LCD发送数据
//-----------------------------------------------------------------
void LCD_Write_Data(INT8U d )
{
	LCD_Busy_Wait();
	LCD_DB_PORT = 0xff;
	RW = 0; _nop_(); DI = 1; //设置为写， 选择数据寄存器
	LCD_DB_PORT = d;
	E = 1; _nop_(); E = 0;
}

//-----------------------------------------------------------------
// 初始化LCD
//-----------------------------------------------------------------
void LCD_Initialize()
{
	CS1 = 1; CS2 = 1;                 //左半屏片选
	LCD_Write_Command(0x3f);          //显示开
	LCD_Write_Command(LCD_START_ROW); //设置起始行
}

//-----------------------------------------------------------------
//
// 通用显示函数
// 
// 从第P页第L列开始显示W个字节数据,数据在r所指向的缓冲
// 每字节8位是垂直显示的,高位在下,低位在上
// 每个8*128的矩形区域为一页
// 整个LCD又由64x64的左半屏和64x64的右半屏构成
//-----------------------------------------------------------------
void Common_Show(INT8U P,INT8U L,INT8U W,INT8U *r)
{
	INT8U i;
	if (L < 64) {
		CS1 = 1; CS2 = 0;       //左半屏
		LCD_Write_Command(LCD_PAGE + P);
		LCD_Write_Command(LCD_COL + L);
		if (L + W < 64) {
			for (i=0; i<W; i++) {
				LCD_Write_Data(r[i]);
			}
		} else {
			for (i=0; i<64-L; i++) {
				LCD_Write_Data(r[i]);
			}
			CS1 = 0; CS2 = 1;    //右半屏
			LCD_Write_Command(LCD_PAGE + P);
			LCD_Write_Command(LCD_COL);
			for (i=64-L; i<W; i++) {
				LCD_Write_Data(r[i]);
			}
		}
	} else {
		CS1 = 0; CS2 = 1;    //右半屏
		LCD_Write_Command(LCD_PAGE + P);
		LCD_Write_Command(LCD_COL + L - 64);
		for (i=64-L; i<W; i++) {
			LCD_Write_Data(r[i]);
		}
	}
}

//-----------------------------------------------------------------
// 显示一个8×8点阵字符
//-----------------------------------------------------------------
//void Display_A_Char(INT8U P,INT8U L,INT8U *M)
//{
//	Common_Show( P,    L, 8, M );
//}

//-----------------------------------------------------------------
// 显示一个16×16点阵汉字
//-----------------------------------------------------------------
void Display_A_WORD(INT8U P,INT8U L,INT8U *M)
{
	Common_Show( P, L, 16, M );    //汉字上半部分
	Common_Show( P+1, L, 16, M+16); //下半部分
}

//-----------------------------------------------------------------
// 显示一串16×16点阵汉字
//-----------------------------------------------------------------
void Display_A_WORD_String(INT8U P,INT8U L,INT8U C,INT8U *M)
{
	INT8U i;
	for (i=0; i<C; i++) {
		Display_A_WORD(P, L+i*16, M+i*32);
	}
}

//-----------------------------------------------------------------
// 显示图像
// 说明:这里W与图像宽度相同,但H不是图像高度,图像实际高度为H*8
//-----------------------------------------------------------------
void Display_Image(INT8U P,INT8U L,INT8U W,INT8U H,INT8U * G)
{
	INT8U i;
	for (i=0; i<H; i++) {
		Common_Show(P+i, L, W, G+i*W);
	}
}
