#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "sys.h"

u16 crc16_ccitt(u8 *ptr, u8 len);
void BuffReset_API(u8 *ptr,u8 len);

//uint32_t ASCII_TO_INT(u8 *pdata,u16 NUM);
//u16 crc16one(u8 input,u16 incrc);
//u8 CrcCheck(u8 *buff,u16 buffsize,u8* crc);
#endif

