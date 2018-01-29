#include"head.h"

void main()
{
	uint showCount = 0;
	uint monthCount = 0;
	uint i;
	WDT_CONTR = WDT;
	eepromInit();
	while(1)
	{
		WDT_CONTR = WDT;
		monthCount = calMonth();
		for(showCount=0;showCount<3600;showCount++)
		{
			for(i=0;i<monthCount;i++)
				show(i);
		}
	}
}