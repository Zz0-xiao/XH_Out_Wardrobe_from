#include <delay.h>
#include "STC8.H"
#include "sys.h"
#include "rs485.h"
#include "utility.h"
#include "key.h"
#include "timer.h"
#include "motor.h"
#include "process.h"

RS485_StatusTypeDef Protocol_Process(u8* pbuff);
RS485_StatusTypeDef  ResultSend(RS485_StatusTypeDef result);
code u8  RevData[16] = {0x53, 0x44, 0x02, 0x05, 0x73 , 0x00, 0x01, 0x37, 0x1b};

u8 addr, cmdr;
RS485_StatusTypeDef processResult = RS485_INI;
//53 44 02 05 73 00 01 6f 77;
void main()
{
    delay_init();
    Uart2Init();
    TIM3_Initial();
    EA = 1;					//允许全局中断
    Delay_ms(20);
    MotorInit();

    addr = ((P1 & 0x1c) >> 2);//读拨码开关地址

//    CrcProtocol(RevData);
    TransmitData_API("Uart Test !\r\n",0);
    while (1)
    {
        if(RS485Time_1ms >= 10)
        {
            RS485Time_1ms = 1;
            processResult = CrcProtocol(UART2RevData);
            if(processResult == RS485_OK)
            {
                processResult = Protocol_Process(UART2RevData);
            }
            UART2RXDataLenth = 0;
            ResultSend(processResult);
            BuffReset_API(UART2RevData, 16);
        }
    }
}

RS485_StatusTypeDef Protocol_Process(u8* pbuff)
{
    u8 cmdr;

    cmdr = pbuff[4];

    switch(cmdr)
    {
    case DEBUG_SESES:
        processResult = Debug_Process(&pbuff[5]);
        break;
    case OUT_CLOTHING_SDSES:
        processResult = SendOut(&pbuff[5]);
        break;
    default:
        break;
    }
    return processResult;
}

RS485_StatusTypeDef  ResultSend(RS485_StatusTypeDef result)
{
    u8  ResultData[]={0x00,0x00};
    if(result == RS485_OK)
    {
        TransmitData_SDSES(0x00, 0x05, 0x70, ResultData);///////////////
    }
    else  if(result == RS485_NO_GOODS)
        TransmitData_SDSES(0x00, 0x05, 0x71, ResultData);///////////////
    else if(result == RS485_BLOCK)
        TransmitData_SDSES(0x00, 0x05, 0x72, ResultData);///////////////
    else if(result == RS485_CRCERROR)
        TransmitData_API("CRC ERROR", 0);
//				TransmitData_API("CRC ERROR", 0);
//    if(result == RS485_BUSY)
//        TransmitData_API("ERROR BUSY", 0);
    return RS485_OK;
}


//        if(RS485Time_1ms > 10)
//        {
//            RS485Time_1ms = 0;
//            cmdr = UART2RevData[0];
//            switch(cmdr)
//            {
//            case 0x01:
////            Uart2SendStr("111 !\r\n");
////            TransmitData_API(RevData, 0);
//                TransmitData_SDSES(0x03, 0x05, 0x73, aaa);
//                break;
//            case 0x02:
//                CrcProtocol(RevData);
//                break;
//            case 0x03:
//                TransmitData_API("U33 !\r\n", 0);
//                break;
//            case 0x04:
//                Uart2Send(addr);
//                Uart2Send(addr);
//                break;
//            case 0x05:
//                TransmitData_API("555!\r\n", 2);
//                break;
//            default:
//                break;
//            }
//            UART2RXDataLenth = 0;
//            BuffReset_API(UART2RevData, 16);
//        }


