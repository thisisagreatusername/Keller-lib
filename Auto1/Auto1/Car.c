/*
 * Car.c
 *
 * Created: 26.01.2016 21:31:16
 *  Author: tiws-16-11
 */ 
#include "Car.h"
#include "Blue.h"
#include "Car_Defines.h"
#include "Map.h"
#include <math.h>

BOOL CAR_CONNECTED = FALSE;

int8_t speed = 0;
int8_t dir = 0;
uint8_t chFlags; //Change Flags

RESULT Car_sendPosition()
{
	static uint8_t state = 1;
	static PointI_16 pt;
	
	if(state == 1)
	{
		pt = Map_getSmallPos();
		pt.x += 512;
		pt.y += 512;	
	}
	
	static const uint8_t POSHEADER = 0b10000000;
	static const uint8_t XHEAD = 0;
	static const uint8_t YHEAD = 1 << 6;
	static const uint8_t LOW = 0;
	static const uint8_t HIGH = 1 << 5;
	
	
	uint8_t data = 0;
	
	switch(state)
	{
	case 0: // pos y part 2
		data = POSHEADER | YHEAD | HIGH;
		data |=  (((uint16_t)pt.y & 0x03E0) >> 5);
		break;
	case 1: // pos x part 1
		data = POSHEADER | XHEAD | LOW;
		data |= pt.x & 0b00011111;
		break;
	case 2:  // pos x part 2
		data = POSHEADER | XHEAD | HIGH;
		data |= (((uint16_t)pt.x & 0x03E0) >> 5);
		break; 
	case 3: // pos y part 1
		data = POSHEADER | YHEAD | LOW;
		data |= pt.y & 0b00011111;
		break;	
	default:
		return R_NULL;	
	}
	
	RESULT res = Blue_Send(data);
	if(SUCCEDED(res))
	{
		state++;
		if(state > 3)
		state = 0;
	}
	return R_OK;
}

int16_t Car_calcDir(int16_t dir)
{
	dir = clamp(dir,-100,100);
	int8_t sign = 1;
	if(dir < 0)
		sign = -1;
	
	return sign * (100 - (int16_t)(sqrtf((float)(10000 - dir * dir)) + 0.5f));
}

void Car_SetDefaults()
{
	speed = 0;
	dir = 0;
	chFlags = FLAG_SPEED | FLAG_DIR;
}

void Car_init()
{
	Blue_Init();
}

BOOL Car_connect()
{
	uint8_t msg;
	RESULT res;
	if(CAR_CONNECTED)
	{
		res = Blue_Send(MSGCTRL_INIT);
		return SUCCEDED(res);
	}
	
	res = Blue_Get(&msg);
	
	if(SUCCEDED(res))
	{
		if(msg == MSGCTRL_INIT)
		{
			Car_SetDefaults();
			CAR_CONNECTED = TRUE;
			res = Blue_Send(msg);
			return SUCCEDED(res);
		}
	}
	return FALSE;
}

BOOL Car_isConnected()
{
	return CAR_CONNECTED;
}

RESULT Car_update()
{
	uint8_t msg;
	RESULT res = R_OK;
	
	res = Car_sendPosition();
	if(FAILED(res))
		return res;
	
	if(SUCCEDED(Blue_Get(&msg)))
	{
		const uint8_t type = msg & MSGMASK_TYPE;
		uint8_t data = msg & MSGMASK_DATA;
		if((type == MSGSPEED) || (type == MSGSTEER))
		{
			data = from6Bit(data);
		}
		
		switch(type)
		{
		case MSGSPEED:
			if(data != speed)
			{
				speed = data;
				chFlags |= FLAG_SPEED;
			}
			break;
		case MSGSTEER:
			if(data != dir)
			{
				dir = data;
				chFlags |= FLAG_DIR;
			}
			break;
		case MSGSPECIAL:
			if(msg == MSGSTOP)
			{
				chFlags |= FLAG_STOP;
				CAR_CONNECTED = FALSE;
			}

			break;	
		}
	}
	
	return res;
}

int8_t Car_getSpeed()
{
	return speed;	
}

int8_t Car_getDir()
{
	return dir;
}

uint8_t Car_getFlags()
{
	uint8_t res = chFlags;
	chFlags = 0;
	return res;
}