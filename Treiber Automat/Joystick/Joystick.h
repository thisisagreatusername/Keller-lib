/*
 * Joystick.h
 *
 * Created: 21.01.2016 01:27:43
 *  Author: Henrik
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "Result.h"
#include "Kodierer.h"

RESULT
Joystick_init();		//JoyStick initialisieren

RESULT Joystick_step();		//Schrittfunktion sp�ter Interrupt Service Routine


uint16_t Joystick_get_xraw();	//gibt x-Wert zur�ck

uint16_t Joystick_get_yraw();	//gibt y-Wert zur�ck

int6_t Joystick_get_x();		//gibt x Wert zwischen -32 und +32 zur�ck

int6_t Joystick_get_y();		//gibt y Wert zwischen -32 und +32 zur�ck



BOOL Joystick_get_b1();	// gibt 1 zur�ck wenn Button 1 gedr�ckt ist sons 0

BOOL Joystick_get_b2();	// gibt 1 zur�ck wenn Button 2 gedr�ckt ist sons 0

BOOL Joystick_get_b3();	// gibt 1 zur�ck wenn Button 3 (Joystick) gedr�ckt ist sons 0


RESULT Joystick_setled(uint8_t Led);	//Led�s ein bzw aus schalten


#endif /* JOYSTICK_H_ */