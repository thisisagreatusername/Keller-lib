/*
 * Joystick.h
 *
 * Created: 02.11.2015 18:06:17
 *  Author: tiws-16-11
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_
#include "Result.h"
#include <math.h>

struct Jstick_Data
{
	float x;	
	float y;
};
void Jstick_Init();
RESULT Jstick_Get(struct Jstick_Data* dstData,uint8_t LedDat);

#endif /* JOYSTICK_H_ */