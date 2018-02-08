#include"head.h"

uchar judge()
{
	uchar i;
	ROWBUTTON=1;
	COLUMNBUTTON=1;
	if(!ROWBUTTON)
	{
		for(i=0;i<25;i++)
			Delay40us();
		ROWBUTTON=1;
		if(!ROWBUTTON)
			return 1;
	}
	if(!COLUMNBUTTON)
	{
		for(i=0;i<25;i++)
			Delay40us();
		COLUMNBUTTON=1;
		if(!COLUMNBUTTON)
			return 2;
	}
	return 0;
}

void rowSet()
{
	uint halfCount=100,changeCount=30; //闪烁效果显示halfCount次关闭显示，如果30次闪烁数据不再变化则锁定该改变
	uint month;//,i,j;
	bit changeFlag=0;
	month = eepromInit();
	do
	{
		changeCount=30;
		while(changeCount--)
		{
			for(halfCount=100;halfCount>0;halfCount--)
			{
				show(month);
			}
			for(halfCount=100;halfCount>0;halfCount--)
			{
				show(0);
			}
			if(1==judge())
			{
				month+=32;
				month%=1024;
				flashMonthChange(month);
				initDS1302(0,0,0);
				changeFlag=1;
				break;
			}
		}
	}
	while(changeFlag);	
}

void columnSet()
{
	uint halfCount=100,changeCount=30; //闪烁效果显示halfCount次关闭显示，如果30次闪烁数据不再变化则锁定该改变
	uint month;//,i,j;
	bit changeFlag=0;
	month = eepromInit();
	do
	{
		changeCount=30;
		while(changeCount--)
		{
			for(halfCount=100;halfCount>0;halfCount--)
			{
				show(month);
			}
			for(halfCount=100;halfCount>0;halfCount--)
			{
				show(0);
			}
			if(2==judge())
			{
				if(month%32==0)
					month-=31;
				else
					month++;
				flashMonthChange(month);
				initDS1302(0,0,0);
				changeFlag=1;
				break;
			}
		}
	}
	while(changeFlag);	
}





void monthSet()
{
	uchar setFlag=0;
	setFlag=judge();
	if(setFlag==1)
		rowSet();
	else if(setFlag==2)
		columnSet();
	
}