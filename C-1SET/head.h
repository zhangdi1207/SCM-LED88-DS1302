#ifndef _HEAD_H_
#define _HEAD_H_
#include <reg52.h>
#include <intrins.h>
#define nop() _nop_()
#define uchar unsigned char
#define uint unsigned int
#define ul unsigned long
#define CMD_IDLE    0               //空闲模式
#define CMD_READ    1               //IAP字节读命令
#define CMD_PROGRAM 2               //IAP字节编程命令
#define CMD_ERASE   3  
#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
#define MONTH_DATA 0x0000
#define WDT			0x35			//看门狗初始化@12MHz，2.9071s
//DS1302寄存器定义
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


//初始化年月日等时间值
#define OR_YEA 00
#define OR_MON 01
#define OR_DAT 01
#define OR_HOU 00
#define OR_MIN 00
#define OR_SEC 00

#define SHOWPRA 100 //显示多少次统计一下时间


sfr AUXR        =   0x8e;
sfr IAP_DATA    =   0xC2;           //IAP数据寄存器
sfr IAP_ADDRH   =   0xC3;           //IAP地址寄存器高字节
sfr IAP_ADDRL   =   0xC4;           //IAP地址寄存器低字节
sfr IAP_CMD     =   0xC5;           //IAP命令寄存器
sfr IAP_TRIG    =   0xC6;           //IAP命令触发寄存器
sfr IAP_CONTR   =   0xC7;           //IAP控制寄存器
sfr CLK_DIV = 0x97;					//时钟命令寄存器
sfr WDT_CONTR = 0xc1;

//行列数据74HC595
sbit SHCP = P3^1;
sbit STCP = P3^2;
sbit ROWD = P3^3;
sbit COLD = P3^4;



//DS1302数据线
sbit DS1302RST = P1^0;
sbit DS1302CLK = P1^1;
sbit DS1302IO = P1^2;

//所需函数
void Delay40us();
void Delay1s();
uint eepromInit();
uint calMonth(uint calmo);
void initDS1302(uchar sec,uchar min,uchar hou);
void flashMonthChange(uint fmonth);
void show(uint signalMonth);


//所需数据


#endif