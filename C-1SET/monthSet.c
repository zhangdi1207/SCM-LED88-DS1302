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
	uchar setFlag = 0; //0:û�����ã�1�������ã�2��������
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