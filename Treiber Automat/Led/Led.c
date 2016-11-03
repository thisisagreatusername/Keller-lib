/*
 * Led.c
 *
 * Created: 16.11.2015 16:03:56
 *  Author: tiws-16-11
 */ 
#include <avr/io.h>
#include "Led.h"
uint8_t ledIsInit = FALSE;

void Led_Init()
{
	if(ledIsInit) return;
	DDRJ = 0xFF;
	PORTJ = 0; //Leds off
	ledIsInit = TRUE;
}
RESULT Led_OnAll()
{
	if(!ledIsInit) return R_M_NOT_INIT;
	PORTJ = 0xFF;
	return R_OK;
}
RESULT Led_OffAll()
{
	if(!ledIsInit) return R_M_NOT_INIT;
	PORTJ = 0;
	return R_OK;
}
RESULT Led_SetBit(uint8_t bit, uint8_t val)
{
	if(!ledIsInit) return R_M_NOT_INIT;
	PORTJ =  SetBit(PORTJ,bit,val);
	return R_OK;
}
RESULT Led_ShiftLeft()
{
	if(!ledIsInit) return R_M_NOT_INIT;
	PORTJ = PORTJ << 1 | PORTJ >> 7;
	return R_OK;
}
RESULT Led_ShiftRight()
{
	if(!ledIsInit) return R_M_NOT_INIT;
	PORTJ = PORTJ << 7 | PORTJ >> 1;
	return R_OK;
}
RESULT Led_Set(uint8_t val)
{
	if(!ledIsInit) return R_M_NOT_INIT;
	PORTJ = val;
	return R_OK;
}

