#include <delay.h>
#include "STC8.H"
#include "sys.h"
#include "rs485.h"
#include "utility.h"

//code u8 RevData[64] = {0x53, 0x44, 0x73, 0x45, 0x73, 0x00, 0x00, 0x00, 0x09, 0x20,0x02, 0xff, 0xff, 0x04, 0x00, 0x0a, 0x40, 0xf8};

void main()
{
    u8 cmdr;

    delay_init();
    Uart2Init();
    IE2 = 0x01;
    EA = 1;
    Delay_ms(200);
//    Uart2SendStr("Uart Test !\r\n");

//	oo = crc4(UART2RevData, HEADSIZE+UART2RevData[HEADSIZE+3]+4-2);

    while (1)
    {
        cmdr = UART2RevData[0];

        switch(cmdr)
        {
        case 0x01:
//            Uart2SendStr("111 !\r\n");
           
            break;
        case 0x02:
            Uart2SendStr("22!\r\n");
            break;
        case 0x03:
            Uart2SendStr("U33 !\r\n");
            break;
        case 0x04:
            Uart2SendStr("444 !\r\n");
            break;
        case 0x05:
            Uart2SendStr("555!\r\n");
            break;
        default:
            break;
        }
        UART2RXDataLenth = 0;
        BuffReset_API(UART2RevData, 64);

        Delay_ms(10);
    }
}



