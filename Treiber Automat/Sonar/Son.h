/*
 * Son.h
 *
 * Created: 30.11.2015 18:02:53
 *  Author: tiws-16-10
 */ 


#ifndef SON_H_
#define SON_H_

#include "Result.h"

void Son_init();
RESULT Son_step();
RESULT Son_get(uint8_t *dst);



#endif /* SON_H_ */