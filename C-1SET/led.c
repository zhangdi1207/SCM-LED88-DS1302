#include"head.h"


void select(ul row,ul column)
{
	uchar i;
	for(i=31;i>=0;i--)
	{

		ROWD=(row>>i)&0x01;
		COLD=(column>>i)&0x01;
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
	for(i=0;i<row;i++)
	{
		rlist<<=1;
		rlist|=0x01;
	}
	for(i=0;i<column;i++)
	{
		clist<<=1;
		clist |= 0x01;
	}
	select(rlist,0xffffffff);
	select(0,clist);


}