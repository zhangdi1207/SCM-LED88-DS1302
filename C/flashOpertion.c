#include"head.h"


void IapIdle()
{
	IAP_CONTR = 0;         //使能IAP
    IAP_CMD = 0; 
	IAP_TRIG = 0;            //设置IAP命令
    IAP_ADDRH = 0x80;          //设置IAP高地址
	IAP_ADDRL = 0;               //设置IAP低地址
}


uchar IapReadByte(uint addr)
{
    uchar dat;                       //数据缓冲区
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_READ;             //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    Delay40us();                        //等待ISP/IAP/EEPROM操作完成
    dat = IAP_DATA;                 //读ISP/IAP/EEPROM数据
    IapIdle();                                            /*加上这行后EEPROM操作无效*/
    return dat;                     //返回
}
/*----------------------------
写一字节数据到ISP/IAP/EEPROM区域
addr:要写入的地址
dat:要写入的数据
----------------------------*/
void IapProgramByte(uint addr,uchar dat)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_PROGRAM;          //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_DATA = dat;                 //写ISP/IAP/EEPROM数据
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    Delay40us();                        //等待ISP/IAP/EEPROM操作完成

    IapIdle();                                            /*加上这行后EEPROM操作无效*/
}
/*----------------------------
扇区擦除 某一地址addr的数据
----------------------------*/
void IapEraseSector(uint addr)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_ERASE;            //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    Delay40us();                        //等待ISP/IAP/EEPROM操作完成
                                                                
    IapIdle();                                        /*加上这行后EEPROM操作无效*/
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

