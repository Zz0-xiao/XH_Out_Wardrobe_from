#include "rs485.h"
#include <STC8.H>
#include "sys.h"
#include "intrins.h"

bit busy;
u8 UART2RevData[64];
u16 UART2RXDataLenth=0;

void Uart2Isr() interrupt 8 using 1
{
    if (S2CON & 0x02)
    {
        S2CON &= ~0x02;
        busy = 0;
    }
    if(S2CON & 0x01)
    {
        S2CON &= ~0x01;
        UART2RevData[UART2RXDataLenth++] = S2BUF;
        if(UART2RXDataLenth > 15)
            UART2RXDataLenth = 15;
    }
}

void Uart2Init()
{
    P3_Mode_OUT_PP(RS485EN);
    Res(RS485EN);

    S2CON = 0x50;
    T2L = BRT;
    T2H = BRT >> 8;
    AUXR = 0x14;
    busy = 0;
}

void Uart2Send(char dat)
{
    Set(RS485EN);
    _nop_();
    _nop_();
    while (busy);
    busy = 1;
    S2BUF = dat;
    _nop_();
    _nop_();
    Res(RS485EN);
}

void Uart2SendStr(char *p)
{
    while (*p)
    {
        Uart2Send(*p++);
    }
}