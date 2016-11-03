/*
 * Joystick.c
 *
 * Created: 16.11.2015 15:17:08
 *  Author: tiws-16-11
 */ 
#include <avr/io.h>
#include "Joystick.h"

uint8_t joyIsInit = FALSE;

void Jstick_Init()
{
	if(joyIsInit) return;
	
	DDRB = 0xf7;	// /SS, MOSI, SCK: Ausgänge
	PORTB |= 0x1;	// /SS=1 (Slave deaktiviert)
	// SPI als Master mit f_SCK=f_CPU/128 einschalten
	SPCR = (1<<SPE)|(1<<MSTR)|(0b11<<SPR0);
	joyIsInit = TRUE;
}


RESULT Jstick_Get(struct Jstick_Data* dstData,uint8_t LedDat)
{
	if(!joyIsInit)
		return  R_M_NOT_INIT;
	
	uint8_t pBuffer[5];
	PORTB &=~1; // Slave
	SPDR = 0b10000000|(LedDat & 0b11);
	for (uint8_t i = 0; i < 5; i++)
	{
		while (!(SPSR & (1<<SPIF)));  // Warte auf SPI-Übertragung
		pBuffer[i] = SPDR;
		if (i<4) SPDR = 0;
	}
	PORTB |= 1;
	
	dstData->x =  *(uint16_t*)pBuffer;
	dstData->y = *(uint16_t*)(pBuffer + 2);
	dstData->x -= 512;
	dstData->y -= 512;
	
	dstData->x /= 420.0f;
	dstData->y /= 420.0f;
	
	dstData->x = dstData->x * (fabs(dstData->x) > 0.1f);
	dstData->y = dstData->y * (fabs(dstData->y) > 0.1f);
	
	return R_OK;
}