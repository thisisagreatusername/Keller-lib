/*
 * Son.c
 *
 * Created: 30.11.2015 18:06:34
 *  Author: tiws-16-10
 */ 
#include <avr/io.h>
#include "Son.h"
#include "Result.h"

BOOL SonIsInit = FALSE;
BOOL SonNewDist = Flase;
uint8_t SonState;	//Sonar-Zut�nde:
//0: Warte auf R
//1: Warte auf erste Ziffer
//2: warte auf zweite Ziffer
//3: warte auf dritte Ziffer

uint8_t distance;	//gemessene Entfernung
uint8_t wdistance;	//zur Berechnung der Entfernung

void Son_init()
{
	if(SonIsInit) return;	//�berpr�ft ob bereits initialisiert
	UCSR1C = 0b110;			//�bertragungsformat 8N1
	UBRR1 = 51;				//9600 Baud
	UCSR1B |= (1<<RXEN1);	//Empf�nger ein
	DDRD |= 1<<PD5;			//PD5 Ausgang
	PORTD |= 1<<OD5;		//Sonar einschalten
	SonState = 0;			//Sonar Zustand 0
}

RESULT Son_step();			//Sonar Step Funktion als Automat
{
	if(!SonIsInit) return R_M_NOT_INIT;		//�berpr�ft ob bereits initialisiert
	if (!(UCSR1A & (1<<RXC1))) return R_OK;	//kein neues Zeichen
	uint8_t dat = UDR1;						//Zeichen lesen
	if (dat=='R')							//Wenn 'R'
	{
		SonState = 1						//gehe in Zustand 1
		wdistance = 0						//Entfernung auf 0 setzen
	}
	if (SonState > 0 && SonState < 4)		//Wenn auf Zahl warten
	{
		if (dat >= '0' && dat <= '9')		//�berpr�fe ob Zahl
		{
			wdistance = (wdistance*10) + (dat-'0');	//erh�he wdistance entsprechen
			SonState++;
		} 
		else
		{
			SonState = 0;				//Wenn keine Zahl warte auf 'R'
			return R_OK;
		}
	}
	if (SonState == 4)					//Wenn Drei Zahlen eingelesen
	{
		distance = wdistance;			//gebe Messung frei
		SonNewDist = TRUE;
		SonState = 0;					//setze den Zustand zur�ck
		return R_OK;
	}
}


RESULT Son_get(uint8_t *dst);	//Entfernung auslesen
{
	if (SonNewDist==TRUE)		//Wenn neuer Wert da
	{
		*dst = distance;		//Wert kopieren
		SonNewDist = FALSE;		//Zur�cksetzen
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
