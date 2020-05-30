#include<reg52.h>
#include"XPT2046.h"
#define uint unsigned int
#define uchar unsigned char
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

uchar disp[4];
uchar code smg[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void dalay(uint i);
void datapros();
void Display();
void main()
{
	while(1)
	{
		datapros();
		Display();
	}
}
void datapros()
{
	uchar temp;
	static  uint x;
	if(x==50)
	{
		x=0;
		temp= Read_AD_Data(0x94); //AIN0¼ÌµçÆ÷
	}
	x++;
	disp[0]=smg[temp/1000];
	disp[1]=smg[temp/100%10];
	disp[2]=smg[temp%100/10];
	disp[3]=smg[temp%10]; 
}
void delay(uint i)
{
	while(i--);
}
void Display()
{
	uchar i;
	for(i=0;i<4;i++)
	{
		if(i==0) {LSA=1;LSB=1;LSC=1;}
		if(i==1) {LSA=0;LSB=1;LSC=1;}
		if(i==2) {LSA=1;LSB=0;LSC=1;}
		if(i==3) {LSA=0;LSB=0;LSC=1;}
		P0=disp[i];
		delay(100);
		P0=0x00;
	}
}