//-----------------------------------------------------------------
// PG160128液晶驱动程序(T6963C)
//-----------------------------------------------------------------
#include <reg51.h>
#include <stdio.h>
#include <math.h>
#include <intrins.h>
#include <absacc.h>
#include <string.h>
#include "LCD_160128.h" 
//ASCII字模8*8
#define ASC_CHR_WIDTH    8
#define ASC_CHR_HEIGHT  12 
//汉字字模12*12
#define HZ_CHR_HEIGHT   12
#define HZ_CHR_WIDTH    12
//液晶宽度/高度定义
INT8U code LCD_WIDTH  = 20;   //宽160像素(160/8 = 20个字节)
INT8U code LCD_HEIGHT = 128;  //高128像素
//ASC字符点阵库
INT8U code ASC_MSK[96 * 12] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,// <0x20时
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// ' '
0x00,0x30,0x78,0x78,0x78,0x30,0x30,0x00,0x30,0x30,0x00,0x00,// '!'
0x00,0x66,0x66,0x66,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// '"'
0x00,0x6c,0x6c,0xfe,0x6c,0x6c,0x6c,0xfe,0x6c,0x6c,0x00,0x00,// '#'
0x30,0x30,0x7c,0xc0,0xc0,0x78,0x0c,0x0c,0xf8,0x30,0x30,0x00,// '$'
0x00,0x00,0x00,0xc4,0xcc,0x18,0x30,0x60,0xcc,0x8c,0x00,0x00,// '%'
0x00,0x70,0xd8,0xd8,0x70,0xfa,0xde,0xcc,0xdc,0x76,0x00,0x00,// '&'
0x00,0x30,0x30,0x30,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// '''
0x00,0x0c,0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x0c,0x00,0x00,// '('
0x00,0x60,0x30,0x18,0x0c,0x0c,0x0c,0x18,0x30,0x60,0x00,0x00,// ')'
0x00,0x00,0x00,0x66,0x3c,0xff,0x3c,0x66,0x00,0x00,0x00,0x00,// '*'
0x00,0x00,0x00,0x18,0x18,0x7e,0x18,0x18,0x00,0x00,0x00,0x00,// '+'
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38,0x60,0x00,// ','
0x00,0x00,0x00,0x00,0x00,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,// '-'
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38,0x00,0x00,// '.'
0x00,0x00,0x02,0x06,0x0c,0x18,0x30,0x60,0xc0,0x80,0x00,0x00,// '/'
0x00,0x7c,0xc6,0xce,0xde,0xd6,0xf6,0xe6,0xc6,0x7c,0x00,0x00,// '0'
0x00,0x10,0x30,0xf0,0x30,0x30,0x30,0x30,0x30,0xfc,0x00,0x00,// '1'
0x00,0x78,0xcc,0xcc,0x0c,0x18,0x30,0x60,0xcc,0xfc,0x00,0x00,// '2'
0x00,0x78,0xcc,0x0c,0x0c,0x38,0x0c,0x0c,0xcc,0x78,0x00,0x00,// '3'
0x00,0x0c,0x1c,0x3c,0x6c,0xcc,0xfe,0x0c,0x0c,0x1e,0x00,0x00,// '4'
0x00,0xfc,0xc0,0xc0,0xc0,0xf8,0x0c,0x0c,0xcc,0x78,0x00,0x00,// '5'
0x00,0x38,0x60,0xc0,0xc0,0xf8,0xcc,0xcc,0xcc,0x78,0x00,0x00,// '6'
0x00,0xfe,0xc6,0xc6,0x06,0x0c,0x18,0x30,0x30,0x30,0x00,0x00,// '7'
0x00,0x78,0xcc,0xcc,0xec,0x78,0xdc,0xcc,0xcc,0x78,0x00,0x00,// '8'
0x00,0x78,0xcc,0xcc,0xcc,0x7c,0x18,0x18,0x30,0x70,0x00,0x00,// '9'
0x00,0x00,0x00,0x38,0x38,0x00,0x00,0x38,0x38,0x00,0x00,0x00,// ':'
0x00,0x00,0x00,0x38,0x38,0x00,0x00,0x38,0x38,0x18,0x30,0x00,// ';'
0x00,0x0c,0x18,0x30,0x60,0xc0,0x60,0x30,0x18,0x0c,0x00,0x00,// '<'
0x00,0x00,0x00,0x00,0x7e,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,// '='
0x00,0x60,0x30,0x18,0x0c,0x06,0x0c,0x18,0x30,0x60,0x00,0x00,// '>'
0x00,0x78,0xcc,0x0c,0x18,0x30,0x30,0x00,0x30,0x30,0x00,0x00,// '?'
0x00,0x7c,0xc6,0xc6,0xde,0xde,0xde,0xc0,0xc0,0x7c,0x00,0x00,// '@'
0x00,0x30,0x78,0xcc,0xcc,0xcc,0xfc,0xcc,0xcc,0xcc,0x00,0x00,// 'A'
0x00,0xfc,0x66,0x66,0x66,0x7c,0x66,0x66,0x66,0xfc,0x00,0x00,// 'B'
0x00,0x3c,0x66,0xc6,0xc0,0xc0,0xc0,0xc6,0x66,0x3c,0x00,0x00,// 'C'
0x00,0xf8,0x6c,0x66,0x66,0x66,0x66,0x66,0x6c,0xf8,0x00,0x00,// 'D'
0x00,0xfe,0x62,0x60,0x64,0x7c,0x64,0x60,0x62,0xfe,0x00,0x00,// 'E'
0x00,0xfe,0x66,0x62,0x64,0x7c,0x64,0x60,0x60,0xf0,0x00,0x00,// 'F'
0x00,0x3c,0x66,0xc6,0xc0,0xc0,0xce,0xc6,0x66,0x3e,0x00,0x00,// 'G'
0x00,0xcc,0xcc,0xcc,0xcc,0xfc,0xcc,0xcc,0xcc,0xcc,0x00,0x00,// 'H'
0x00,0x78,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x78,0x00,0x00,// 'I'
0x00,0x1e,0x0c,0x0c,0x0c,0x0c,0xcc,0xcc,0xcc,0x78,0x00,0x00,// 'J'
0x00,0xe6,0x66,0x6c,0x6c,0x78,0x6c,0x6c,0x66,0xe6,0x00,0x00,// 'K'
0x00,0xf0,0x60,0x60,0x60,0x60,0x62,0x66,0x66,0xfe,0x00,0x00,// 'L'
0x00,0xc6,0xee,0xfe,0xfe,0xd6,0xc6,0xc6,0xc6,0xc6,0x00,0x00,// 'M'
0x00,0xc6,0xc6,0xe6,0xf6,0xfe,0xde,0xce,0xc6,0xc6,0x00,0x00,// 'N'
0x00,0x38,0x6c,0xc6,0xc6,0xc6,0xc6,0xc6,0x6c,0x38,0x00,0x00,// 'O'
0x00,0xfc,0x66,0x66,0x66,0x7c,0x60,0x60,0x60,0xf0,0x00,0x00,// 'P'
0x00,0x38,0x6c,0xc6,0xc6,0xc6,0xce,0xde,0x7c,0x0c,0x1e,0x00,// 'Q'
0x00,0xfc,0x66,0x66,0x66,0x7c,0x6c,0x66,0x66,0xe6,0x00,0x00,// 'R'
0x00,0x78,0xcc,0xcc,0xc0,0x70,0x18,0xcc,0xcc,0x78,0x00,0x00,// 'S'
0x00,0xfc,0xb4,0x30,0x30,0x30,0x30,0x30,0x30,0x78,0x00,0x00,// 'T'
0x00,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0x78,0x00,0x00,// 'U'
0x00,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0x78,0x30,0x00,0x00,// 'V'
0x00,0xc6,0xc6,0xc6,0xc6,0xd6,0xd6,0x6c,0x6c,0x6c,0x00,0x00,// 'W'
0x00,0xcc,0xcc,0xcc,0x78,0x30,0x78,0xcc,0xcc,0xcc,0x00,0x00,// 'X'
0x00,0xcc,0xcc,0xcc,0xcc,0x78,0x30,0x30,0x30,0x78,0x00,0x00,// 'Y'
0x00,0xfe,0xce,0x98,0x18,0x30,0x60,0x62,0xc6,0xfe,0x00,0x00,// 'Z'
0x00,0x3c,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x3c,0x00,0x00,// '['
0x00,0x00,0x80,0xc0,0x60,0x30,0x18,0x0c,0x06,0x02,0x00,0x00,// '\'
0x00,0x3c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x3c,0x00,0x00,// ']'
0x10,0x38,0x6c,0xc6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// '^'
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,// '_'
0x30,0x30,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// '`'
0x00,0x00,0x00,0x00,0x78,0x0c,0x7c,0xcc,0xcc,0x76,0x00,0x00,// 'a'
0x00,0xe0,0x60,0x60,0x7c,0x66,0x66,0x66,0x66,0xdc,0x00,0x00,// 'b'
0x00,0x00,0x00,0x00,0x78,0xcc,0xc0,0xc0,0xcc,0x78,0x00,0x00,// 'c'
0x00,0x1c,0x0c,0x0c,0x7c,0xcc,0xcc,0xcc,0xcc,0x76,0x00,0x00,// 'd'
0x00,0x00,0x00,0x00,0x78,0xcc,0xfc,0xc0,0xcc,0x78,0x00,0x00,// 'e'
0x00,0x38,0x6c,0x60,0x60,0xf8,0x60,0x60,0x60,0xf0,0x00,0x00,// 'f'
0x00,0x00,0x00,0x00,0x76,0xcc,0xcc,0xcc,0x7c,0x0c,0xcc,0x78,// 'g'
0x00,0xe0,0x60,0x60,0x6c,0x76,0x66,0x66,0x66,0xe6,0x00,0x00,// 'h'
0x00,0x18,0x18,0x00,0x78,0x18,0x18,0x18,0x18,0x7e,0x00,0x00,// 'i'
0x00,0x0c,0x0c,0x00,0x3c,0x0c,0x0c,0x0c,0x0c,0xcc,0xcc,0x78,// 'j'
0x00,0xe0,0x60,0x60,0x66,0x6c,0x78,0x6c,0x66,0xe6,0x00,0x00,// 'k'
0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7e,0x00,0x00,// 'l'
0x00,0x00,0x00,0x00,0xfc,0xd6,0xd6,0xd6,0xd6,0xc6,0x00,0x00,// 'm'
0x00,0x00,0x00,0x00,0xf8,0xcc,0xcc,0xcc,0xcc,0xcc,0x00,0x00,// 'n'
0x00,0x00,0x00,0x00,0x78,0xcc,0xcc,0xcc,0xcc,0x78,0x00,0x00,// 'o'
0x00,0x00,0x00,0x00,0xdc,0x66,0x66,0x66,0x66,0x7c,0x60,0xf0,// 'p'
0x00,0x00,0x00,0x00,0x76,0xcc,0xcc,0xcc,0xcc,0x7c,0x0c,0x1e,// 'q'
0x00,0x00,0x00,0x00,0xec,0x6e,0x76,0x60,0x60,0xf0,0x00,0x00,// 'r'
0x00,0x00,0x00,0x00,0x78,0xcc,0x60,0x18,0xcc,0x78,0x00,0x00,// 's'
0x00,0x00,0x20,0x60,0xfc,0x60,0x60,0x60,0x6c,0x38,0x00,0x00,// 't'
0x00,0x00,0x00,0x00,0xcc,0xcc,0xcc,0xcc,0xcc,0x76,0x00,0x00,// 'u'
0x00,0x00,0x00,0x00,0xcc,0xcc,0xcc,0xcc,0x78,0x30,0x00,0x00,// 'v'
0x00,0x00,0x00,0x00,0xc6,0xc6,0xd6,0xd6,0x6c,0x6c,0x00,0x00,// 'w'
0x00,0x00,0x00,0x00,0xc6,0x6c,0x38,0x38,0x6c,0xc6,0x00,0x00,// 'x'
0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x3c,0x0c,0x18,0xf0,// 'y'
0x00,0x00,0x00,0x00,0xfc,0x8c,0x18,0x60,0xc4,0xfc,0x00,0x00,// 'z'
0x00,0x1c,0x30,0x30,0x60,0xc0,0x60,0x30,0x30,0x1c,0x00,0x00,// '{'
0x00,0x18,0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x18,0x00,0x00,// '|'
0x00,0xe0,0x30,0x30,0x18,0x0c,0x18,0x30,0x30,0xe0,0x00,0x00,// '}'
0x00,0x73,0xda,0xce,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// '~'
};

struct typFNT_GB16 // 汉字字模显示数据结构
{
  char Index[2];
  char Msk[24];
};

//取本例12*12汉字点阵时,先在Zimo软件中设置字体字号为宋体小五号,
//取点阵前要设置横向取模,字节不倒序,然后输入汉字并按下Ctrl+Enter,
//下面是“°”的点阵编码
code struct typFNT_GB16 GB_16[] = { 
{{"°"},{0x00,0x00,0x70,0x00,0x50,0x00,0x70,0x00,0x00,0x00,0x00,0x00,
         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}
};
INT8U gCurRow,gCurCol;   // 图形当前行、列存储，行高16点，列宽8点
INT8U tCurRow,tCurCol;   // 文本当前行、列存储，行高8点 ，列宽8点
INT8U ShowModeSW;        // 当前显示模式
INT16U  txthome,grhome;
//-----------------------------------------------------------------
// 状态位STA1,STA0判断(读写指令和读写数据)
//-----------------------------------------------------------------
INT8U Status_BIT_01() 
{


}

//-----------------------------------------------------------------
// 状态位ST3判断(数据自动写状态)
//-----------------------------------------------------------------
INT8U Status_BIT_3() 
{


}

//-----------------------------------------------------------------
// 写双参数的指令
//-----------------------------------------------------------------
INT8U LCD_Write_Command_P2(INT8U cmd,INT8U para1,INT8U para2) 
{


}

//-----------------------------------------------------------------
// 写单参数的指令
//-----------------------------------------------------------------
INT8U LCD_Write_Command_P1(INT8U cmd,INT8U para1) 
{


}

//-----------------------------------------------------------------
// 写无参数的指令
//-----------------------------------------------------------------
INT8U LCD_Write_Command(INT8U cmd) 
{


}

//-----------------------------------------------------------------
// 写数据
//-----------------------------------------------------------------
INT8U LCD_Write_Data(INT8U dat) 
{


}

//-----------------------------------------------------------------
// 读数据
//-----------------------------------------------------------------
INT8U LCD_Read_Data() 
{


}

//-----------------------------------------------------------------
// 设置当前地址
//-----------------------------------------------------------------
void Set_LCD_POS(INT8U row, INT8U col)
{
	INT16U Pos;	
	Pos = row * LCD_WIDTH + col;
	LCD_Write_Command_P2(LC_ADD_POS,Pos % 256, Pos / 256);
    
	gCurRow = row;
	gCurCol = col;
}

//-----------------------------------------------------------------
// LCM 初始化
//-----------------------------------------------------------------
void LCD_Initialise()
{
	RESET = 0;
	RESET = 1;
	LCD_Write_Command_P2(LC_TXT_STP,0x00,0x00);      //文本显示区首地址
	LCD_Write_Command_P2(LC_TXT_WID,LCD_WIDTH,0x00); //文本显示区宽度
	LCD_Write_Command_P2(LC_GRH_STP,0x00,0x00);      //图形显示区首地址
	LCD_Write_Command_P2(LC_GRH_WID,LCD_WIDTH,0x00); //图形显示区宽度     
	LCD_Write_Command_P1(LC_CGR_POS, CGRAMSTART >> 11);    
	LCD_Write_Command(LC_CUR_SHP | 0x01);            //光标形状
	LCD_Write_Command(LC_MOD_OR);                    //显示方式设置
	LCD_Write_Command(LC_DIS_SW  | 0x08);    
	grhome = GRSTART;
    txthome = TXTSTART;
}

//-----------------------------------------------------------------
// ASCII及汉字显示
//-----------------------------------------------------------------
void Disp_Str_at_xy(INT8U x,INT8U y,char *Buffer)
{
	char c1,c2,cData;
	INT8U i = 0,j,k,uLen;	
	uLen = strlen(Buffer);
	while(i < uLen)
	{
		c1 = Buffer[i];c2 = Buffer[i+1]; 		
		Set_LCD_POS(y,x / 8);		
		//ASCII字符显示
		if(c1 >= 0) 
		{
		    if(c1 < 0x20)
		    {
		        switch(c1)
		        {
		            case CR:
		            case LF:      //回车或换行
		                i++;
						x = 0;
		                if(y < 112) y += HZ_CHR_HEIGHT;
		                continue;                        
		            case BS:      //退格
						i++;
		                if(y > ASC_CHR_WIDTH) y -= ASC_CHR_WIDTH;
		                cData = 0x00;
		                break;
		        }
		    } 
		    for(j = 0; j < ASC_CHR_HEIGHT; j++)
		    {
		        if(c1 >= 0x1F)
		        {
				   	cData = ASC_MSK[ (c1 - 0x1F) * ASC_CHR_HEIGHT + j];
					Set_LCD_POS( y + j , x / 8);
					if( (x % 8) == 0)
					{
						LCD_Write_Command(LC_AUT_WR);
			           	LCD_Write_Data(cData);	
			        	LCD_Write_Command(LC_AUT_OVR);
					}
					else
						OutToLCD(cData,x,y+j);
		        }
		        Set_LCD_POS(y + j, x / 8);
		    }
		    if(c1 != BS) x += ASC_CHR_WIDTH; 	    
		}
		
		//中文字符显示
		else  
		{ 			
		    for(j = 0;j < sizeof(GB_16)/sizeof(GB_16[0]);j++)
		    {
		        if(c1 == GB_16[j].Index[0] && c2 == GB_16[j].Index[1])
		        break;
		    }
		    for(k = 0;k < HZ_CHR_HEIGHT; k++)
		    {				
		        Set_LCD_POS(y + k, x / 8);
		        if(j < sizeof(GB_16)/sizeof(GB_16[0]))
		        {
					c1 = GB_16[j].Msk[k*2];
					c2 = GB_16[j].Msk[k*2+1];
				}
				else c1 = c2 = 0;	   
					
				if((x % 8) == 0)
				{
					LCD_Write_Command(LC_AUT_WR);
					LCD_Write_Data(c1);
			        LCD_Write_Command(LC_AUT_OVR);
		        }
				else OutToLCD(c1,x,y + k); 					
				
				if(((x + 2 + HZ_CHR_WIDTH / 2) % 8) == 0)
				{
					LCD_Write_Command(LC_AUT_WR);
					LCD_Write_Data(c2);
					LCD_Write_Command(LC_AUT_OVR);
		        }
				else
					OutToLCD(c2,x + 2 + HZ_CHR_WIDTH / 2,y + k);
		    }
		    x += HZ_CHR_WIDTH;
		    i++;
		} 
		i++;
	}
}

//-----------------------------------------------------------------
// 输出起点x不是8的倍数时,原字节分成两部分输出到LCD
//-----------------------------------------------------------------
void OutToLCD(INT8U Dat,INT8U x,INT8U y)
{
    INT8U dat1,dat2,a,b;
    b = x % 8; a = 8 - b; 
    Set_LCD_POS(y,x / 8);
    LCD_Write_Command(LC_AUT_RD); 
    dat1 = LCD_Read_Data();
    dat2 = LCD_Read_Data();    
    //将读取的前后两字节分别与待显示字节的前后部分组合
    dat1 = (dat1 & (0xFF<<a)) | (Dat>>b);
    dat2 = (dat2 & (0xFF>>b)) | (Dat<<a);
    LCD_Write_Command(LC_AUT_OVR);
    Set_LCD_POS(y,x / 8);    
    //输出组合后的两字节
    LCD_Write_Command(LC_AUT_WR); 
    LCD_Write_Data(dat1);    
    LCD_Write_Data(dat2);
    LCD_Write_Command(LC_AUT_OVR);
}

//-----------------------------------------------------------------
// 绘制图像(图像数据来自于Flash程序ROM空间)
//-----------------------------------------------------------------
void Draw_Image(INT8U *G_Buffer, INT8U Start_Row, INT8U Start_Col)
{   
    INT16U i,j,W,H;
    //图像行数控制(G_Buffer的前两个字节分别为图像宽度与高度)
    W = G_Buffer[1];
    for(i = 0;i < W;i++)    
    {
       Set_LCD_POS(Start_Row + i,Start_Col);
       LCD_Write_Command(LC_AUT_WR); 
       //绘制图像每行像素
       H = G_Buffer[0];
       for( j = 0; j < H / 8; j++)  
         LCD_Write_Data(G_Buffer[ i * ( H / 8 ) + j + 2 ]);
       LCD_Write_Command(LC_AUT_OVR);
    }
}

//-----------------------------------------------------------------
/*   下列函数本例未用
//-----------------------------------------------------------------
// 绘点函数
// 参数:点的坐标,模式1/0分别为显示与清除点
//-----------------------------------------------------------------
void Pixel(INT8U x,INT8U y, INT8U Mode)
{
    INT8U start_addr, dat;
    start_addr = 7 - ( x & 0x07);
    dat = LC_BIT_OP | start_addr;       //生成位操作命令绘点数据    
    if (Mode) dat |= 0x08;
    Set_LCD_POS(y, x >> 3);
    LCD_Write_Command(LC_BIT_OP | dat); //写数据
}

//-----------------------------------------------------------------
// 两数交换
//-----------------------------------------------------------------
void Exchange(INT8U *a, INT8U *b)
{
   INT8U t;
   t = *a; *a = *b; *b = t;
}

//-----------------------------------------------------------------
// 绘制直线函数(本例未使用)
// 参数:起点与终点坐标,模式为显示(1)或清除(0),点阵不超过255*255)
//-----------------------------------------------------------------
void Line(INT8U x1,INT8U y1, INT8U x2,INT8U y2, INT8U Mode)
{
    INT8U x,y;        //绘点坐标
    float k,b;        //直线斜率与偏移
    
    if( fabs(y1 - y2) <= fabs( x1 - x2) )
    {
        k = (float)(y2 - y1) / (float)(x2 - x1) ;
        b = y1 - k * x1;             
        if( x1 > x2 ) Exchange(&x1, &x2);        
        for(x = x1;x <= x2; x++)
        {
            y = (INT8U)(k * x + b);
            Pixel(x, y, Mode);
        }
    }
    else 
    {
        k = (float)(x2 - x1) / (float)(y2 - y1) ;
        b = x1 - k * y1;        
        if( y1 > y2 ) Exchange(&y1, &y2);
        for(y = y1;y <= y2; y++)
        {
            x = (INT8U)(k * y + b);
            Pixel( x , y,Mode );
        }
    }
}
*/

