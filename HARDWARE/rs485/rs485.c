#include "rs485.h"
#include <STC8.H>
#include "intrins.h"
#include "utility.h"
#include "string.h"
#include "timer.h"

bit busy;    //串口忙
u8 UART2RevData[16];//串口2接收到的数据
u8 UART2RXDataLenth = 0;//串口2接收数据的长度

//<神思协议定义
//<s>协议头
u8 HEAD[] =  "SD";
u8 HEADSIZE = 2;

/*******************************
名称：Uart2Isr()
功能：串口2中断函数
参数：无
返回：无
*******************************/
void Uart2Isr() interrupt 8
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
        if(UART2RXDataLenth >= 16)//这里要=也加上不加上会出错
        {
            UART2RXDataLenth--;
            RS485Time_1ms = 0;//超市停止计时，不过好像还会计时，先放着
        }
        else
            RS485Time_1ms = 1; //每个字节接收都把他复位
    }
}

/*******************************
名称：Uart2Init()
功能：串口2初始化函数，包括拨码开关，485控制脚的I/O设置
参数：无
返回：无
*******************************/
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

/*******************************
名称：Uart2Send()
功能：串口2初始化函数，包括拨码开关，485控制脚的I/O设置
参数：char dat，可以是十六位数
返回：无
*******************************/
void Uart2Send(char dat)
{
    Set(RS485EN);

    while (busy);//这里到时候加入超时 算了，不加了麻烦
    busy = 1;
    _nop_();
    _nop_();
    S2BUF = dat;
    _nop_();
    _nop_();
    Res(RS485EN);
}


/*******************************
名称：CrcProtocol(u8* pbuff)
功能：检查协议，包括地址校验crc校验都在这里，地址的话是把一数据都接收，然后在判断地址
参数：pbuff，为收到串口数据，大部分情况下传这个
返回：RS485_StatusTypeDef 头错误或者crc错误，还有正确
*******************************/
RS485_StatusTypeDef CrcProtocol(u8* pbuff)
{
    u8 lenth;
    u16	crc = 0;

    if((pbuff[0] != 'S') || ( pbuff[1] != 'D'))
        return RS485_HEADERROR;

    if(pbuff[2] != addr) // 判断是不是当前地址
    {
//       TransmitData_API("addrErro !\r\n", 0);//测试用，就看看到时候屏蔽
			Uart2Send(pbuff[2]);
						Uart2Send(pbuff[2]);
        return RS485_INI;  //地址错误返回默认
    }
    lenth =  pbuff[HEADSIZE + 1 ] + 2;////头+2，地址+1，长度+1，校验-2
    crc = crc16_ccitt(pbuff, lenth);
//    Uart2Send(crc / 256);
//    Uart2Send(crc % 256);
//    Uart2Send(pbuff[lenth]);
//    Uart2Send(pbuff[lenth + 1]);
    if((crc / 256 == pbuff[lenth]) && (crc % 256  == pbuff[lenth + 1]))
    {
//        TransmitData_API("ok !", 0);//测试用，就看看到时候屏蔽
        return RS485_OK;
    } else
    {
//        TransmitData_API("ERRO !", 0); //测试用，就看看到时候屏蔽
        return RS485_CRCERROR; //返回crc错误
    }
}
/*******************************
名称：TransmitData_API()
功能：发送字符串，反正我发送这个没有问题，也可以发其他的吧
参数：dat，要发送的东西，
datasize  发送的长度 如果为0着全发送，
返回：无
*******************************/
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
功能：串口发送数据，适用于xiao，自动加入SD,crc
参数： address 地址，
			len只是data长度,
			cmdr  命令
			data  发送数据,协议内容，只是data数据，或数组
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



