/*
 * Car_Defines.c
 *
 * Created: 25.01.2016 15:45:29
 *  Author: tiws-16-11
 */ 
#include "Car_Defines.h"
#include <avr/io.h>

int8_t from6Bit(uint8_t b)
{
	b = b & 0b00111111;
	if(b & 0b00100000)
	{
		//negative
		return 0 - (int8_t)(b & 0b00011111);
	}
	else
	{
		//positive
		return b;
	}
}
int8_t to6Bit(int8_t d)
{
	if(d < 0)
	{
		//keep sign
		d = abs(d);
		return (d |MSGMASK_SIGN) & MSGMASK_DATA;
	}
	else
	{
		return d & MSGMASK_UNDATA;
	}
}