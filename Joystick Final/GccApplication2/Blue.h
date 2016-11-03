/*
 * Blue.h
 *
 * Created: 09.11.2015 18:46:24
 *  Author: tiws-16-11
 */ 


#ifndef BLUE_H_
#define BLUE_H_
#include <avr/io.h>
#include "Result.h"

void Blue_Init();
RESULT Blue_Get(uint8_t* dst);
RESULT Blue_Send(uint8_t data);

#endif /* BLUE_H_ */