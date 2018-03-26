#include "rs485.h"
#include <STC8.H>
#include "sys.h"
#include "intrins.h"
#include "utility.h"
#include "string.h"

bit busy;
u8 UART2RevData[16];
u16 UART2RXDataLenth = 0;

//<神思协议定义
//<s>协议头
u8 HEAD[] =  "SD";
u8 HEADSIZE = 2;

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
        if(UART2RXDataLenth >= 64)
            UART2RXDataLenth--;
    }
}

void Uart2Init()
{
    P3_Mode_OUT_PP(RS485EN);//485en设置位推挽输出
    P1_Mode_PullUp(key1 | key2 | key3);//拨码开关设为输入

    Res(RS485EN);    //默认位接收模式

	  IE2 |= 0x01;			// 允许串口2中断
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
    while (busy);//这里到时候加入超时
    busy = 1;
    S2BUF = dat;
    _nop_();
    _nop_();
    Res(RS485EN);
}


/*******************************
名称：CrcProtocol(u8* pbuff)
功能：检查协议，并不声明
参数：USART_TypeDef *uart 串口号 u8* pbuff 接收全部数据，不偏移
返回：HAL_StatusTypeDef communication.h
*******************************/
u8 CrcProtocol(u8* pbuff)
{
    u8 lenth;
    u16	crc = 0;

    if((pbuff[0] != 'S') || ( pbuff[1] != 'D'))
        return 0;

    if(pbuff[2] != addr) // 判断是不是当前地址
    {
        TransmitData_API("addrErro !\r\n", 0);//测试用，就看看到时候屏蔽
        return 0;
    }

    lenth =  pbuff[HEADSIZE + 1 ] + 2;////头+2，地址+1，长度+1，校验-2
    crc = crc16_ccitt(pbuff, lenth);
//		Uart2Send(lenth);
//    Uart2Send(crc / 256);
//    Uart2Send(crc % 256);
//    Uart2Send(pbuff[lenth]);
//    Uart2Send(pbuff[lenth + 1]);
//    return 0;
    if((crc / 256 == pbuff[lenth]) && (crc % 256  == pbuff[lenth + 1]))
    {
        TransmitData_API("ok !\r\n", 0);//测试用，就看看到时候屏蔽
        return 1;
    } else
    {
        TransmitData_API("ERRO !\r\n",0);//测试用，就看看到时候屏蔽
        return 0;
    }
}

void TransmitData_API(const void* dat, u16 datasize)
{
    u16 i;
    u8* pdat = (u8*) dat;
    if(datasize == 0)
        datasize = strlen((char*)pdat) ;
    for(i = 0; i <= datasize; i++)
        Uart2Send(pdat[i]);
}

/*******************************
名称：UART_TransmitData_SDSES()
功能：串口发送数据，适用于神思，自动加入SDsEs,crc
参数： *huart串口结构体
			address 地址，
			len只是data长度,函数中自动加2
			cmdr  命令
			data  发送数据,不包含任何协议内容，只是data数据，或数组
返回：HAL_StatusTypeDef communication.h
*******************************/
u8 SendBuff[16];
void TransmitData_SDSES(u8 address , u8  len, u8 cmdr , const void* dat)
{
    u16 crc16 = 0;
    u8 sendLen = 0;
    u8 crc[2];

    u8* pdat = (u8*) dat;

    if(len == 0)
        len = strlen((char*)pdat);
    //头 SDsEs 5
    memcpy(SendBuff, HEAD, HEADSIZE);
    sendLen += HEADSIZE;
    //长度 4字节
    //加入地址
    SendBuff[sendLen] = address;
    sendLen++;
    //加入长度
    SendBuff[sendLen] = len;
    sendLen++;
    //state 1字节
    SendBuff[sendLen] = cmdr;
    sendLen++;
//		memcpy(SendBuff + sendLen, crc, 2);
//    sendLen += 2;
    //加入数据
    memcpy(SendBuff + sendLen, dat, 2);
    sendLen += 2;
    //crc 2字节
    crc16 = crc16_ccitt(SendBuff, sendLen);
    crc[0] = crc16 >> 8;
    crc[1] = crc16 & 0xFF;
    memcpy(SendBuff + sendLen, crc, 2);
    sendLen += 2;
    TransmitData_API(SendBuff, sendLen);
}


//void Uart2SendStr(char *p)
//{
//    while (*p)
//    {
//        Uart2Send(*p++);
//    }
//}



