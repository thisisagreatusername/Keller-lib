/*
 * Joystick.c
 *
 * Created: 21.01.2016 01:26:01
 *  Author: Henrik
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Joystick.h"
#include "Result.h"

RESULT Joystickisinit = FALSE;
uint8_t i = 6;	//Byte, dass gerade emofange wird
uint8_t LedDat = 0b11;	//Leds am Joystick
uint8_t data[5];	//Speicher der Werte
uint8_t datacopy[5];	//Speicher der Werte

RESULT Joystick_init()
{
	if (Joystickisinit) return R_OK;
	
	DDRB = 0xf7;	//	/SS, MOSI, SCK: Ausgänge
	PORTB |= 0x1;	//	/SS=1 (Slave deaktiviert)
	//SPI als Master mit fSCK=f_CPU/128 einschalten
	SPCR = (1<<SPE) | (1<<MSTR) | (0b11<<SPR0);
	Joystickisinit = TRUE;
	return R_OK;
}

RESULT Joystick_step()
{
	switch(i)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		if (SPSR & (1<<SPIF))	//Wenn SPI fertig
		{
			data[i] = SPDR;		//Byte empfangen
			if (i<4)
			{
				SPDR = 0;		//Byte senden
			}
			i++;
		}
		break;
		
		case 5:	//end
		PORTB |= 1;			//Slave deaktivieren
		i++;
		//Kopie zum auslesen erstellen
		datacopy[0] = data[0];
		datacopy[1] = data[1];
		datacopy[2] = data[2];
		datacopy[3] = data[3];
		datacopy[4] = data[4];
		break;
		
		
		case 6:	//start
		PORTB &=~1;		//Slave aktivieren
		SPDR = 0b100000000 | (LedDat & 0b11);	//1. Byte senden
		i = 0;
		break;
		
		default:
		break;
	}
	return R_OK;
}


uint16_t Joystick_get_xraw()
{
	uint16_t x = (datacopy[1] << 8) + datacopy[0];
	return(x);
}


uint16_t Joystick_get_yraw()
{
	uint16_t y = (datacopy[3] << 8) + datacopy[2];
	return(y);
}


//	1 = gedrückt
BOOL Joystick_get_b1()
{
	return (data[4] & 0b010);
}


BOOL Joystick_get_b2()
{
	return(data[4] & 0b100);
}


BOOL Joystick_get_b3()		//Joystick gedrückt
{
	return(data[4] & 0b001);
}


RESULT Joystick_setled(uint8_t Led)
{
	LedDat = Led;
	return R_OK;
}




int6_t Joystick_get_x()
{
	uint16_t x = (datacopy[1] << 8) + datacopy[0];
	x -= 512;
	x /= 16;
	int6_t xmapped = x;
	if (xmapped<4 && xmapped>-4)
	{
		xmapped = 0;
	}
	return xmapped;
}


int6_t Joystick_get_y()
{
	uint16_t y = (datacopy[3] << 8) + datacopy[2];
	y -= 512;
	y /= 16;
	int6_t ymapped = y;
	if (ymapped<4 && ymapped>-4)
	{
		ymapped = 0;
	}
	return ymapped;
}