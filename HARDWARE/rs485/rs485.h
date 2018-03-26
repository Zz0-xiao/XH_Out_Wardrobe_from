#ifndef __RS3485_H
#define __RS3485_H

#include "sys.h"

#define FOSC 24000000UL
#define BRT (65536-FOSC/9600/4)

#define RS485EN     P37

extern u8 UART2RevData[16];
extern u16 UART2RXDataLenth;//UART1接受数据长度

void Uart2Init();
void Uart2Send(char dat);
void Uart2SendStr(char *p);
u8 CrcProtocol(u8* pbuff);
void TransmitData_API(const void* dat, u16 datasize);
void TransmitData_SDSES(u8 address , u8  len, u8 cmdr , const void* dat);
#endif





