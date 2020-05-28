#include<reg52.h>
#define uint unsigned int 
#define uchar unsigned char
uchar code smg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar temp,ge,shi,bai,i;
uint num;
sbit LDA=P2^2;
sbit LDB=P2^3;
sbit LDC=P2^4;
void key();
void delay(uint x);
void display(uint num1);
void main()
{
	while(1)
	{
		key();
		P0=smg[num];
		//display(key()-1);
	}
}
void key()
{

	char a=0;
	P1=0x0f;
	if(P1!=0x0f)
	{
		delay(10);
		if(P1!=0x0f)
		{
			switch(P1)
			{
				case 0x07 :num=0;break;
				case 0x0b :num=1;break;
				case 0x0d:num=2;break;
				case 0x0e :num=3;break;
			}
		}
	}
	P1=0xf0;
	if(P1!=0xf0)
	{
		delay(10);
		if(P1!=0xf0)
		{
			switch(P1)
			{
				case 0x70: num=num;break;
				case 0xb0: num=num+4;break;
				case 0xd0: num=num+8;break;
				case 0xe0: num=num+12; break;
			}
		}
	}
	while((a<50)&&(P1!=0xf0))
	{
		a++;
		delay(1);
	}
}
void delay(uint x)
{
	uint y;
	for(x;x>0;x--)
		for(y=110;y>0;y--);
}
