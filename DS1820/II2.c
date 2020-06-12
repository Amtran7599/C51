#include<reg52.h>
#include"DS18B20.h"
#define uint unsigned int
#define uchar unsigned char
sbit LCD1=P2^2;
sbit LCD2=P2^3;
sbit LCD3=P2^4;
uchar code smg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar disp[8];
void delay(uint i)
{
	while(i--);	
}
void datapros(int temp)
{
	float tp;
	if(temp<0)
	{
		disp[0]=0x40;
		temp=temp-1;
		tp=~temp;
		temp=tp*0.0625*100+0.5;
	}
		else
		{
			disp[0]=0x00;
			tp=temp;
			temp=tp*0.0625*100+0.5;
		}
	disp[1]=smg[temp%10000/1000];
	disp[2]=smg[temp%1000/100];
	disp[3]=smg[temp%100/10];
	disp[4]=smg[temp%10];
}
void display()
{
 uchar i;
 for(i=0;i<6;i++)
	{
	switch(i)
	{
		case(0):LCD1=1;LCD2=1;LCD3=1;break;
		case(1):LCD1=0;LCD2=1;LCD3=1;break;
		case(2):LCD1=1;LCD2=0;LCD3=1;break;
		case(3):LCD1=0;LCD2=0;LCD3=1;break;	
		case(4):LCD1=1;LCD2=1;LCD3=0;break;
		case(5):LCD1=0;LCD2=1;LCD3=0; break;
	}
	P0=disp[i];
	delay(10);
	P0=0x00;
}
}
void main()
{
	while(1)
	{
		datapros(ReadTemp());
		display();
	}
}