#include"head.h"

void main()
{
	ul showCount = 0;
	uint monthCount = 1;
	uint i=0,j=0;
	WDT_CONTR = WDT;
	if(!TESTFLAG)
		Delay1s();
	//1302��ʼ������ȡMONTH_DATAΪ���µ�month���ݣ�ÿ���趨��ds1302��ʱ����30�죬(�趨month������flash����30���month+1����flash)Ȼ���ʼ��da1302
	initDS1302(0,0,0);
	monthCount = eepromInit();
	if(TESTFLAG)
		{
			flashMonthChange(1);
			monthCount=1;
		}
	while(1)
	{
		//�������Ź�
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