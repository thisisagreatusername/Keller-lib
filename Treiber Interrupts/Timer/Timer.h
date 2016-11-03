/*
 * Timer.h
 *
 * Created: 07.12.2015 18:15:21
 *  Author: tiws-16-10 // Henrik Rosenberg
 */ 

#ifndef TIMER_H_
#define TIMER_H_

#include "Result.h"

void Timer_init100ms();		//Timer inititialisieren

RESULT Timer_start(uint16_t timerwert, uint8_t nr);	//Timer nummer mit timerwert starten

uint16_t Timer_gettime(uint8_t nr);	//Timerstand von Timer nummer auslesen


uint32_t Timer_gettotal();	//Programmzeitcounter auslesen




#endif /* TIMER_H_ */