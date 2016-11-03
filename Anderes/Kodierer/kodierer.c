/*
 * kodierer.c
 *
 * Created: 21.01.2016 01:28:34
 *  Author: Henrik
 */ 
#include <avr/io.h>
#include "Result.h"
#include "Kodierer.h"

uint8_t Encode(uint2_t typ, int6_t value)
{
	if (value==-32)
	{
		return 0b00011111 | (typ<<6);
	}
	
	if((value < -32) || (value > 31))
	{
		//Fehlerzähler erhöhen;
		return 0;
	}
	

	if (value&0b10000000)	//Wenn Wert negativ
	{
		value = abs(value) | 0b00100000;
	}
	else
	{
		value = value & 0b00011111;
	}
	
	//Nachricht zusammensetzen
	uint8_t message = 0;
	message |= typ<<6;	//tt00 0000
	message |= value;	//ttww wwww
	return message;
}



RESULT Decode(uint8_t message, int6_t *value, uint2_t *typ)
{
	//typ zurückgeben
	*typ = (message & 0b11000000) >> 6;
	
	if (message & 0b00100000)
	{
		*value = 0 - (message&0b00011111);
	}
	else
	{
		*value = (message & 0b00011111);
	}
	return R_OK;
}