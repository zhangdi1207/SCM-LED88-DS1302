#include <reg52.h>
#include <intrins.h>
#define nop() _nop_()
#define uchar unsigned char
#define uint unsigned int
#define ul unsigned long
#define CMD_IDLE    0               //����ģʽ
#define CMD_READ    1               //IAP�ֽڶ�����
#define CMD_PROGRAM 2               //IAP�ֽڱ������
#define CMD_ERASE   3  
#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
#define MONTH_DATA 0x0000
#define WDT			0x35			//���Ź���ʼ��@12MHz��2.9071s
//DS1302�Ĵ�������
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


//��ʼ�������յ�ʱ��ֵ
#define OR_YEA 00
#define OR_MON 01
#define OR_DAT 01
#define OR_HOU 00
#define OR_MIN 00
#define OR_SEC 00

#define SHOWPRA 100000 //��ʾ���ٴ�ͳ��һ��ʱ��

#define TESTFLAG 1


sfr AUXR        =   0x8e;
sfr IAP_DATA    =   0xC2;           //IAP���ݼĴ���
sfr IAP_ADDRH   =   0xC3;           //IAP��ַ�Ĵ������ֽ�
sfr IAP_ADDRL   =   0xC4;           //IAP��ַ�Ĵ������ֽ�
sfr IAP_CMD     =   0xC5;           //IAP����Ĵ���
sfr IAP_TRIG    =   0xC6;           //IAP������Ĵ���
sfr IAP_CONTR   =   0xC7;           //IAP���ƼĴ���
sfr CLK_DIV = 0x97;					//ʱ������Ĵ���
sfr WDT_CONTR = 0xc1;

//��������74HC595
sbit SHCP = P3^0;
sbit STCP = P3^1;
sbit ROW0D = P3^2;
sbit COL0D = P3^3;
sbit ROW1D = P3^6;
sbit ROW2D = P3^7;
sbit ROW3D = P1^3;
sbit COL1D = P1^4;
sbit COL2D = P1^5;
sbit COL3D = P1^6;

//����
sbit BUTTON = P1^7;



//DS1302������
sbit DS1302RST = P1^0;
sbit DS1302CLK = P1^1;
sbit DS1302IO = P1^2;





uchar read1302(uchar addr)	 //BCD??
{
	uchar i,temp;
	DS1302RST=0;
	DS1302CLK=0;
	DS1302RST=1;
	for(i=8;i>0;i--)
	{
		DS1302CLK=0;
		DS1302IO=(bit)(addr&0x01);
		DS1302CLK=1;
		addr>>=1;
	}
	temp=0;
	nop();
	nop();
	for(i=8;i>0;i--)
	{  
		temp>>=1;
		DS1302CLK=0;		
		if(DS1302IO)
		{
			temp=temp|0x80;
		}
		DS1302CLK=1;

	}
	DS1302RST=0;
	DS1302CLK=1;
	DS1302IO=0;
	DS1302IO=1;
	return temp;
}

void select(ul row,ul column)		//ע��rowȡ��,���蹲��
{
	int i;
	row=~row;
	column=~column;
	for(i=7;i>=0;i--)
	{

		ROW0D=(row>>i)&0x01;
		COL0D=(column>>i)&0x01;
		ROW1D=(row>>(i+8))&0x01;
		COL1D=(column>>(i+8))&0x01;
		ROW2D=(row>>(i+16))&0x01;
		COL2D=(column>>(i+16))&0x01;
		ROW3D=(row>>(i+24))&0x01;
		COL3D=(column>>(i+24))&0x01;
		SHCP=0;
		nop();
		SHCP=1;
	}
	STCP=0;
	nop();
	nop();
	STCP=1;
}

void show(uint signalMonth)
{
	uchar row,column,i;
	ul rlist=0,clist = 0;
	uint myMonth;
	myMonth = signalMonth;
	//row,column����
	row = myMonth/32;
	column = myMonth%32;
	for(i=0;i<row/8;i++)
	{
		rlist = 0xff;
		rlist = rlist<<(i*8);
		select(rlist,0xffffffff);
	}
	rlist=0;	
	for(i=0;i<(row%8);i++)
	{
		rlist<<=1;
		rlist= rlist|0x01;
	}
	rlist=rlist<<(row/8*8);
	select(rlist,0xffffffff);
	for(i=0;i<column;i++)
	{
		clist<<=1;
		clist |= 0x01;
	}
	rlist=1;
	rlist<<=row;
	select(rlist,clist);
}


void main()
{
	uint monthCount;
	uchar i,j;
	while(1)
	{
		for(i=0;i<128;i++)
		{
			if(i%32 > 7)
				continue;
			P2=read1302(READ_SEC);
			monthCount=i;
			j=100;
			while(j--)
				show(monthCount);
		}
		//monthSet();	
	}
}