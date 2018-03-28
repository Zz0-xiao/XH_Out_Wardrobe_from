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
//code u8  RevData[16] = {0x53, 0x44, 0x02, 0x05, 0x73 , 0x00, 0x01, 0x37, 0x1b};

u8 addr;
RS485_StatusTypeDef processResult = RS485_INI;


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
    TransmitData_API("Uart Test !\r\n", 0);
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

/*******************************
名称：Protocol_Process()
功能：信息处理
参数：pbuff 数组。即由串口收到的数据
返回：RS485_StatusTypeDef
*******************************/
RS485_StatusTypeDef Protocol_Process(u8* pbuff)
{
    u8 cmdr;
    cmdr = pbuff[4];

    switch(cmdr)
    {
    case DEBUG_SESES: //调试用
        processResult = Debug_Process(&pbuff[5]);
        break;
    case OUT_CLOTHING_SDSES: //出货电机控制i
        processResult = SendOut(&pbuff[5]);
        break;
    default:
        break;
    }
    return processResult;
}
/*******************************
名称：ResultSend()
功能：数据上传到主板，有些数据没有上传，如串口超时
参数：result  为RS485_StatusTypeDef类型，过程处理完后的一个返回值，地址错误不传回
返回：RS485_StatusTypeDef
*******************************/
RS485_StatusTypeDef  ResultSend(RS485_StatusTypeDef result)
{
    u8  ResultData[] = {0x00, 0x00};
    if(result == RS485_OK)
    {
        TransmitData_SDSES(0x00, 0x05, 0x70, ResultData);//正常
    }
    else  if(result == RS485_NO_GOODS)
        TransmitData_SDSES(0x00, 0x05, 0x71, ResultData);//无货
    else if(result == RS485_BLOCK)
        TransmitData_SDSES(0x00, 0x05, 0x72, ResultData);//卡货
    else if(result == RS485_CRCERROR)
        TransmitData_API("CRC ERROR", 0);///crc校验错误
//				TransmitData_API("CRC ERROR", 0);
//    if(result == RS485_BUSY)
//        TransmitData_API("ERROR BUSY", 0);
    return RS485_OK;
}
