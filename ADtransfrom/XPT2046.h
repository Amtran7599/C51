#ifndef   __XPT2026_H_
#define   __XPT2046_H_
#include<reg52.h>
#include<intrins.h>
#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif
#ifndef ulong
#define ulong unsigned long
#endif
//--定义使用的IO口--//
sbit DOUT = P3^7; //输出
sbit CLK = P3^6;	//时钟
sbit DIN =P3^4;		//输入
sbit CS = P3^5;		//片选

uint Read_AD_Data(uchar cmd);
uint SPI_Read(void);
void SPI_Write(uchar dat);
#endif
