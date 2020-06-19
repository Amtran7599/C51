#include<reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit LSA = P2^2;
sbit LSC = P2^3;
sbit LSB = P2^4;

sbit IRIN = P3^2;

u8 Irvalue[6];
u8 Time;

u8 Display[8];
u8 code smg[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0X76};
	
void delay(u16 i)
{
	while(i--);
}

void Digdisplay()
{
	u8 i;
	for(i=0;i<3;i++)
	{
		if(i == 0) {LSA = 1;LSB = 1;LSC = 1;}
		if(i == 1) {LSA = 0;LSB = 1;LSC = 1;}
		if(i == 2) {LSA = 1;LSB = 0;LSC = 1;}
		P0 = Display[i];
		delay(100);
		P0 = 0x00;
	}
}
void IrInit()
{
	IT0 = 1; //下降沿触发
	EX0  = 1; //打开外部中断0
	EA =1 ;//开启总中断
	IRIN = 1;
}
void main()
{
	IrInit();
	while(1)
	{
		Display[0] = smg[Irvalue[2]/16];
		Display[1] = smg[Irvalue[2]%16];
		Display[2] = smg[16];
		Digdisplay();
	}
}
void ReadIr() interrupt 0
{
	u8 j,k;
	u16 err;
	Time = 0;
	delay(700);//7ms;
	if(IRIN == 0)
	{
		err = 1000;
		while((IRIN == 0)&&(err>0))//等待9ms
		{
			delay(1);
			err--;
		}
		if(IRIN == 1)
		{
			err = 500;
			while(IRIN==1&&err > 0)//等450ms高电平
			{
				delay(1);
				err--;
			}
			for(k=0;k<4;k++)
		{
			for(j=0;j<8;j++)
			{
				err=60;
				while((IRIN ==0)&&(err>0))//先等560us
				{
					delay(1);
					err--;
				}
				err = 500;
				while(IRIN == 1 && err > 0)
				{
					delay(10);
					Time++;
					err--;
					if(Time > 30)
					{
						return ;
					}
				}
				Irvalue[k]>>=1;
				if(Time >= 8)	//Time大于560ms，判定1
				{
					Irvalue[k] |=0x80;
				}
				Time = 0;
			}
		}
		}
		if(Irvalue[2]!=~Irvalue[3])//数据错误，推出中断
		{
			return;
		}
	}
}