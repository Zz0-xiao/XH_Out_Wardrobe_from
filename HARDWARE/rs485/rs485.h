#ifndef __RS485_H__
#define __RS485_H__

#include "sys.h"

#define FOSC 24000000UL
#define BRT (65536-FOSC/9600/4)

#define RS485EN     P37

#define key1   P12
#define key2   P13
#define key3   P14


extern u8 UART2RevData[16];
extern u16 UART2RXDataLenth;//UART1接受数据长度

extern u8 addr;//UART1接受数据长度

void Uart2Init();
void Uart2Send(char dat);
void Uart2SendStr(char *p);
u8 CrcProtocol(u8* pbuff);
void TransmitData_API(const void* dat, u16 datasize);
void TransmitData_SDSES(u8 address , u8  len, u8 cmdr , const void* dat);
#endif





