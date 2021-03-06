//-----------------------------------------------------------------
//  名称: 按键控制定时器选播多段音乐
//-----------------------------------------------------------------
//  说明: 本例内置三段音乐曲目,K1可启停音乐播放,K2用于选择音乐段.
//-----------------------------------------------------------------
#include <reg51.h>
#include <intrins.h>
#define INT8U	unsigned char
#define INT16U  unsigned int
//当前曲目索引,音符索引
INT8U Song_idx = 0, Tone_idx = 0;
sbit SPK = P3^7; //蜂鸣器
sbit K1  = P1^0; //播放和停止键K1( 曲目选择键K2由INT0中断控制)
//数码管段码表
INT8U code SEG_CODE[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
//14个音符在TIMER0模式0下的定时/计数寄存器值初值表
INT8U code HI_LIST[] = 
{ 0,226,229,232,234,236,238,240,241,243,244,245,246,247,248 };
INT8U code LO_LIST[] = 
{ 0,  4, 12, 9, 20,  2,  8,  6,  2, 22,  5, 26,  1,  4,  2 };
//三段曲目音符(这些数据是任意编写的,读者可以自行修改)
INT8U code Song[][50] = 
{
 {1,2,3,1,1,2,3,1,3,4,5,3,4,5,5,6,5,3,5,6,5,3,5,3,2,1,2,1,-1},
 {3,3,3,4,5,5,5,5,6,5,3,5,3,2,1,5,6,5,3,3,2,1,1,-1},
 {3,2,1,3,2,1,1,2,3,1,1,2,3,1,3,4,5,3,4,5,5,6,5,3,5,3,2,1,3,2,1,1,-1}
};
//三段曲目节拍
INT8U code Len[][50] = 
{
 {1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1,2,-1},
 {1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,2,-1},
 {1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,1,2,2,-1}
};
//-----------------------------------------------------------------
// 延时子程序	 
//-----------------------------------------------------------------
void delay_ms(INT16U ms) 
{
	INT8U i; while(ms--) for(i = 0; i < 120; i++);
}

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main()
{
	P2 = 0xC0;			  	//开始显示0
	IE = 0x8B;				//允许TIMER0与INT0中断
	TMOD = 0x00;
	IT0 = 1;				//外部中断0中断触发方式：下降沿触发
	IP = 0x01;				//INT0设为高优先级
	while(1)
	{
		while(K1 == 1);		//等待按下播放键
		while(K1 == 0);		//等待释放播放键
		Tone_idx = 0;		//从第0个音符开始
		TR0 = 1;			//开始播放
		/* 播放过程中按下K1可提前停止播放（K1=0） */
		/* 如果切换音乐段会触发外部中断，导致TR=0，播放也会停止 */
		while(Song[Song_idx][Tone_idx] != -1 && K1 == 1 && TR0 == 1)
		{
			/* 每一音符的播放延时长度变化而形成节拍 */
			delay_ms(300 * Len[Song_idx][Tone_idx]);
			Tone_idx++;				//下一音符索引
		}
		TR0 = 0;	   		//停止播放
		while(K1 == 0);		//如果提前停止播放，按键未释放时则等待
	}
}

//-----------------------------------------------------------------
// 外部中断0(K2)
//-----------------------------------------------------------------
void EX0_INT() interrupt 0
{
	TR0 = 0;					//结束或中途切换歌曲时停止播放
	if (++Song_idx == 3)		//K2选择下一曲目，到底回头
		Song_idx = 0;
	Tone_idx = 0;				//音符索引归0
	P2 = SEG_CODE[Song_idx];	//数码管
}

//-----------------------------------------------------------------
// 定时器0中断函数
// SPK输出脉冲,并根据曲目索引及音符索引设置新的定时初值
//-----------------------------------------------------------------
void T0_INT() interrupt 1
{
	SPK = !SPK;
	TH0 = HI_LIST[Song[Song_idx][Tone_idx]];
	TL0 = LO_LIST[Song[Song_idx][Tone_idx]];
}
