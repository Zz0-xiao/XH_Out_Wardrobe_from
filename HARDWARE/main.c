#include <delay.h>
#include "STC8.H"
#include "sys.h"
#include "rs485.h"
#include "utility.h"
#include "key.h"

code u8  RevData[16] = {0x53, 0x44, 0x03, 0x05, 0x73 , 0x00, 0x01, 0x9D, 0x4A};
code u8 aaa[2] = {0x03, 0x20};
//53 44 03 05 73 12 01 6f 77;
void main()
{
    u8 cmdr;

    delay_init();
    Uart2Init();
    IE2 = 0x01;			//允许中断
    EA = 1;					//允许全局中断

    Delay_ms(200);

//    Uart2SendStr("Uart Test !\r\n");
    CrcProtocol(RevData);

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

//            TransmitData_API("444 !\r\n", 3);
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



