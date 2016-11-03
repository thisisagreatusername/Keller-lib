/*
 * Bit.c
 *
 * Created: 16.11.2015 16:36:48
 *  Author: tiws-16-11
 */ 
#include <avr/io.h>
#include "Bit.h"

uint8_t GetBit(uint32_t src, uint8_t bit)
{
	return ((src & (1 << bit)) != 0);
}
uint32_t SetBit(uint32_t src, uint8_t bit, uint8_t val)
{
	if(val)
	{
		//set 1
		uint32_t mask = 0b1;
		mask = mask << bit;
		return src | mask;
	}
	else
	{
		uint32_t mask = ~(1 << bit);
		return src & mask;
	}
}