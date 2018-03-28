#include "process.h"
#include "rs485.h"
#include "motor.h"
#include "delay.h"
/*******************************
名称：Debug_Process()
功能：收到DEBUG_SESES 是的处理函数即调试函数
参数：pbuff  数组，基本上从第5位开始
返回：result   流程处理的结果
*******************************/
RS485_StatusTypeDef Debug_Process(u8* pbuff)
{
    //pbuff[0] 电机 pbuff[1]时间
    RS485_StatusTypeDef result = RS485_INI;
    //调试的流程没有加入电机超时
    if((pbuff[0] <= 4) && (pbuff[0] > 0))
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

/*******************************
名称：SendOut()
功能：OUT_CLOTHING_SDSES 是的处理函数即出货的函数
参数：pbuff  数组，基本上从第5位开始
返回：result   流程处理的结果
*******************************/

RS485_StatusTypeDef SendOut(u8* pbuff)
{
    RS485_StatusTypeDef result = RS485_INI;
//	uint32_t timeout = 50000;//10s

    if((pbuff[0] < 1) || (pbuff[0] > 3))
        return RS485_ERROR;

    result = MotorDriveDCs(pbuff[0]);

    return result;
}





