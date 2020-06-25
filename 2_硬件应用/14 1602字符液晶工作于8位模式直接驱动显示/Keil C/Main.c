//-----------------------------------------------------------------
//  名称: 1602字符液晶工作于8位模式直接驱动显示
//-----------------------------------------------------------------
//  说明: 本例液晶实现了四项演示功能,分别为水平滚动,带光标显示随机
//        算术式,全码表字符显示,CGRAM自定义字符显示.
//	  
//-----------------------------------------------------------------
#include <reg51.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define INT8U  unsigned char
#define INT16U unsigned int
sbit SW1 = P3^0;		//水平水平滚动显示
sbit SW2 = P3^1;		//带光标显示随机算术式
sbit SW3 = P3^2;		//全码表字符显示
sbit SW4 = P3^3;		//CGRAM自定义字符显示
INT8U code msg[] =		//待滚动显示的字符串(字符串最前面加了16个空格)
"                you are going to spend even more time working on the schematic ?";
//-----------------------------------------------------------------
extern delay_ms(INT16U x);
extern void Initialize_LCD();
extern void Write_LCD_Data(INT8U dat);
extern void Write_LCD_Command(INT8U cmd);
extern void Busy_Wait();
extern void LCD_ShowString(INT8U,INT8U,INT8U *);
//-----------------------------------------------------------------
//自定义CGRAM字符及图标点阵数据(共两组,每组字符不超过8个)
INT8U code CGRAM_Dat1[][8] = //7个图标符号（高度由1~7横递增的矩形）
{	{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00},	//1横
	{0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x00},	//2横
	{0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,0x00},	//3横
	{0x00,0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x00},	//4横
	{0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x00},	//5横
	{0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00},	//6横
	{0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00} 	//7横
};
INT8U code CGRAM_Dat2[][8] = //5个汉字字符
{	{0x08,0x0F,0x12,0x0F,0x0A,0x1F,0x02,0x00},	//年
	{0x0F,0x09,0x0F,0x09,0x0F,0x09,0x13,0x00},	//月
	{0x0F,0x09,0x09,0x0F,0x09,0x09,0x0F,0x00},	//日
	{0x1F,0x0A,0x1F,0x0A,0x0A,0x0A,0x12,0x00},	//开
	{0x0A,0x1F,0x04,0x1F,0x04,0x0A,0x11,0x00} 	//关
};
//-----------------------------------------------------------------
// 将自定义字符点阵写入CGRAM
//-----------------------------------------------------------------
void Write_CGRAM(INT8U g[][8], INT8U n)
{
	INT8U i, j;
	Write_LCD_Command(0x04);			//设置CGRAM地址为0x40
	for (i = 0; i < n; i++)				//n个自定义字符
		for(j = 0; j < 8; j++)			//每个字符8字节点阵数据
			Write_LCD_Data(g[i][j]);	//写入CGRAM
}

//-----------------------------------------------------------------
// SW1: 水平滚动显示字符串
//-----------------------------------------------------------------
void H_Scroll_Display()
{
	INT16U i;
	Write_LCD_Command(0x0C);					//开显示，关光标
	LCD_ShowString(0, 0, "LCD1602 DEMO - 1");	//第0行显示标题
	LOOP1:
	for (i = 0; i < strlen(msg); i++)			//滚动输出所有字符
	{	
		LCD_ShowString(1, 0, msg + i);			//msg+1实现取字符指针递增
		delay_ms(50);
		if (SW1)
			return;								//未置于SW1位置时立即返回
	}
	delay_ms(1000);								//显示完所有字符后暂停1秒，然后继续
	goto LOOP1;
}

//-----------------------------------------------------------------
// SW2: 带光标显示随机算术式
//-----------------------------------------------------------------
void Cursor_Display()
{
	INT8U i;
	int a, b,;
	char disp_buff[17];
	
	Write_LCD_Command(0x0C);								//开显示，关光标
	LCD_ShowString(0, 0, "LCD1602 DEMO - 2");				//第0行显示标题
	LCD_ShowString(1, 0, "               ");				//清空第1行，输出16个空格
	Write_LCD_Command(0x0F);								//开显示，开光标，光标闪烁
	srand(TH0);												//用TH0作为随机种子
	while(1)
	{
		if (SW2)			//未置于SW2位置时立即返回
			return;
		a = rand() % 100;	//产生不超过100的随机数a, b
		b = rand() % 100;
		sprintf(disp_buff, "%2d + %2d = %2d", a, b, a+b);	//生成算术式及运算结果字符串
		Write_LCD_Command(0xC0);							//显示位置定位于第1行开始位置
		for (i = 0; i < 16; i++)							//循环逐个输出算术式字符
		{
			if (disp_buff[i])
				Write_LCD_Data(disp_buff[i]);
			else
				Write_LCD_Data(' ');
			delay_ms(100);
		}
		delay_ms(200);										//显示完一个算术式后暂停200ms
		LCD_ShowString(1, 0, "                ");			//清空该行，输出16个空格
	}
}

//-----------------------------------------------------------------
// SW3: 全码表字符显示
//-----------------------------------------------------------------
void Show_All_Inter_Chars()
{
	INT8U i, j = 0;
	
	Write_LCD_Command(0x0C);					//开显示，关光标
	LCD_ShowString(0, 0, LCD1602 DEMO - 3");	//第0行显示标题
	LCD_ShowString(1, 0, "                ");	//第一行清空
	LOOP3:
	Write_LCD_Command(0xC0);					//显示位置定位于第1行开始位置
	/* 从全码表显示，范围为0x20~0xFF，超过0xFF后溢出为0x00，循环结束 */
	for (i = 0x20; i != 0x00; i++)
	{
		if (i >= 0x80 && i <= 0x9F)
			continue;					//跳过空白区字符
		if ((++j) % 16 == 0)			//判断是否显示满一行
		{
			delay_ms(500);
			LCD_ShowString(1, 0, "                ");
			Write_LCD_Command(0xC0);			//显示位置定位于第1行开始位置
			j = 0;								//显示字符计数变量清零
		}
		Write_LCD_Data(i);				//在当前位置显示编码为i的字符
		delay_ms(500);			
		if (SW3)
			return;
	}
	delay_ms(500);
	goto LOOP3;
}

//-----------------------------------------------------------------
// SW4: CGRAM自定义字符显示
//-----------------------------------------------------------------
void Display_CGRAM_Chars()
{
	INT8U i, j = 0;
	
	Write_LCD_Command(0x0C);					//开显示，关光标
	LCD_ShowString(0, 0, "LCD1602 DEMO - 4");	//第0行显示标题
	LOOP4:
	/* 第1组自定义CGRAM字符演示 */
	LCD_ShowString(1, 0, "                ");	//第1行清空
	Write_CGRAM(CGRAM_Dat1, 7);					//第1组自定义字符点阵写入CGRAM
	Write_LCD_Command(0xC0 | 1);				//显示位置定位于第1行开始位置
	for (i = 6; i != 0xFF; i--)					//7线~1线式方块逐个显示
	{
		Write_LCD_Data(i);					//在当前位置显示编码为i的字符
		delay_ms(50);
		if (SW4)
			return;
	}
	for (i = 0; i < 6; i++)						//1线~7线式方块逐个显示
	{
		Write_LCD_Data(i);					//在当前位置显示编码为i的字符
		delay_ms(50);
		if (SW4)
			return;
	}	
	delay_ms(500);
	/* 第2组自定义CGRAM字符演示 */
	LCD_ShowString(1, 0, "                ");
	Write_CGRAM(CGRAM_Dat2, 5);					//第2组自定义字符点阵写入CGRAM
	Write_LCD_Command(0xC0 | 4);				//显示位置定位于第1行4列
	for (i = 0; i <= 4; i++)					//5个自定义汉字字符显示
	{
		Write_LCD_Data(i);					//在当前位置显示编码为i的字符
		Write_LCD_Data(' ');
		delay_ms(100);
		if (SW4)
			return;
	}
	delay_ms(1000);
	goto LOOP4;				//继续
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	P3 = 0xFF;						//P3端口置为0xFF
	Initialize_LCD();				//初始化LCD
	TR0  = 1;						//启动定时器,提供随机种子
	while(1)						//主循环控制实现各类演示
	{	if (SW1 == 0) H_Scroll_Display();
		if (SW2 == 0) Cursor_Display();
		if (SW3 == 0) Show_All_Inter_Chars();
		if (SW4 == 0) Display_CGRAM_Chars();
	}
}