#include"head.h"

/**************************************
—” ±XŒ¢√Î(STC15F104W@11.0592M)
**************************************/


 /*
void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}

		 */
void Delay40us()		//@11.0592MHz
{
	unsigned char i;
	WDT_CONTR = WDT;
	i = 108;
	while (--i);
}

void Delay10ms()
{
	uchar i=250;
	while(i--)
	{
		Delay40us();
	}
}


void Delay1s()		//@11.0592MHz
{
	unsigned char i, j, k;
	WDT_CONTR = WDT;
	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}