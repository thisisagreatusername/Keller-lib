/*
 * Car_Defines.h
 *
 * Created: 25.01.2016 15:08:23
 *  Author: tiws-16-11
 */ 


#ifndef CAR_DEFINES_H_
#define CAR_DEFINES_H_

#include <avr/io.h>
#include <math.h>

#define MSGSPEED  0x40
#define MSGSTEER  0x80
#define MSGSPECIAL  0xC0
#define MSGCTRL  0x00
#define MSGMASK_TYPE 0xC0
#define MSGMASK_DATA  0x3F
#define MSGMASK_SIGN  0x20
#define MSGMASK_UNDATA   0x1f

#define MSGCTRL_INIT  0xC0
#define MSGJOY_INIT  0xC2

#define MSGDISCONNECT 0xC1
#define MSGSTOP 0xFF
#define MSGBOOST 0xC3

int8_t from6Bit(uint8_t b);
int8_t to6Bit(int8_t d);

#endif /* CAR_DEFINES_H_ */