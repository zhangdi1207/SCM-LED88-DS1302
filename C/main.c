#include"head.h"

void main()
{
	uint showCount = 0;
	uint monthCount = 1;
	uint i,j;
	WDT_CONTR = WDT;
	Delay1s();
	//1302��ʼ������ȡMONTH_DATAΪ���µ�month���ݣ�ÿ���趨��ds1302��ʱ����30�죬(�趨month������flash����30���month+1����flash)Ȼ���ʼ��da1302
	initDS1302(0,0,0);
	monthCount = eepromInit();
	while(1)
	{
		//�������Ź�
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