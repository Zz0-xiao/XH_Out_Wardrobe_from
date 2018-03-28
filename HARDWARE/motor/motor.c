#include "motor.h"
#include "delay.h"
#include "timer.h"

/*******************************
名称：MotorInit()
功能：电机管脚初始化，包括设置为0
参数：无
返回：无
*******************************/
void MotorInit()
{
    P3_Mode_OUT_PP(MOROT1 | MOROT2 | MOROT3); //

    Res(MOROT1);
    Res(MOROT2);
    Res(MOROT3);
}

/*******************************
名称：MotorDriveDc()
功能：控制电机
参数：motor_mode 电机模式start为启动(为0x01)，其他为停止
number  番外为0x00-0x04，共三个电机，0x04为全部控制
返回：无
*******************************/
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

/*******************************
名称：MotorDriveDCs()
功能：发货控制电机用，感应到传感器就停止或者超时
参数：motorDCNum  电机序号
返回：RS485_StatusTypeDef
*******************************/

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



