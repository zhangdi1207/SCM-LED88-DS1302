#include"head.h"

/*
//DS1302Êý¾ÝÏß
sbit DS1302RST = P1^3;
sbit DS1302CLK = P1^4;
sbit DS1302IO = P1^5;


#define WRITE_SEC	 0X80
#define WRITE_MIN	 0X82
#define WRITE_HOU	 0X84
#define WRITE_DAT	 0X86
#define WRITE_MON	 0X88
#define WRITE_YEA	 0X8C

#define READ_SEC	 0x81
#define READ_MIN	 0x83
#define READ_HOU	 0x85
#define READ_DAT	 0x87
#define WRITE_PROTECT 0X8E
*/
void write1302(uchar addr,uchar dat)
{
	uchar i,temp;
	DS1302RST=0;
	DS1302CLK=0;
	DS1302RST=1;
	for(i=8;i>0;i--)
	{
		DS1302CLK=0;
		temp=addr;
		DS1302IO=(bit)(temp&0x01);
		addr>>=1;
		DS1302CLK=1;
	}
	for(i=8;i>0;i--)
	{
		DS1302CLK=0;
		temp=dat;
		DS1302IO=(bit)(temp&0x01);
		dat>>=1;
		DS1302CLK=1;
	}
}

uchar read1302(uchar addr)	 //BCDÂë
{
	uchar i,temp;
	DS1302RST=0;
	DS1302CLK=0;
	DS1302RST=1;
	for(i=8;i>0;i--)
	{
		DS1302CLK=0;
		temp=addr;
		DS1302IO=(bit)(temp&0x01);
		addr>>=1;
		DS1302CLK=1;
	}
	for(i=8;i>0;i--)
	{
		temp= DS1302IO;
		DS1302CLK=1;
		temp>>=1;
		DS1302CLK=0;
	}
	DS1302RST=0;
	/*
	dat1=temp;
	dat2=dat1/16;
	dat1=dat1%16;
	dat1=dat1+dat2*10;
	return dat1;
	*/
	return temp;
}

//void initDS1302(uchar sec=OR_SEC,uchar min=OR_MIN,uchar hou=OR_HOU)
void initDS1302(uchar sec,uchar min,uchar hou)
{
	 write1302(WRITE_PROTECT,0X00);
	 write1302(WRITE_SEC,sec);
	 write1302(WRITE_MIN,min);
	 write1302(WRITE_HOU,hou);
	 write1302(WRITE_DAT,OR_DAT);
	 write1302(WRITE_MON,OR_MON);
	 write1302(WRITE_YEA,OR_YEA);
}


uint calMonth(uint month)
{
	uchar date;
	uchar sec,min,hou;
	date = read1302(READ_DAT);
	if(date == 0x31)
	{
		month++;
		flashMonthChange(month);
		hou = read1302(READ_HOU);
		min = read1302(READ_MIN);
		sec = read1302(READ_SEC);
		initDS1302(sec,min,hou);
	}
	return month;
}