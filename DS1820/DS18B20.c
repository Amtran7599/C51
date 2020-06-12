#include"DS18B20.h"
void Delay1ms(uint y)
{
	uint x;
	for( ; y>0; y--)
	{
		for(x=110; x>0; x--);
	}
}
uchar Ds18b20Init()
{
	uchar i;
	DSPORT = 0;	
	i=70;
	while(i--);
	DSPORT = 1;			
	i = 0;
	while(DSPORT)	
	{
		Delay1ms(1);
		i++;
		if(i>5)
		{
			return 0;
		}
	
	}
	return 1;
}
void Ds18b20WriteByte(uchar dat)
{
	uint i, j;

	for(j=0; j<8; j++)
	{
		DSPORT = 0;	     	 
		i++;
		DSPORT = dat & 0x01;  
		i=6;
		while(i--); 
		DSPORT = 1;	
		dat >>= 1;
	}
}
uchar Ds18b20ReadByte()
{
	uchar byte, bi;
	uint i, j;	
	for(j=8; j>0; j--)
	{
		DSPORT = 0;
		i++;
		DSPORT = 1;
		i++;
		i++;
		bi = DSPORT;
		byte = (byte >> 1) | (bi << 7);						  
		i = 4;		
		while(i--);
	}				
	return byte;
}
void	ChangeTemp() 
{
	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);//����ROM
	Ds18b20WriteByte(0x44);//ת��
}
void ReadTempCom()//���Ͷ�ȡ����
{
	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);//����ROM
	Ds18b20WriteByte(0xbe);//��ȡRAM����
}
int ReadTemp()//��ȡ�¶�
{
	int t=0;
	uchar th,tl;
	ChangeTemp();
	ReadTempCom();
	tl=Ds18b20ReadByte();
	th=Ds18b20ReadByte();
	t=th;
	t<<=8;
	t|=tl;
	return t;
}
