#include "delay.h"
#include <STC8.H>
#include "intrins.h"

void delay_init()
{
    P_SW2 = 0x80;
    CKSEL = 0x00;                               //选择内部IRC ( 默认 )
    P_SW2 = 0x00;
    /*
    P_SW2 = 0x80;
    XOSCCR = 0xc0;                              //启动外部晶振
    while (!(XOSCCR & 1));                      //等待时钟稳定
    CKDIV = 0x00;                               //时钟不分频
    CKSEL = 0x01;                               //选择外部晶振
    P_SW2 = 0x00;
    */
    /*
    P_SW2 = 0x80;
    IRC32KCR = 0x80;                            //启动内部32K IRC
    while (!(IRC32KCR & 1));                    //等待时钟稳定
    CKDIV = 0x00;                               //时钟不分频
    CKSEL = 0x03;                               //选择内部32K
    P_SW2 = 0x00;
    */
}

/***********************************************
函数名称：Delay_10us
功    能：STC8单片机10us延时程序
入口参数：us:延时的微秒数，十的倍数
返 回 值：无
备    注：示波器实测11.2us，内部时钟：24MHz
************************************************/
//void Delay_10us(unsigned int us)
//{
//	unsigned char i;
//  while( us--)
//  {
//		i = 40;
//		while (--i);
//  }
//}
/***********************************************
函数名称：Delay_ms
功    能：STC8系列单片机1ms延时程序
入口参数：ms:延时的毫秒数
返 回 值：无
备    注：示波器实测：1.01ms，内部时钟：24MHz
************************************************/
void Delay_ms(unsigned int ms)
{
    unsigned int i;
    while( (ms--) != 0)
    {
        for(i = 0; i < 1850; i++);
    }
}


void Delay_100ms(unsigned int ms)		//@24.000MHz
{
    unsigned char i, j, k;
    while((ms--) != 0)
    {
        _nop_();
        _nop_();
        i = 13;
        j = 45;
        k = 214;
        do
        {
            do
            {
                while (--k);
            } while (--j);
        } while (--i);
    }
}


