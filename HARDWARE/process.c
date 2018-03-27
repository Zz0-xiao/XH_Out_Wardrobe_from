#include "process.h"
#include "rs485.h"
#include "motor.h"
#include "delay.h"

RS485_StatusTypeDef Debug_Process(u8* pbuff)
{
    //pbuff[0] 电机 pbuff[1]时间
    RS485_StatusTypeDef result = RS485_INI;

//	uint32_t driveTime = ((pbuff[3]<<8)+pbuff[4])*1000;
//	if(driveTime > 0)
//			timeOutCounter = TIMESTART;

    if((pbuff[0] <= 3) && (pbuff[0] > 0))
    {   //电机驱动这里一块看情况改改，可以直接驱动p口
        MotorDriveDc(START, pbuff[0]);
        Delay_100ms(pbuff[1]);
        MotorDriveDc(STOP, pbuff[0]);
        result = RS485_OK;
    }
//	timeOutCounter = TIMEEND;
//	UART_TransmitData_SDSES(USART1,0,0xA101,OPSUCCESS,"");
    return result;
}

RS485_StatusTypeDef SendOut(u8* pbuff)
{
    RS485_StatusTypeDef processResult = RS485_INI;
//	uint32_t timeout = 50000;//10s

    if((pbuff[0] < 1) || (pbuff[0] > 3))
        return RS485_ERROR;

    processResult = MotorDriveDCs(pbuff[0]);
    return processResult;
}





