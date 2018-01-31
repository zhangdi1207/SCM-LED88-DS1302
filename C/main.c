#include"head.h"

void main()
{
	uint showCount = 0;
	uint monthCount = 1;
	uint i,j;
	WDT_CONTR = WDT;
	Delay1s();
	//1302初始化、读取MONTH_DATA为最新的month数据，每次设定或ds1302计时超过30天，(设定month数据至flash或者30天后month+1存至flash)然后初始化da1302
	initDS1302(0,0,0);
	monthCount = eepromInit();
	while(1)
	{
		//启动看门狗
		WDT_CONTR = WDT;
		showCount++;
		if(showCount == SHOWPRA)
		{
			monthCount = calMonth(monthCount);
			showCount=0;
		}
		//monthCount=400;
		j=0;
		for(i=0;i<monthCount;i++)
		{
			show(i);
			//j+=16;
			/*
			for(j=0;j<30;j++)
			Delay40us();
			//*/
		}
		
	}
}