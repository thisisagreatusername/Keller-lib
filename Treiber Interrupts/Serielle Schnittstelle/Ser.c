/*
 * Ser.c
 *
 * Created: 21.01.2016 01:34:12
 *  Author: Henrik
 */ 
#include "Result.h"
#include <avr/interrupt.h>
#include "Kodierer.h"
#include "Ser.h"


uint8_t message[4] = {0, 0b01000000, 0b10000000, 0b11000000};	//Speichert die Nachrichten der 4 verschiedenen Kategorien
BOOL sendrequest[4] = {FALSE, FALSE, FALSE, FALSE};	//Speicher ob die Nachricht der jeweiligen Kategorie gessendet werden soll
uint8_t received = 0;	//zuletzt empfangenes Byte
uint8_t next = 0;


/*
RESULT Ser_init_blue	//PC-Kommunikation via Bluetooth initialisieren
{
	UCSR0C=0b110;                   // Übertragungsformat 8N1
	UBRR0=51;                       // 9600 Baud
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);   // Empfänger und Sender einschalten
	//Interrupts freigeben
}*/

RESULT Ser_init_pc()	//PC Kommunikation über Kabel initialisieren
{
	UCSR2C=0b110;	                // Übertragungsformat 8N1
	UBRR2=51;                     // 9600 Baud
	UCSR2B=(1<<RXEN2)|(1<<TXEN2); // Sender und Empfänger ein
	UCSR2B |= (1<<RXCIE2);        // Empfangsinterrupt ein
	return R_OK;
}

ISR(USART2_RX_vect)	//ISR Empfang
{
	received = UDR2;
}

ISR(USART2_UDRE_vect)	// Sendepuffer-frei ISR
{
	if (next >4)
	{
		next = 0;
	}
	for (int8_t i = 0; i<4; i++)
	{
		if (sendrequest[next]==TRUE)
		{
			UDR2 = message[next];
			next++;
			return;
		}
		next++;
	}
	UCSR2B &= ~(1<<UDRIE2);     // Puffer-frei-Interrupt aus
	return;
}


uint8_t ser_get()	// Empfangsnachricht abholen
{
	return received;
}

RESULT Ser_send(uint8_t code, uint2_t typ)
{
	uint8_t temp = UCSR2B;
	UCSR2B &= ~(1<<RXCIE2);
	
	message[typ] = code;
	sendrequest[typ] = TRUE;
	
	UCSR2B = temp;
	UCSR2B |= 1<<UDRIE2;         // Interrupt-Freigabe einschalten	
	return R_OK;
}