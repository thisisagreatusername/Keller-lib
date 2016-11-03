/*
 * USB_Driver.c
 *
 * Created: 30.11.2015 18:04:16
 *  Author: tiws-16-12
 */ 
#include "USB_Driver.h"

uint8_t send_msg;
uint8_t return_msg;
uint8_t byteGesendet = 0;
uint8_t byteEmpfangen = 0;

void usb_init()
{
	UCSR2C=0b110;					// Übertragungsformat 8N1
	UBRR2=51;						// 9600 Baud
	UCSR2B=(1<<RXEN2)|(1<<TXEN2);	// Sender und Empfänger ein
}

uint8_t usb_get(uint8_t *msg)
{
	if(!byteEmpfangen)
		return 0;
	*msg = return_msg;
	byteEmpfangen = 0;
	return 1;
}

uint8_t usb_send(uint8_t *msg)
{
	if(!byteGesendet)
		return 0;
	send_msg = *msg;
	byteGesendet = 0;
	return 1;
}

uint8_t usb_step()
{
	if (UCSR2A & (1<<RXC2) && byteEmpfangen == 0)		// wenn Byte empfangen
	{
		return_msg = UDR2;
		byteEmpfangen = 1;
	}
	if (UCSR2A & (1<<UDRE2) && byteGesendet == 0)	// wenn Sendebuffer frei
	{
		UDR2 = send_msg;
		byteGesendet = 1;
	}
	return 1;
}