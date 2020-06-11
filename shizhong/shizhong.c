#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit RS=P2^6;
sbit LCDEN=P2^7;
sbit wr=P2^5;
sbit s1=P1^3;
sbit s2=P1^2;
sbit s3=P1^1;
sbit s4=P1^0;
sbit rd=P1^7;
sbit sd=P1^6;
uchar code table[]=" 2020-06-30 Wed";
uchar code table1[]="    00:00:00";
uchar mtable[]={31,28,31,30,31,30,31,31,30,31,30,31};
uchar code wtable[]="Mon TuesWed ThurFri Sat Sun ";
uchar count=0,shi,fen,miao,s1num,s2num;
char week,day,month;
uint year;
void delay(uint x)
{
	uint y;
	for(x;x>0;x--)
		for(y=110;y>0;y--);
}
void write_com(uchar com)
{
	wr=0;
	RS=0;
	LCDEN=0;
	P0=com;
	delay(5);
	LCDEN=1;
	delay(5);
	LCDEN=0;;
}
void write_dat(uchar dat)
{
	RS=1;
	LCDEN=0;
	wr=0;
	P0=dat;
	delay(5);
	LCDEN=1;
	delay(5);
	LCDEN=0;
}	
void init()
{
	uchar num;
	shi=23;
	fen=59;
	miao=55;
	year=2020;
	month=6;
	day=11;
	week=3;
	if(((year%100!=0)&&(year%4==0))||(year%400)==0) mtable[1]==29;
	else mtable[1]=28;
	LCDEN=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);
	for(num=0;num<16;num++)
	{
		write_dat(table[num]);
		delay(20);
	}
	write_com(0x80+0x40);
		for(num=0;num<10;num++)
	{
		write_dat(table1[num]);
		delay(20);
	}
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
}
void write_sfm(uchar add,uchar dat)
{
	uchar shi,ge;
	shi=dat/10;
	ge=dat%10;
	write_com(0x80+0x40+add);
	write_dat(0x30+shi);
	write_dat(0x30+ge);
}
void write_n(uchar add,uint dat)
{
	uchar ge,shi,bai,qian;
	qian=dat/1000;
	bai=(dat/100)%10;
	shi=(dat%100)/10;
	ge=dat%10;
	write_com(0x80+add);
	write_dat(0x30+qian);
	write_dat(0x30+bai);
	write_dat(0x30+shi);
	write_dat(0x30+ge);
}
void write_w(uchar add,uchar dat)
{
	uchar i;
	write_com(0x80+add);
	for(i=4*dat-4;i<4*dat;i++) 
			{
				write_dat(wtable[i]);
				delay(20);
			}
	
}
void write_yr(uchar add,uchar dat)
{
	uchar ge,shi;
	shi=dat/10;
	ge=dat%10;
	write_com(0x80+add);
	write_dat(0x30+shi);
	write_dat(0x30+ge);
}
void presskey()
{
	rd=0;
	if(s1==0)
	{
		delay(5);
		if(s1==0)
		{
			s1num++;
			while(!s1);
			TR0=0;
			write_com(0x0f);
			if(s1num==1)
			{
				write_com(0x80+0x40+11);
			}
			if(s1num==2)
			{
				write_com(0x80+0x40+8);
			}
			if(s1num==3)
			{
				write_com(0x80+0x40+5);
			}
			if(s1num==4)
			{
				s1num=0;
				write_com(0x0c);
				TR0=1;
			}
		}
	}
	else
		{
			if(s2==0)
			{
				delay(5);
				if(s2==0)
				{
					while(!s2);
					if(s1num==1)
					{
						miao++;
						if(miao==60)
							miao=0;
						write_sfm(10,miao);
						write_com(0x80+0x40+10);
					}
					if(s1num==2)
					{
						fen++;
						if(fen==60)
							fen=0;
						write_sfm(7,fen);
						write_com(0x80+0x40+7);
					}
					if(s1num==3)
					{
						shi++;
						if(shi==24)
							shi=0;
						write_sfm(4,shi);
						write_com(0x80+0x40+4);
					}
				}
			}
			if(s3==0)
			{
				delay(5);
				if(s3==0)
				{
					while(!s3);
					if(s1num==1)
					{
						if(miao==0)
						{	
							miao=60;
							write_sfm(10,miao);
							write_com(0x80+0x40+10);
						}
						miao--;
						write_sfm(10,miao);
						write_com(0x80+0x40+10);
					}
					if(s1num==2)
					{
						if(fen==0)
						{	
							fen=60;
							write_sfm(10,fen);
							write_com(0x80+0x40+7);
						}
						fen--;
						write_sfm(10,fen);
						write_com(0x80+0x40+7);
					}
					if(s1num==2)
					{
						if(shi==0)
						{	
							shi=24;
							write_sfm(4,shi);
							write_com(0x80+0x40+4);
						}
						shi--;
						write_sfm(10,shi);
						write_com(0x80+0x40+4);
					}
				}
			}
		}
		rd=1;
}
void presskey2()
{
	sd=0;
	if(s1==0)
	{
		delay(5);
		if(s1==0)
		{
			s2num++;
			while(!s1);
			TR0=0;
			write_com(0x0f);
			if(s2num==1)
			{
				write_com(0x80+2);
			}
			if(s2num==2)
			{
				write_com(0x80+7);
			}
			if(s2num==3)
			{
				write_com(0x80+10);
			}
			if(s2num==4)
			{
				write_com(0x80+13);
			}
			if(s2num==5)
			{
				s2num=0;
				write_com(0x0c);
				TR0=1;
			}
		}
	}
	else
		{
			if(s2==0)
			{
				delay(5);
				if(s2==0)
				{
					while(!s2);
					if(s2num==1)
					{
						year++;
						write_n(1,year);
						write_com(0x80+1);
						if(((year%100!=0)&&(year%4==0))||((year%400)==0)) mtable[1]=29;
							else mtable[1]=28;
					}
					if(s2num==2)
					{
						month++;
						if(month>12)
							month=1;
						write_yr(6,month);
						write_com(0x80+6);
					}
					if(s2num==3)
					{
						day++;
						if(day>mtable[month-1])
							day=1;
						write_yr(9,day);
						write_com(0x80+9);
					}
					if(s2num==4)
					{
						week++;
						if(week>7)
							week=1;
						write_w(12,week);
						write_com(0x80+12);
					}
				}
			}
			if(s3==0)
			{
				delay(5);
				if(s3==0)
				{
					while(!s3);
					if(s2num==1)
					{
						year--;
						write_n(1,year);
						write_com(0x80+1);
						if(((year%100!=0)&&(year%4==0))||((year%400)==0)) mtable[1]=29;
							else mtable[1]=28;
					}
					if(s2num==2)
					{
						month--;
						if(month==0)
							month=12;
						write_yr(6,month);
						write_com(0x80+6);
					}
					if(s2num==3)
					{
						day--;
						if(day==0)
							day=mtable[month-1];
						write_yr(9,day);
						write_com(0x80+9);
					}
					if(s2num==4)
					{
						week++;
						if(week==0)
							week=7;
						write_w(12,week);
						write_com(0x80+12);
					}
				}
			}
		}
		sd=1;
}
void main()
{
	init();
	while(1)
	{
		presskey();
		presskey2();
	};
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	count++;
	if(count==20)
	{
		count=0;
		miao++;
		if(miao>=60)
		{
			miao=0;
			fen++;
			if(fen>=60)
			{
				fen=0;
				shi++;
				if(shi>=24)
				{
					shi=0;
					day++;
					week++;
					if(week>7)
						week=1;
					if(day>table[month-1])
					{
						day=1;
						month++;
						if(month>12)
						{
							month=1;
							year++;
							if(((year%100!=0)&&(year%4==0))||(year%400)==0) mtable[1]==29;
							else mtable[1]=28;
						}
					}
				}
			}
		}
		write_n(1,year);
		write_yr(6,month);
		write_yr(9,day);
		write_w(12,week);
		write_sfm(4,shi);
		write_sfm(7,fen);
		write_sfm(10,miao);
	}
}