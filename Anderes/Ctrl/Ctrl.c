/*
 * Ctrl.c
 *
 * Created: 21.01.2016 01:23:41
 *  Author: Henrik
 */ 
#include "Ctrl.h"
#include "Ser.h"
#include "Result.h"
#include "Joystick.h"
#include "Lcd.h"
#include "Timer.h"
#include "Kodierer.h"
#include <avr/interrupt.h>

BOOL Connected = FALSE;
int6_t x, y;
int6_t xold, yold;
uint16_t repeatintervall = 0;

void Ctrl_init(uint16_t repeattime)
{
	repeatintervall = repeattime;
	Ser_init_pc();
	Joystick_init();
	Lcd_init("X:              Y:              ");
	Timer_init100ms();
	sei();
}

uint8_t Ctrl_connect()
{
	if (Connected)
	{
		return CTRL_CONNECTED;
	}
	
	uint8_t data = ser_get();
	if (data==0b11000010)
	{
		Ser_send(data, C_CONTROL);
		Connected = TRUE;
		return CTRL_CONNECTED;
	}

	return(CTRL_NOTCONNECTED);
}


RESULT Ctrl_update()
{
	Joystick_step();
	Lcd_step();
	//x und y auf dem LC-Display ausgeben
	Lcd_dispNum(x, 3, 3);
	Lcd_dispNum(y, 19, 3);
	//x und y aktualisieren
	x = Joystick_get_x();
	y = Joystick_get_y();
	
	//Wenn x sich geändert hat senden
	if (xold!=x)
	{
		int8_t code = Encode(C_SPEED, x);
		Ser_send(code, C_SPEED);
		xold = x;
	}
	
	//Wenn y sich geändert hat senden
	if (yold!=y)
	{
		int8_t code = Encode(C_STEERING, y);
		Ser_send(code, C_STEERING);
		yold = y;
	}
	
	//Nach einem bestimmten Zeitintervall alles wiederhohlen
	if (repeatintervall!=0 && Timer_gettime(0)==0)
	{
		//sende x
		int8_t codex = Encode(C_SPEED, x);
		Ser_send(codex, C_SPEED);
		xold = x;
		
		//sende y
		int8_t codey = Encode(C_STEERING, y);
		Ser_send(codey, C_STEERING);
		yold = y;
		
		//timer neustarten
		Timer_start(repeatintervall, 0);
	}
	
	return R_OK;
}