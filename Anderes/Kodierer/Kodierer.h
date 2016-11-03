/*
 * Kodierer.h
 *
 * Created: 21.01.2016 01:29:26
 *  Author: Henrik
 */ 


#ifndef KODIERER_H_
#define KODIERER_H_

#include "Result.h"


typedef int8_t int6_t;		// Vorzeichenbit 0 0 x   x x x x
//liegt zwischen -32 und +31

typedef uint8_t uint2_t;	// 0 0 0 0  0 0 x x
//liegt zwischen 0b00=0 und 0b11=4

#define C_CONTROL 0b00
#define C_SPEED 0b01
#define C_STEERING 0b10
#define C_SPECIAL 0b11



uint8_t Encode(uint2_t typ, int6_t value);	//Nachricht aus Typ und Wert zusammensetzen.

RESULT Decode(uint8_t message, int6_t *value, uint2_t *typ);	//Nachricht in Typ und Wert zerlegen





#endif /* KODIERER_H_ */