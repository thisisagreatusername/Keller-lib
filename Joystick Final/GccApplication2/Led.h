/*
 * Led.h
 *
 * Created: 02.11.2015 15:42:38
 *  Author: tiws-16-11
 */ 

#ifndef LED_H_
#define LED_H_
#include "Result.h"
#include "Bit.h"

void Led_Init();
void DLed_Init();
void DLed_Set(uint8_t val);
RESULT Led_OnAll();
RESULT Led_OffAll();
RESULT Led_SetBit(uint8_t bit, uint8_t val);
RESULT Led_ShiftLeft();
RESULT Led_ShiftRight();
RESULT Led_Set(uint8_t val);

#endif /* LED_H_ */