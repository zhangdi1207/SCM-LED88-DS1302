#include"head.h"

void judgeSet()
{
	BUTTON=1;
	if(!BUTTON)
}

void rowSet()
{
}

void columnSet()
{
}





void monthSet()
{
	uchar setFlag = 0; //0:没有设置，1：行设置，2：列设置
	setFlag = judgeSet();
	if(setFlag==1)
	{
		rowSet();
	}
	else if(setFlag==2)
	{
		columnSet();
	}
}