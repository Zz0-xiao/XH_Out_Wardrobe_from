#ifndef __SYS_H__
#define __SYS_H__

#include <STC8.H>

#define  u8   unsigned char	  //0-255
#define  u16  unsigned  int 	//0-65536
#define  u32  unsigned long   //0-4294967295


#define Set(n)    n=1;
#define Res(n)    n=0;//输出低电平 
//
//typedef unsigned          char u8;	  //0-255
//typedef unsigned short     int u16;	//0-65536
//typedef unsigned           long u32;  //0-4294967295



//  reg |= (x)  即对reg执行按位取或
//  例如x=0x01， 0x01等价于二进制(0000 0001)，即第0位为1
//  reg |=0x01，也就是将reg中的第0位置为1，不改变其他位的值
//  例如x=0x13， 0x13等价于二进制(0001 0011)，即第0、1和4位为1，
//  reg |=0x13，也就是将reg中的第0、1和4位置为1，不改变其他位的值

//  reg &=~(x)  即将x按位取反，然后对reg按位取与
//  例如x=0x01， ~x=0xfe，0xfe等价于二进制(1111 1110)，即第0位为0
//  reg &=0xfe，也就是将reg中的第0位置为0，不改变其他位的值
//  例如x=0x13， ~x=0xec，0xec等价于二进制(1110 1100)，即第0、1和4位为0，
//  reg &=0xec，也就是将reg中的第0、1和4位置为0，不改变其他位的值

//端口位
#define   PIN_7			0x80		//第7位
#define   PIN_6			0x40		//第6位
#define   PIN_5			0x20		//第5位
#define   PIN_4			0x10		//第4位
#define   PIN_3			0x08		//第3位
#define   PIN_2			0x04		//第2位
#define   PIN_1			0x02		//第1位
#define   PIN_0			0x01		//第0位
#define   PIN_ALL		0xff		//所有位

//端口模式设定
#define   P0_Mode_PullUp(x)		(P0M1 &=~(x));(P0M0 &=~(x))	//将P00~P07设置为上拉准双向口
#define		P0_Mode_OUT_PP(x)		(P0M1 &=~(x));(P0M0 |= (x))	//将P00~P07设置为推挽输出
#define 	P0_Mode_HighZ(x)		(P0M1 |= (x));(P0M0 &=~(x))	//将P00~P07设置为高阻输入
#define 	P0_Mode_OUT_OD(x)		(P0M1 |= (x));(P0M0 |= (x))	//将P00~P07设置为开漏输出

#define   P1_Mode_PullUp(x)		(P1M1 &=~(x));(P1M0 &=~(x))	//将P10~P17设置为上拉准双向口
#define		P1_Mode_OUT_PP(x)		(P1M1 &=~(x));(P1M0 |= (x))	//将P10~P17设置为推挽输出
#define 	P1_Mode_HighZ(x)		(P1M1 |= (x));(P1M0 &=~(x))	//将P10~P17设置为高阻输入
#define 	P1_Mode_OUT_OD(x)		(P1M1 |= (x));(P1M0 |= (x))	//将P10~P17设置为开漏输出

#define   P2_Mode_PullUp(x)		(P2M1 &=~(x));(P2M0 &=~(x))	//将P20~P27设置为上拉准双向口
#define		P2_Mode_OUT_PP(x)		(P2M1 &=~(x));(P2M0 |= (x))	//将P20~P27设置为推挽输出
#define 	P2_Mode_HighZ(x)		(P2M1 |= (x));(P2M0 &=~(x))	//将P20~P27设置为高阻输入
#define 	P2_Mode_OUT_OD(x)		(P2M1 |= (x));(P2M0 |= (x))	//将P20~P27设置为开漏输出

#define   P3_Mode_PullUp(x)		(P3M1 &=~(x));(P3M0 &=~(x))	//将P30~P37设置为上拉准双向口
#define		P3_Mode_OUT_PP(x)		(P3M1 &=~(x));(P3M0 |= (x))	//将P30~P37设置为推挽输出
#define 	P3_Mode_HighZ(x)		(P3M1 |= (x));(P3M0 &=~(x))	//将P30~P37设置为高阻输入
#define 	P3_Mode_OUT_OD(x)		(P3M1 |= (x));(P3M0 |= (x))	//将P30~P37设置为开漏输出

#define   P4_Mode_PullUp(x)		(P4M1 &=~(x));(P4M0 &=~(x))	//将P40~P47设置为上拉准双向口
#define		P4_Mode_OUT_PP(x)		(P4M1 &=~(x));(P4M0 |= (x))	//将P40~P47设置为推挽输出
#define 	P4_Mode_HighZ(x)		(P4M1 |= (x));(P4M0 &=~(x))	//将P40~P47设置为高阻输入
#define 	P4_Mode_OUT_OD(x)		(P4M1 |= (x));(P4M0 |= (x))	//将P40~P47设置为开漏输出

#define   P5_Mode_PullUp(x)		(P5M1 &=~(x));(P5M0 &=~(x))	//将P50~P57设置为上拉准双向口
#define		P5_Mode_OUT_PP(x)		(P5M1 &=~(x));(P5M0 |= (x))	//将P50~P57设置为推挽输出
#define 	P5_Mode_HighZ(x)		(P5M1 |= (x));(P5M0 &=~(x))	//将P50~P57设置为高阻输入
#define 	P5_Mode_OUT_OD(x)		(P5M1 |= (x));(P5M0 |= (x))	//将P50~P57设置为开漏输出

#define   P6_Mode_PullUp(x)		(P6M1 &=~(x));(P6M0 &=~(x))	//将P60~P67设置为上拉准双向口
#define		P6_Mode_OUT_PP(x)		(P6M1 &=~(x));(P6M0 |= (x))	//将P60~P67设置为推挽输出
#define 	P6_Mode_HighZ(x)		(P6M1 |= (x));(P6M0 &=~(x))	//将P60~P67设置为高阻输入
#define 	P6_Mode_OUT_OD(x)		(P6M1 |= (x));(P6M0 |= (x))	//将P60~P67设置为开漏输出

#define   P7_Mode_PullUp(x)		(P7M1 &=~(x));(P7M0 &=~(x))	//将P70~P77设置为上拉准双向口
#define		P7_Mode_OUT_PP(x)		(P7M1 &=~(x));(P7M0 |= (x))	//将P70~P77设置为推挽输出
#define 	P7_Mode_HighZ(x)		(P7M1 |= (x));(P7M0 &=~(x))	//将P70~P77设置为高阻输入
#define 	P7_Mode_OUT_OD(x)		(P7M1 |= (x));(P7M0 |= (x))	//将P70~P77设置为开漏输出

#endif
