/*
 * engine.h
 *
 * Created: 26.01.2016 21:22:24
 *  Author: tiws-16-10
 */ 


#ifndef ENGINE_H_
#define ENGINE_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void engineInit(); 
void engineStart();
void engineStop();
void engineStep();
void rotationGet(int16_t* spA, int16_t* spB);
void clearCounter();
void engineRight(int16_t speed);
void engineLeft(int16_t speed);
uint8_t engine_getErrCount();

#endif /* ENGINE_H_ */