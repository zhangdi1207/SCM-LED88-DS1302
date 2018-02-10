#include"head.h"

void changeDataTo595(ul dat[])
{
	uchar left[4]={0,0,0,0},right[4]={0,0,0,0};
	uchar i,tempRow,tempColumn;
	for(i=0;i<4;i++)
	{
		tempRow=dat[0]>>(i*8);
		tempColumn=dat[1]>>(i*8);

		if(tempRow&0x01)  //1->9
			right[i]|=0x80;
		if(tempRow&0x02)  //2->14
			right[i]|=0x04;
		if(tempRow&0x04)  //3->8
			left[i]|=0x01;
		if(tempRow&0x08)  //4->12
			right[i]|=0x10;
		if(tempRow&0x10)  //5->1
			left[i]|=0x80;
		if(tempRow&0x20)  //6->7
			left[i]|=0x02;
		if(tempRow&0x40)  //7->2
			left[i]|=0x40;
		if(tempRow&0x80)  //8->5
			left[i]|=0x08;

		if(tempColumn&0x01) //1->13
			right[i]|=0x08;
		if(tempColumn&0x02) //2->3
			left[i]|=0x20;
		if(tempColumn&0x04) //3->4
			left[i]|=0x10;
		if(tempColumn&0x08) //4->10
			right[i]|=0x40;
		if(tempColumn&0x10) //5->6
			left[i]|=0x04;
		if(tempColumn&0x20) //6->11
			right[i]|=0x20;
		if(tempColumn&0x40) //7->15
			right[i]|=0x02;
		if(tempColumn&0x80) //8->16
			right[i]|=0x01;
	}
	dat[0]=left[3]*0x1000000+left[2]*0x10000+left[1]*0x100+left[0];
	dat[1]=right[3]*0x1000000+right[2]*0x10000+right[1]*0x100+right[0];
}

void select(ul row,ul column) //注意row需要取反
{
	int i;
	ul hc595Data[2];
	ul left,right;
	row = ~row;
	hc595Data[0]=row;
	hc595Data[1]=column;
	changeDataTo595(hc595Data);
	left=hc595Data[0],right=hc595Data[1];
	for(i=31;i>=0;i--)
	{
		ROWD=(left>>i)&0x01;
		COLD=(right>>i)&0x01;
		SHCP=0;
		nop();
		SHCP=1;
	}
	STCP=0;
	nop();
	nop();
	STCP=1;
}
//显示设置

void show(uint signalMonth)	//每次显示8行
{
	uchar row,column,i;
	ul rlist=0,clist = 0;
	uint myMonth;
	WDT_CONTR = WDT;
	myMonth = signalMonth%1024;
	//row,column设置
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