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
//	int i = 0, delay =500;
//	motorDCNum--;
//	GPIO_WriteBit(MOTOR[motorDCNum].GPIOx,MOTOR[motorDCNum].GPIO_Pin,Bit_SET);
    if(P36 == 1)//有货退
        return RS485_BLOCK;

    MotorDriveDc(START, motorDCNum);
//超时再说
    while(1)
    {
        MotorTime_1ms++;
        if(MotorTime_1ms > 20000)
            return RS485_NO_GOODS;   //说明无货
        if(P36 == 1)//有货
        {
            Delay_100ms(1);
            MotorTime_1ms = 0;
            while(1)
            {
                MotorTime_1ms++;
                if(MotorTime_1ms > 20000)
                    return RS485_BLOCK;   //说明卡货
                if(P36 == 0)
                {
                    MotorDriveDc(STOP, motorDCNum);
                    MotorTime_1ms = 1;
                    return RS485_OK;
                }
            }
        }
    }
}



