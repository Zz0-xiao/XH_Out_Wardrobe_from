#include <STC8.H>
#include "timer.h"

u16 RS485Time_1ms = 1;
u16 MotorTime_1ms = 0;
void TM3_Isr() interrupt 19 
{
   if(RS485Time_1ms > 0)
        RS485Time_1ms++;
    if(MotorTime_1ms > 0)
        MotorTime_1ms++;
    //测试端口
//    P15 = !P15;
    AUXINTIF &= ~0x02;                          //清中断标志
}

void TIM3_Initial()     //1毫秒@24.000MHz
{
    T4T3M &= 0xFD;		//定时器时钟12T模式
    T3L = 0x30;		//设置定时初值
    T3H = 0xF8;		//设置定时初值
    T4T3M |= 0x08;		//定时器3开始计时

//    T4T3M &= 0xFD;		//定时器时钟12T模式
//    T3L = 0xE0;		//设置定时初值
//    T3H = 0xB1;		//设置定时初值
    T4T3M |= 0x08;		//定时器3开始计时
    IE2 |= ET3;                                  //使能定时器中断
    EA = 1;
}

