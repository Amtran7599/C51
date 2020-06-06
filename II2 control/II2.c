#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit sda=P2^0;
sbit scl=P2^1;
sbit LCD1=P2^2;
sbit LCD2=P2^3;
sbit LCD3=P2^4;
uchar code smg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void delay()
{;;}
void delay1(uchar x)
{
	uchar b;
	for(x;x>0;x--)
		for(b=110;b>0;b--);
}	
void start()
{
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();
}
void stop()
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();
}
void respons()
{
	uchar i;
	scl=1;
	delay();
	while((sda==1)&&(i>255))i++;
	scl=0;
	delay();
}
void init()
{
	sda=1;
	delay();
	scl=1;
	delay();
}
void write(uchar date)
{
	uchar i,ans;
	ans=date;
	for(i=0;i<8;i++)
		{
			ans=ans<<1;
			scl=0;
			delay();
			sda=CY;
			delay();
			scl=1;
			delay();
		}
		scl=0;
		delay();
		sda=1;						//ÊÍ·Å×ÜÏß 
		delay();
}
uchar read()
{
	uchar i,ans;
	scl=0;
	delay();
	sda=1;
	delay();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay();
		ans=ans<<1;
		ans|=sda;
		scl=0;
		delay();
	}
	return ans;
}
void Write_add(uchar address,uchar date)
{
	start();
	write(0xa0);
	respons();
	write(address);
	respons();
	write(date);
	respons();
	stop();
}
uchar Random_read(uchar address)
{
	uchar ans;
	start();
	write(0xa0);
	respons();
	write(address);
	respons();
	start();
	write(0xa1);
	respons();
	ans=read();
	stop();
	return ans;
}
void display(uchar ans)
{
	uchar ge,shi,i=0;
	ge=ans%10;
	shi=ans/10;
	for(i=0;i<3;i++){
	switch(i)
	{
		case 0:LCD1=1;LCD2=1;LCD3=1;break;
		case 1:LCD1=0;LCD2=1;LCD3=1;break;
	}
	if(i==0) P0=smg[shi];
	if(i==1) P0=smg[ge];
	delay1(1);
	P0=0x00;
}
}
void main(){
	uchar ans;
	init();
	Write_add(23,31);
	delay1(100);
	ans=Random_read(23);
	P2=ans;
	while(1)
	{
		display(ans);
	}
}