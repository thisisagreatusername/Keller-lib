/*
 * Ctrl.h
 *
 * Created: 21.01.2016 01:25:03
 *  Author: Henrik
 */ 


#ifndef CTRL_H_
#define CTRL_H_

#include "Result.h"

#define CTRL_CONNECTED 0
#define CTRL_NOTCONNECTED 1

void Ctrl_init(uint16_t repeattime);

uint8_t Ctrl_connect();

RESULT Ctrl_update();


#endif /* CTRL_H_ */