#include"head.h"


void select(ul row,ul column) //注意row需要取反
{
	int i;
	row = ~row;
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
//显示设置

void show(uint signalMonth)	//每次显示8行
{
	uchar row,column,i;
	ul rlist=0,clist = 0;
	uint myMonth;
	myMonth = signalMonth;
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
/*
void show(uint signalMonth)	//每次显示半行
{
	uchar row,column,i; 
	ul rlist=0,clist=0; 
	uint myMonth;
	myMonth=signalMonth;
	row = myMonth/32;
	column = myMonth%32;
	for(i=0;i<row;i++)
	{
		rlist=1;
		rlist = rlist<<i;
		select(rlist,0xffff);
		select(rlist,0xffff0000);
	}
	for(i=0;i<column;i++)
	{
		clist<<=1;
		clist |= 0x01;
	}
	rlist=1;
	rlist=rlist<<row;
	select(rlist,clist&0xffff);
	select(rlist,clist&0xffff0000);


}
//*/