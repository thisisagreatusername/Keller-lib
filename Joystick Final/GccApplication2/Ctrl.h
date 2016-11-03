/*
 * Ctrl.h
 *
 * Created: 25.01.2016 15:03:15
 *  Author: tiws-16-11
 */ 


#ifndef CTRL_H_
#define CTRL_H_

#include "Result.h"
void Ctrl_init();
BOOL Ctrl_connect();

RESULT Ctrl_Update();
void Ctrl_UpdateData(int8_t speed, int8_t steer,BOOL panicButton, BOOL speedButton);
BOOL Ctrl_isConnected();
int8_t Ctrl_GetBoostFactor();


#endif /* CTRL_H_ */