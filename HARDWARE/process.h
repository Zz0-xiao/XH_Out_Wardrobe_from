#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "sys.h"
#include "rs485.h"

RS485_StatusTypeDef Debug_Process(u8* pbuff);
RS485_StatusTypeDef SendOut(u8* pbuff);


#endif





