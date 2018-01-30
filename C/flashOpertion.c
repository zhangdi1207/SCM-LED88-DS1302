#include"head.h"


void IapIdle()
{
	IAP_CONTR = 0;         //ʹ��IAP
    IAP_CMD = 0; 
	IAP_TRIG = 0;            //����IAP����
    IAP_ADDRH = 0x80;          //����IAP�ߵ�ַ
	IAP_ADDRL = 0;               //����IAP�͵�ַ
}


uchar IapReadByte(uint addr)
{
    uchar dat;                       //���ݻ�����
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_READ;             //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    Delay40us();                        //�ȴ�ISP/IAP/EEPROM�������
    dat = IAP_DATA;                 //��ISP/IAP/EEPROM����
    IapIdle();                                            /*�������к�EEPROM������Ч*/
    return dat;                     //����
}
/*----------------------------
дһ�ֽ����ݵ�ISP/IAP/EEPROM����
addr:Ҫд��ĵ�ַ
dat:Ҫд�������
----------------------------*/
void IapProgramByte(uint addr,uchar dat)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_PROGRAM;          //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_DATA = dat;                 //дISP/IAP/EEPROM����
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    Delay40us();                        //�ȴ�ISP/IAP/EEPROM�������

    IapIdle();                                            /*�������к�EEPROM������Ч*/
}
/*----------------------------
�������� ĳһ��ַaddr������
----------------------------*/
void IapEraseSector(uint addr)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_ERASE;            //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    Delay40us();                        //�ȴ�ISP/IAP/EEPROM�������
                                                                
    IapIdle();                                        /*�������к�EEPROM������Ч*/
}

uint eepromInit()
{
	uint month;
	uchar mH,mL;
	mH = IapReadByte(MONTH_DATA+1);
	mL = IapReadByte(MONTH_DATA);
	month = mH * 256 + mL;
	if(month>1023)
	{
		month=1;
		IapEraseSector(MONTH_DATA);
		IapProgramByte(MONTH_DATA+1,0);
		IapProgramByte(MONTH_DATA,1);
	}

	return month;
}

void flashMonthChange(uint month)
{
	uchar mH,mL;
	mH = month/256;
	mL = month%256;
	IapEraseSector(MONTH_DATA);
	IapProgramByte(MONTH_DATA+1,mH);
	IapProgramByte(MONTH_DATA,mL);
}

