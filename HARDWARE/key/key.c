#include <STC8.H>
#include "key.h"

void init_key(void)
{
    P1_Mode_PullUp(key1 | key2 | key3);
}

u8 address()
{
//    u8 add;
//    //00011100
	    //11111111
//    add = (P1 & 0x1c)>>2;
	return (P1 & 0x1c);
}




