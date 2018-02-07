#include <reg52.h>
#include <intrins.h>
#define nop() _nop_()
#define uchar unsigned char
#define uint unsigned int
#define ul unsigned long
#define CMD_IDLE    0               //空闲模式
#define CMD_READ    1               //IAP字节读命令
#define CMD_PROGRAM 2               //IAP字节编程命令
#define CMD_ERASE   3  
#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
#define MONTH_DATA 0x0000
#define WDT			0x35			//看门狗初始化@12MHz，2.9071s
//DS1302寄存器定义
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


//初始化年月日等时间值
#define OR_YEA 00
#define OR_MON 01
#define OR_DAT 01
#define OR_HOU 00
#define OR_MIN 00
#define OR_SEC 00

#define SHOWPRA 100000 //显示多少次统计一下时间

#define TESTFLAG 1


sfr AUXR        =   0x8e;
sfr IAP_DATA    =   0xC2;           //IAP数据寄存器
sfr IAP_ADDRH   =   0xC3;           //IAP地址寄存器高字节
sfr IAP_ADDRL   =   0xC4;           //IAP地址寄存器低字节
sfr IAP_CMD     =   0xC5;           //IAP命令寄存器
sfr IAP_TRIG    =   0xC6;           //IAP命令触发寄存器
sfr IAP_CONTR   =   0xC7;           //IAP控制寄存器
sfr CLK_DIV = 0x97;					//时钟命令寄存器
sfr WDT_CONTR = 0xc1;

//行列数据74HC595
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

//按键
sbit BUTTON = P1^7;



//DS1302数据线
sbit DS1302RST = P1^0;
sbit DS1302CLK = P1^1;
sbit DS1302IO = P1^2;

//数据
uchar row595[4]={0,0,0,0};
uchar column595[4]={0,0,0,0};



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

void longToRow(ul dat,uchar arr[4])
{
	arr[0]=dat;
	arr[1]=dat>>8;
	arr[2]=dat>>16;
	arr[3]=dat>>24;						  
}

void changeFor788AS()
{
	uchar i,left,right;
	left=0;
	right=0;
	for(i=0;i<4;i++)
	{
		if(row595[i]&0x01)		//1->9
			right=right|0x80;
		if(row595[i]&0x02)	   //2->14
			right=right|0x04;
		if(row595[i]&0x04)	  //3->8
			left=left|0x01;	
		if(row595[i]&0x08)	  //4->12
			right=right|0x10;
		if(row595[i]&0x10)	  //5->1
			left=left|0x80;
		if(row595[i]&0x20)	  //6->7
			left=left|0x02;
		if(row595[i]&0x40)	  //7->2
			left=left|0x40;
		if(row595[i]&0x80)	  //8->5
			left=left|0x08;

		if(column595[i]&0x01)	  //1->13
			right=right|0x08;
		if(column595[i]&0x02)	  //2->3
			left=left|0x20;
		if(column595[i]&0x04)	  //3->4
			left=left|0x10;
		if(column595[i]&0x08)	  //4->10
			right=right|0x40;
		if(column595[i]&0x10)	  //5->6
			left=left|0x04;
		if(column595[i]&0x20)	  //6->11
			right=right|0x20;
		if(column595[i]&0x40)	  //7->15
			right=right|0x02;
		if(column595[i]&0x80)	  //8->16
			right=right|0x01;
	}
}

void select(ul row,ul column)
{
	int i;
	longToRow(row,row595);
	longToRow(column,column595);
	changeFor788AS();
	for(i=7;i>=0;i--)
	{

		ROW0D=row595[0]&0x01;
		COL0D=column595[0]&0x01;
		ROW1D=row595[1]&0x01;
		COL1D=column595[1]&0x01;
		ROW2D=row595[2]&0x01;
		COL2D=column595[2]&0x01;
		ROW3D=row595[3]&0x01;
		COL3D=column595[3]&0x01;
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
	ul rlist=0,clist=0; 
	uint myMonth;
	myMonth=signalMonth;
	row = myMonth/32;
	column = myMonth%32;
	/*
	for(i=0;i<row;i++)
	{
		rlist=1;
		rlist = rlist<<i;
		select(~rlist,0xffff);
		select(~rlist,0xffff0000);
	}
	for(i=0;i<column;i++)
	{
		clist<<=1;
		clist |= 0x01;
	}
	rlist=1;
	rlist=rlist<<row;
	select(~rlist,clist&0xffff);
	select(~rlist,clist&0xffff0000);
	//*/
	select(0x0,0xffffffff);

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