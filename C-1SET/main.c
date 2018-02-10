#include"head.h"

void main()
{
	ul showCount = 0;
	uint monthCount = 1;
	uint i=0,j=0;
	WDT_CONTR = WDT;
	if(!TESTFLAG)
		Delay1s();
	//1302初始化、读取MONTH_DATA为最新的month数据，每次设定或ds1302计时超过30天，(设定month数据至flash或者30天后month+1存至flash)然后初始化da1302
	initDS1302(0,0,0);
	monthCount = eepromInit();
	if(TESTFLAG)
		{
			flashMonthChange(1);
			monthCount=1;
		}
	while(1)
	{
		//启动看门狗
		WDT_CONTR = WDT;
		showCount++;
		//show(read1302(READ_SEC));
		/*
		if(showCount == (TESTFLAG?1:SHOWPRA))
		{
			monthCount = calMonth(monthCount);
			showCount=0;
			//P2=read1302(READ_SEC);
		}
		*/
		monthCount = calMonth(monthCount);
		for(j=0;j<2;j++)
			show(monthCount);
		monthSet();
		monthCount = eepromInit();

		
	}
}