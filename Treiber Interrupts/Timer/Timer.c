/*
 * Timer.c
 *
 * Created: 07.12.2015 18:44:05
 *  Author: tiws-16-10
 */ 
#include <avr/io.h>
#include "Timer.h"
#include "Result.h"

uint32_t Timer_counter;		//Aufwährtszählender Programmzeitcounter
uint16_t Timer_array[4];	//Abwährtszählende Timer (4)

#define WGM_CTC 0b0100		//Clear Timer on Compare - Modus
#define CS256 0b100		//Vorteiler 256

void Timer_init100ms()	//Initialisierungsfunktion für 100ms Timer
{
	TCCR1A = WGM_CTC & 0b11;	//Betriebsart & Zähltakt
	TCCR1B = (WGM_CTC & 0b1100)<<1 | (CS256 & 0b111);
	OCR1A = 3125;				//Vergleichswert für 100 ms
	Timer_counter = 0;			//Programmzeitcounter löschen
	TIMSK1 |= 1<<OCIE1A;		//Vergleichs-Int A ein
}

RESULT Timer_start(uint16_t timerwert, uint8_t nr)	//Timer nummer mit timerwert starten
{
	uint8_t aiz = TIMSK1;		//aktuellen Interrupt-Zustand sichern
	TIMSK1 &= ~(1<<OCIE1A);		//Vergleichs-Interrupt A ausschalten
	Timer_array[nr & 0b11] = timerwert;			//Timer setzen
	TIMSK1 = aiz;				//Interrupt-Zustand wiederherstellen
	return R_OK;
}


uint16_t Timer_gettime(uint8_t nr);	//Timerstand von Timer nummer auslesen
{
	uint8_t aiz = TIMSK1;		//aktuellen Interrupt-Zustand sichern
	TIMSK1 &= ~(1<<OCIE1A);		//Vergleichs-Interrupt A ausschalten
	uint16_t tts = Timer_array[nr & 0b11];	//Timer-Stand von Timer nummer temporär speichern
	TIMSK1 = aiz;				//Interrupt-Zustand wiederherstellen
	return tts;					//Timerstand zurückgeben
}


uint32_t Timer_gettotal()	//Programmzeitcounter auslesen
{
	uint8_t aiz = TIMSK1;		//aktuellen Interrupt-Zustand sichern
	TIMSK1 &= ~(1<<OCIE1A);		//Vergleichs-Interrupt A ausschalten
	uint32_t tts = Timer_counter;	//Programmzeitcounter temporär speichern
	TIMSK1 = aiz;				//Interrupt-Zustand wiederherstellen
	return tts;			//Programmzeitcounter zurückgeben
}




ISR(Timer1_COMPA_vect)	//Vergleichs-Interrupt alle 100ms
{
	Timer_counter++;	//Programmzeitcounter erhöhen
	for (uint8_t nr = 0; nr < 4; nr++)	//Für alle Timer (4)
	{
		if(Timer_array[nr]!=0)	//Wenn noch nicht abgelaufen
		{
			Timer_array[nr]--;	//abwärts zählen
		}
	}
}



