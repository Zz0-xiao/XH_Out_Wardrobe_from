#include "rs485.h"
#include <STC8.H>
#include "sys.h"
#include "intrins.h"
#include "utility.h"
bit busy;
u8 UART2RevData[64];
u16 UART2RXDataLenth = 0;

//<神思协议定义
//<s>协议头
u8 HEAD[] =  "SDsEs";
u8 HEADSIZE = sizeof(HEAD) / sizeof(u8) - 1;

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

/*******************************
名称：CrcProtocol(uint8_t* pbuff)
功能：检查协议，并不声明
参数：USART_TypeDef *uart 串口号 uint8_t* pbuff 接收全部数据，不偏移
返回：HAL_StatusTypeDef communication.h
*******************************/
u8 CrcProtocol(u8* pbuff)
{
    u8 i;
    u16 lenth;
    u16	crc = 0;

//    u8  crc_out_h, crc_out_l;
//    u8  crch, crcl;
    for(i = 0; i < HEADSIZE; i++)
    {
        if(pbuff[i] != HEAD[i])
            return 0;
    }
    lenth = (pbuff[HEADSIZE] << 24) + (pbuff[HEADSIZE + 1] << 16) + (pbuff[HEADSIZE + 2] << 8) +  pbuff[HEADSIZE + 3] + 7 ; //5+4-2 5位头，4位len，2位校验
    crc = crc16_ccitt(pbuff, lenth);

    if((crc / 256 == pbuff[lenth]) && (crc % 256  == pbuff[lenth + 1]))
    {
//        Uart2SendStr("ok!\r\n");
        return 1;
    } else
    {
//        Uart2SendStr("erro!\r\n");
        return 0;
    }
}
