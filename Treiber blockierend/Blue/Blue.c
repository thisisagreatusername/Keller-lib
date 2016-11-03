/*
 * Blue.c
 *
 * Created: 16.11.2015 16:50:10
 *  Author: tiws-16-11
 */ 
#include <avr/io.h>
#include "Blue.h"

BOOL blueIsInit = FALSE;

void Blue_Init()
{
	if(blueIsInit) return;
	UCSR0C=0b110;                   // Übertragungsformat 8N1
	UBRR0=51;                       // 9600 Baud
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);   // Empfänger und Sender
	blueIsInit = TRUE;
}
RESULT Blue_Get(uint8_t* dst)
{
	if(!blueIsInit) return R_M_NOT_INIT;
	if(!(UCSR0A & (1<<RXC0))) return R_BUFF_NOT_READY; // warte auf ein Byte
	*dst = UDR0;                 // Byte uebernehmen
	return R_OK;
}
RESULT Blue_Send(uint8_t data)
{
	if(!blueIsInit) return R_M_NOT_INIT;
	if(!(UCSR0A &(1<<UDRE0))) return R_BUFF_NOT_READY;
	UDR0 = data;
	return R_OK;
}