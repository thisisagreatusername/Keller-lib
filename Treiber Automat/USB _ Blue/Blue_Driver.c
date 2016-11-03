/*
 * BlueDriver.c
 *
 * Created: 30.11.2015 18:21:52
 *  Author: tiws-16-12
 */ 
#include "Blue_Driver.h"

uint8_t send_msg;
uint8_t return_msg;
uint8_t byteGesendet;
uint8_t byteEmpfangen;

void blue_init()
{
	UCSR0C=0b110;                   // Übertragungsformat 8N1
	UBRR0=51;                       // 9600 Baud
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);   // Empfänger und Sender
}

uint8_t blue_get(uint8_t *msg)
{
	if(!byteEmpfangen)
		return 0;
	*msg = return_msg;
	byteEmpfangen = 0;
	return 1;
}

uint8_t blue_send(uint8_t *msg)
{
	if(!byteGesendet)
		return 0;
	send_msg = *msg;
	byteGesendet = 0;
	return 1;
}

uint8_t blue_step()
{
	if (UCSR0A & (1<<RXC0) && byteEmpfangen == 0)		// wenn Byte empfangen
	{
		return_msg = UDR0;
		byteEmpfangen = 1;
	}
	if (UCSR0A &(1<<UDRE0) && byteGesendet == 0)	// wenn Sendebuffer frei
	{
		UDR0 = send_msg;
		byteGesendet = 1;
	}
	return 1;
}