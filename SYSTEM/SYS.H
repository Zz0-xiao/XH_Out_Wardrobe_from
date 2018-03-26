#include <STC8.H>

#define  u8   unsigned char	  //0-255
#define  u16  unsigned  int 	//0-65536
#define  u32  unsigned long   //0-4294967295


#define Set(n)    n=1;
#define Res(n)    n=0;//����͵�ƽ 
//
//typedef unsigned          char u8;	  //0-255
//typedef unsigned short     int u16;	//0-65536
//typedef unsigned           long u32;  //0-4294967295



//  reg |= (x)  ����regִ�а�λȡ��
//  ����x=0x01�� 0x01�ȼ��ڶ�����(0000 0001)������0λΪ1
//  reg |=0x01��Ҳ���ǽ�reg�еĵ�0λ��Ϊ1�����ı�����λ��ֵ
//  ����x=0x13�� 0x13�ȼ��ڶ�����(0001 0011)������0��1��4λΪ1��
//  reg |=0x13��Ҳ���ǽ�reg�еĵ�0��1��4λ��Ϊ1�����ı�����λ��ֵ

//  reg &=~(x)  ����x��λȡ����Ȼ���reg��λȡ��
//  ����x=0x01�� ~x=0xfe��0xfe�ȼ��ڶ�����(1111 1110)������0λΪ0
//  reg &=0xfe��Ҳ���ǽ�reg�еĵ�0λ��Ϊ0�����ı�����λ��ֵ
//  ����x=0x13�� ~x=0xec��0xec�ȼ��ڶ�����(1110 1100)������0��1��4λΪ0��
//  reg &=0xec��Ҳ���ǽ�reg�еĵ�0��1��4λ��Ϊ0�����ı�����λ��ֵ

//�˿�λ
#define   PIN_7			0x80		//��7λ
#define   PIN_6			0x40		//��6λ
#define   PIN_5			0x20		//��5λ
#define   PIN_4			0x10		//��4λ
#define   PIN_3			0x08		//��3λ
#define   PIN_2			0x04		//��2λ
#define   PIN_1			0x02		//��1λ
#define   PIN_0			0x01		//��0λ
#define   PIN_ALL		0xff		//����λ

//�˿�ģʽ�趨
#define   P0_Mode_PullUp(x)		(P0M1 &=~(x));(P0M0 &=~(x))	//��P00~P07����Ϊ����׼˫���
#define		P0_Mode_OUT_PP(x)		(P0M1 &=~(x));(P0M0 |= (x))	//��P00~P07����Ϊ�������
#define 	P0_Mode_HighZ(x)		(P0M1 |= (x));(P0M0 &=~(x))	//��P00~P07����Ϊ��������
#define 	P0_Mode_OUT_OD(x)		(P0M1 |= (x));(P0M0 |= (x))	//��P00~P07����Ϊ��©���

#define   P1_Mode_PullUp(x)		(P1M1 &=~(x));(P1M0 &=~(x))	//��P10~P17����Ϊ����׼˫���
#define		P1_Mode_OUT_PP(x)		(P1M1 &=~(x));(P1M0 |= (x))	//��P10~P17����Ϊ�������
#define 	P1_Mode_HighZ(x)		(P1M1 |= (x));(P1M0 &=~(x))	//��P10~P17����Ϊ��������
#define 	P1_Mode_OUT_OD(x)		(P1M1 |= (x));(P1M0 |= (x))	//��P10~P17����Ϊ��©���

#define   P2_Mode_PullUp(x)		(P2M1 &=~(x));(P2M0 &=~(x))	//��P20~P27����Ϊ����׼˫���
#define		P2_Mode_OUT_PP(x)		(P2M1 &=~(x));(P2M0 |= (x))	//��P20~P27����Ϊ�������
#define 	P2_Mode_HighZ(x)		(P2M1 |= (x));(P2M0 &=~(x))	//��P20~P27����Ϊ��������
#define 	P2_Mode_OUT_OD(x)		(P2M1 |= (x));(P2M0 |= (x))	//��P20~P27����Ϊ��©���

#define   P3_Mode_PullUp(x)		(P3M1 &=~(x));(P3M0 &=~(x))	//��P30~P37����Ϊ����׼˫���
#define		P3_Mode_OUT_PP(x)		(P3M1 &=~(x));(P3M0 |= (x))	//��P30~P37����Ϊ�������
#define 	P3_Mode_HighZ(x)		(P3M1 |= (x));(P3M0 &=~(x))	//��P30~P37����Ϊ��������
#define 	P3_Mode_OUT_OD(x)		(P3M1 |= (x));(P3M0 |= (x))	//��P30~P37����Ϊ��©���

#define   P4_Mode_PullUp(x)		(P4M1 &=~(x));(P4M0 &=~(x))	//��P40~P47����Ϊ����׼˫���
#define		P4_Mode_OUT_PP(x)		(P4M1 &=~(x));(P4M0 |= (x))	//��P40~P47����Ϊ�������
#define 	P4_Mode_HighZ(x)		(P4M1 |= (x));(P4M0 &=~(x))	//��P40~P47����Ϊ��������
#define 	P4_Mode_OUT_OD(x)		(P4M1 |= (x));(P4M0 |= (x))	//��P40~P47����Ϊ��©���

#define   P5_Mode_PullUp(x)		(P5M1 &=~(x));(P5M0 &=~(x))	//��P50~P57����Ϊ����׼˫���
#define		P5_Mode_OUT_PP(x)		(P5M1 &=~(x));(P5M0 |= (x))	//��P50~P57����Ϊ�������
#define 	P5_Mode_HighZ(x)		(P5M1 |= (x));(P5M0 &=~(x))	//��P50~P57����Ϊ��������
#define 	P5_Mode_OUT_OD(x)		(P5M1 |= (x));(P5M0 |= (x))	//��P50~P57����Ϊ��©���

#define   P6_Mode_PullUp(x)		(P6M1 &=~(x));(P6M0 &=~(x))	//��P60~P67����Ϊ����׼˫���
#define		P6_Mode_OUT_PP(x)		(P6M1 &=~(x));(P6M0 |= (x))	//��P60~P67����Ϊ�������
#define 	P6_Mode_HighZ(x)		(P6M1 |= (x));(P6M0 &=~(x))	//��P60~P67����Ϊ��������
#define 	P6_Mode_OUT_OD(x)		(P6M1 |= (x));(P6M0 |= (x))	//��P60~P67����Ϊ��©���

#define   P7_Mode_PullUp(x)		(P7M1 &=~(x));(P7M0 &=~(x))	//��P70~P77����Ϊ����׼˫���
#define		P7_Mode_OUT_PP(x)		(P7M1 &=~(x));(P7M0 |= (x))	//��P70~P77����Ϊ�������
#define 	P7_Mode_HighZ(x)		(P7M1 |= (x));(P7M0 &=~(x))	//��P70~P77����Ϊ��������
#define 	P7_Mode_OUT_OD(x)		(P7M1 |= (x));(P7M0 |= (x))	//��P70~P77����Ϊ��©���