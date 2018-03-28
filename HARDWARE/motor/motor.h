#ifndef __MOROT_H__
#define __MOROT_H__

#include "sys.h"
#include "rs485.h"
//电机管脚*3
#define MOROT1     P15
#define MOROT2     P16
#define MOROT3     P17

#define STOP     0x00
#define START    0x01

void MotorInit();
void MotorDriveDc(u8 number, u8 motor_mode);
RS485_StatusTypeDef MotorDriveDCs(u8 motorDCNum);
#endif





