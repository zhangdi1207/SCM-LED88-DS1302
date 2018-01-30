#include"head.h"


/*
//列74HC595的数据线
sbit ColumnData = P1^0;
sbit ColumnSHCP = P1^1;
sbit ColumnSTCP = P1^2;

//行、列芯片的片选
sbit RCChannelData = P3^3;
sbit RCChannelSHCP = P3^6;
sbit RCChannelSTCP = P3^7;

//行74HC138的数据
sbit RowData0 = P3^0;
sbit RowData1 = P3^1;
sbit RowData2 = P3^2;

//行、列选择按钮
sbit RowSelect = P3^4;	   
//sbit RowSelect = P5^4;		 //stc15f408as 16脚
sbit ColumnSelect = P1^7;
//sbit ColumnSelect = P5^5;		 //stc15f408as 16脚

*/

void chipSelect( uchar row,uchar column)
{
	uchar i,dat;
	dat= ~((0x01<<(row/8)) + (0x10<<(column/8))); 
	for(i=0;i<8;i++)
	{
		RCChannelSHCP=0;
		RCChannelData=dat&0x80;
		dat=dat<<1;
		RCChannelSHCP=1;
	}
	RCChannelSTCP=0;
	nop();
	nop();
	RCChannelSTCP=1;
}

void columnSelect(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		ColumnSHCP=0;
		ColumnData=dat&0x80;
		dat=dat<<1;
		ColumnSHCP=1;
	}
	ColumnSTCP=0;
	nop();
	nop();
	ColumnSTCP=1;	
}

void rowSelect(bit rowt,bit rows,bit rowf)
{
	RowData0 = rowf;
	RowData1 = rows;
	RowData2 = rowt;
}


void show(uint i)
{
	uchar row,column,columnData;
	bit rowt,rows,rowf;
	ColumnSelect=~ColumnSelect;
	row= i/32;
	column=i%32;
	columnData=0x01<<(column%8);
	rowf=(row%8)%2;
	rows=((row%8)/2)%2;
	rowt=((row%8)/4)%2;
	chipSelect(row,column);
	columnSelect(columnData);
	rowSelect(rowt,rows,rowf);

	

}