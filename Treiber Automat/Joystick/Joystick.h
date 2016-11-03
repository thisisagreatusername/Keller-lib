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

RESULT Joystick_step();		//Schrittfunktion später Interrupt Service Routine


uint16_t Joystick_get_xraw();	//gibt x-Wert zurück

uint16_t Joystick_get_yraw();	//gibt y-Wert zurück

int6_t Joystick_get_x();		//gibt x Wert zwischen -32 und +32 zurück

int6_t Joystick_get_y();		//gibt y Wert zwischen -32 und +32 zurück



BOOL Joystick_get_b1();	// gibt 1 zurück wenn Button 1 gedrückt ist sons 0

BOOL Joystick_get_b2();	// gibt 1 zurück wenn Button 2 gedrückt ist sons 0

BOOL Joystick_get_b3();	// gibt 1 zurück wenn Button 3 (Joystick) gedrückt ist sons 0


RESULT Joystick_setled(uint8_t Led);	//Led´s ein bzw aus schalten


#endif /* JOYSTICK_H_ */