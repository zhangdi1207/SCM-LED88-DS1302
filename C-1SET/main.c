#include"head.h"

void main()
{
	ul showCount = 0;
	uint monthCount = 1;
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
			P2=read1302(READ_SEC);
		}
		//monthCount=35;
		show(monthCount);
		
	}
}