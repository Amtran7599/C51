#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar R,a=0,flag,count=0;
sbit beep = P1^5;
void main()
{
TMOD=0x21;
	SM0=0;
	SM1=1;
	REN=1;
	//PCON=0x80;		//��������������
	TH1=0xfd;				//��������ʼֵ
	TL1=0xfd;
	EA=1;						//�������ж�
	ES=1;						//���������ж�
	TR1=1; 					//�򿪶�ʱ��1
ET0=1;
TH0=(65535-50000)/256;
TL0=(65535-50000)%256;
	while(1)
	{
		if(flag==1)
		{
			ES=0;
			TR0=1; 			//�򿪶�ʱ��0
			flag=0;
			ES=1;
		}
		if(R=='1') a=8;
		if(R=='2') a=4;
		if(R=='3') a=2;
		if(R=='4') {TR0=0; ET0=0;}
		if(count==a)
		{	
			beep=~beep;
			count=0;
		}
	}
}
void Usart () interrupt 4
{
	R=SBUF;
	RI=0;
	flag=1;
}
void fenmingq () interrupt 1
{
	TH0=(65535-50000)/256;
	TL0=(65535-50000)%256;
	count++;
}