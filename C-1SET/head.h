#ifndef _HEAD_H_
#define _HEAD_H_
#include <reg52.h>
#include <intrins.h>
#define nop() _nop_()
#define uchar unsigned char
#define uint unsigned int
#define ul unsigned long
#define CMD_IDLE    0               //����ģʽ
#define CMD_READ    1               //IAP�ֽڶ�����
#define CMD_PROGRAM 2               //IAP�ֽڱ������
#define CMD_ERASE   3  
#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
#define MONTH_DATA 0x0000
#define WDT			0x35			//���Ź���ʼ��@12MHz��2.9071s
//DS1302�Ĵ�������
#define WRITE_SEC	 0X80
#define WRITE_MIN	 0X82
#define WRITE_HOU	 0X84
#define WRITE_DAT	 0X86
#define WRITE_MON	 0X88
#define WRITE_YEA	 0X8C

#define READ_SEC	 0x81
#define READ_MIN	 0x83
#define READ_HOU	 0x85
#define READ_DAT	 0x87
#define WRITE_PROTECT 0X8E


//��ʼ�������յ�ʱ��ֵ
#define OR_YEA 00
#define OR_MON 01
#define OR_DAT 01
#define OR_HOU 00
#define OR_MIN 00
#define OR_SEC 00

#define SHOWPRA 100 //��ʾ���ٴ�ͳ��һ��ʱ��


sfr AUXR        =   0x8e;
sfr IAP_DATA    =   0xC2;           //IAP���ݼĴ���
sfr IAP_ADDRH   =   0xC3;           //IAP��ַ�Ĵ������ֽ�
sfr IAP_ADDRL   =   0xC4;           //IAP��ַ�Ĵ������ֽ�
sfr IAP_CMD     =   0xC5;           //IAP����Ĵ���
sfr IAP_TRIG    =   0xC6;           //IAP������Ĵ���
sfr IAP_CONTR   =   0xC7;           //IAP���ƼĴ���
sfr CLK_DIV = 0x97;					//ʱ������Ĵ���
sfr WDT_CONTR = 0xc1;

//��������74HC595
sbit SHCP = P3^1;
sbit STCP = P3^2;
sbit ROWD = P3^3;
sbit COLD = P3^4;



//DS1302������
sbit DS1302RST = P1^0;
sbit DS1302CLK = P1^1;
sbit DS1302IO = P1^2;

//���躯��
void Delay40us();
void Delay1s();
uint eepromInit();
uint calMonth(uint calmo);
void initDS1302(uchar sec,uchar min,uchar hou);
void flashMonthChange(uint fmonth);
void show(uint signalMonth);


//��������


#endif