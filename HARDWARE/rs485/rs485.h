#ifndef __RS485_H__
#define __RS485_H__

#include "sys.h"

#define FOSC 24000000UL     //系统时钟
#define BRT (65536-FOSC/9600/4)//波特率设置

#define RS485EN     P37    //485发送接收控制脚
//拨码开关*3
#define key1   P12
#define key2   P13
#define key3   P14

#define DEBUG_SESES        0x60   //调试用
#define OUT_CLOTHING_SDSES  0x61    //出货电机控制i

typedef enum
{
    RS485_INI = 0,
    RS485_OK,
    RS485_ERROR,

    RS485_UART2TIMEOUT,

    RS485_NULL,
    RS485_HEADERROR,//头错误
    RS485_CRCERROR,

    RS485_BLOCK,//卡货
    RS485_NO_GOODS,//无货

} RS485_StatusTypeDef;

extern u8 UART2RevData[16];
extern u8 UART2RXDataLenth;//UART1接受数据长度
extern u8 addr;//UART1接受数据长度

void Uart2Init();
void Uart2Send(char dat);
//void Uart2SendStr(char *p);
RS485_StatusTypeDef CrcProtocol(u8* pbuff);
void TransmitData_API(const void* dat, u16 datasize);
void TransmitData_SDSES(u8 address , u8  len, u8 cmdr , const void* dat);
#endif





