#include "motor.h"
#include "delay.h"
#include "timer.h"
void MotorInit()
{
    P3_Mode_OUT_PP(MOROT1 | MOROT2 | MOROT3); //

    Res(MOROT1);
    Res(MOROT2);
    Res(MOROT3);
}


void MotorDriveDc(u8 motor_mode , u8 number )
{
    if(motor_mode == START)
    {
        if(number == 0x01) {
            Set(MOROT1);
        } else if(number == 0x02) {
            Set(MOROT2);
        } else if(number == 0x03) {
            Set(MOROT3);
        } else if(number == 0x04)
        {
            Set(MOROT1);
            Set(MOROT2);
            Set(MOROT3);
        }
    }
    else
    {
        if(number == 0x01) {
            Res(MOROT1);
        } else if(number == 0x02) {
            Res(MOROT2);
        } else if(number == 0x03) {
            Res(MOROT3);
        } else if(number == 0x04)
        {
            Res(MOROT1);
            Res(MOROT2);
            Res(MOROT3);
        }
    }
}


RS485_StatusTypeDef MotorDriveDCs(u8 motorDCNum)
{
    RS485_StatusTypeDef result = RS485_INI;
//	int i = 0;

    if(P36 == 1)//有货退
        return RS485_BLOCK;

    MotorDriveDc(START, motorDCNum);
//    MotorTime_1ms = 1;

    for(MotorTime_1ms = 1; MotorTime_1ms < 5000;)
    {
        if(P36 == 1)//有货
        {
            for(MotorTime_1ms = 1; MotorTime_1ms < 5000;)
            {
//							Uart2Send(MotorTime_1ms);
                if(P36 == 0)
                {
                    Delay_ms(20);///消抖处理
                    if(P36 == 0)
                    {
                        MotorDriveDc(STOP, motorDCNum);
                        MotorTime_1ms = 0;
                        return RS485_OK;
                    }
                }
            }
            MotorDriveDc(STOP, motorDCNum);
            return RS485_BLOCK;   //说明卡货
        }
    }
    MotorDriveDc(STOP, motorDCNum);
    return  RS485_NO_GOODS;   //说明无货
}



