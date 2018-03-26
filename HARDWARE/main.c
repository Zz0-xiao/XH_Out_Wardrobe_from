#include <delay.h>
#include "STC8.H"
#include "sys.h"
#include "rs485.h"

void main()
{
    u8 cmdr;
  
    delay_init();
    Uart2Init();
    IE2 = 0x01;
    EA = 1;
    Delay_ms(200);
    Uart2SendStr("Uart Test !\r\n");

    while (1)
    {
        cmdr = UART2RevData[0];

        switch(cmdr)
        {
        case 0x01:
            Uart2SendStr("111 !\r\n");
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
//            BuffReset_API(UART2RevData, MAXCOMSIZE);
        UART2RevData[0] = 0;
        Delay_ms(10);
    }
}


