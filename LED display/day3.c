#include "reg52.h"	
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
uchar code smg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar num,shi,ge,bai,i,aa;
uint temp;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
void delay(uint x)
{
	while(x--);
}
void display(uchar ge,uchar shi,uchar bai);
void int1();
void main()
{
	int1();
	while(1)
	{
		if(aa==2)
		{
			ge++;
			if(ge==10)
			{
				shi++;
				ge=0;
			}
			if(shi==10)
			{
				bai++;
				shi=0;
			}
			if (bai==10)
			{
				ge=0;
				shi=0;
				bai=0;
			}
			aa=0;
		}
		display(ge,shi,bai);
	}
}
	
void display(uchar ge,uchar shi,uchar bai)
{
	for(i=0;i<3;i++)
	{
		switch(i)
		{
			case(0):LSA=1,LSB=1,LSC=1;break;
			case(1):LSA=0,LSB=1,LSC=1;break;
			case(2):LSA=1,LSB=0,LSC=1;break;
		}
		if(i==0) P0=smg[bai];
		if(i==1) P0=smg[shi];
		if(i==2) P0=smg[ge];
		delay(1);
		P0=0x00;
	}
}
void int1 ()
{
	aa=0;
	temp=0;
	EA=1;
	ET0=1;
	TR0=1;
	TH0=(65535-50000)/256;
	TL0=(655535-50000)%256;
}
void intr() interrupt 1
{
	TH0=(65535-50000)/256;
	TL0=(655535-50000)%256;
	aa++;
}
