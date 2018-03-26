#include <delay.h>
#include "STC8.H"
#include "sys.h"
#include "rs485.h"
#include "utility.h"
#include "key.h"
#include "timer.h"

code u8  RevData[16] = {0x53, 0x44, 0x02, 0x05, 0x73 , 0x00, 0x01, 0x37, 0x1b};
code u8 aaa[2] = {0x03, 0x20};
u8 addr;
//53 44 02 05 73 00 01 6f 77;
void main()
{
    u8 cmdr;

    delay_init();
    Uart2Init();
    TIM3_Initial();

    EA = 1;					//允许全局中断

    Delay_ms(20);
//    Uart2SendStr("Uart Test !\r\n");
    CrcProtocol(RevData);
    addr = ((P1 & 0x1c) >> 2);

    while (1)
    {
        cmdr = UART2RevData[0];
        switch(cmdr)
        {
        case 0x01:
//            Uart2SendStr("111 !\r\n");
//            TransmitData_API(RevData, 0);
            TransmitData_SDSES(0x03, 0x05, 0x73, aaa);
            break;
        case 0x02:
            CrcProtocol(RevData);
            break;
        case 0x03:
            TransmitData_API("U33 !\r\n", 0);
            break;
        case 0x04:
            Uart2Send(addr);
            Uart2Send(addr);
            break;
        case 0x05:
            TransmitData_API("555!\r\n", 2);
            break;
        default:
            break;
        }
        UART2RXDataLenth = 0;
        BuffReset_API(UART2RevData, 16);
        Delay_ms(10);
    }
}



