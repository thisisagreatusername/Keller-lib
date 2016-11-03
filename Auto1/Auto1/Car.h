/*
 * Car.h
 *
 * Created: 26.01.2016 21:29:14
 *  Author: tiws-16-11
 */ 


#ifndef CAR_H_
#define CAR_H_

#include <avr/io.h>
#include "Result.h"

#define FLAG_SPEED	0x01
#define FLAG_DIR	0x02
#define FLAG_STOP	0x04

void Car_init();
BOOL Car_connect();
BOOL Car_isConnected();
RESULT Car_update();
int8_t Car_getSpeed();
int8_t Car_getDir();

uint8_t Car_getFlags();
int16_t Car_calcDir(int16_t dir);

#endif /* CAR_H_ */