//-----------------------------------------------------------------
//  名称: Nokia7110液晶头文件(SED1565)
//-----------------------------------------------------------------
#define INT8U   unsigned char
#define INT16U  unsigned int
#define _XTAL_FREQ 4000000UL
//-----------------------------------------------------------------
// SEG1565显示地址控制命令
//-----------------------------------------------------------------
#define PAGE    0xB0  //页地址
//SED1565最大分辨率为132*65,在驱动Nokia7710时,其起始列为第18列,而不是0列
//由于SED1565的列地址高4位命令为0001XXXX,低3位命令为0000XXXX
//将起始列(18->0x12)组合到列地址高4位与低4位命令后,可得:0001-0001与0000-0010
//即0x11与0x02,故有如下定义
#define COL_H4  0x11  //列地址高四位
#define COL_L4  0x02  //列地址低四位
#define LINE    0x40  //行地址
//-----------------------------------------------------------------
// 函数声明
//-----------------------------------------------------------------
void SPI_MasterInit();
void Nokia_Reset();
void Nokia_Init();
void Nokia_CLS();
void Write_Norkia_Command(INT8U cmd);
void Write_Nokia_Data(INT8U cd);
void Set_Nokia_LCD_POS(INT8U page, INT8U col) ;
void Show_Char(INT8U c, INT8U reverse); 
void Show_String(INT8U *str,INT8U reverse);	