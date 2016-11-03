#include "Ctrl.h"
#include "Blue.h"
#include "Car_Defines.h"

BOOL CTRL_CONNECTED = FALSE;
uint8_t chFlags = 0;

#define FLAG_SPEED	0x01
#define FLAG_DIR	0x02
#define FLAG_STOP	0x04

int8_t lastSpeed = 0;
int8_t lastSteer = 0;
BOOL lastPanicButton = FALSE;
BOOL lastBoost = FALSE;
int8_t boostFactor = 1;

void Car_SetDefaultValues()
{
	lastSpeed = 0;
	lastSteer = 0;
	lastPanicButton = FALSE;
	lastBoost = FALSE;
	chFlags = FLAG_SPEED | FLAG_DIR;
	boostFactor = 1;
}

void Ctrl_init()
{
	Blue_Init();
}

int8_t Ctrl_GetBoostFactor()
{
	return boostFactor;
}

BOOL Ctrl_connect()
{
	static uint16_t timer = 0;
	
	uint8_t msg;
	RESULT res;
	if(CTRL_CONNECTED)
	{
		res = Blue_Send(MSGJOY_INIT);
		return SUCCEDED(res);
	}
		
	res = Blue_Get(&msg);
	
	if(SUCCEDED(res))
	{
		if(msg == MSGJOY_INIT)
		{
			CTRL_CONNECTED = TRUE;
			Blue_Send(msg);
			Blue_Send(msg);
			Blue_Send(msg);
			res = Blue_Send(msg);
			
			Car_SetDefaultValues();
			return SUCCEDED(res);
		}
	}
	else
	{
		// this will fix the disconnection bug with the pc
		timer++;
		if(timer == 0)
			Blue_Send(MSGSTOP);	
	}
	
	
	return FALSE;
}

BOOL Ctrl_isConnected()
{
	return CTRL_CONNECTED;
}

RESULT Ctrl_Update()
{
	uint8_t msg;
	RESULT res;
	if(SUCCEDED(Blue_Get(&msg)))
	{
		switch(msg)
		{
			case MSGDISCONNECT:
				CTRL_CONNECTED = FALSE;
				break;
		}
	}
		
	if(chFlags & FLAG_STOP)
	{
		res = Blue_Send(MSGSTOP);
		if(SUCCEDED(res))
		{
			chFlags &= ~FLAG_STOP;
			CTRL_CONNECTED = FALSE;
			return R_OK;
		}
		else
		{
			return res;
		}
	}
	
	if(chFlags & FLAG_SPEED)
	{
		res = Blue_Send(MSGSPEED | to6Bit(lastSpeed * boostFactor));
		if(SUCCEDED(res))
		{
			chFlags &= ~FLAG_SPEED;
		}
		else
		{
			return res;
		}
	}
	
	if(chFlags & FLAG_DIR)
	{
		res = Blue_Send(MSGSTEER | to6Bit(lastSteer));
		if(SUCCEDED(res))
		{
			chFlags &= ~FLAG_DIR;
		}
		else
		{
			return res;
		}
	}
	
	return R_OK;
}

void Ctrl_UpdateData(int8_t speed, int8_t steer, BOOL panicButton, BOOL speedButton)
{
	if(lastSteer != steer)
	{
		lastSteer = steer;
		chFlags |= FLAG_DIR;
	}
	
	if(lastSpeed != speed)
	{
		lastSpeed = speed;
		chFlags |= FLAG_SPEED;
	}
	
	if(lastPanicButton != panicButton)
	{
		lastPanicButton = panicButton;
		chFlags |= FLAG_STOP;
	}
	
	if(lastBoost != speedButton)
	{
		lastBoost = speedButton;
		if(lastBoost == 1)
		{
			// toogle booosto
			if (boostFactor == 1)
				boostFactor = 2;
			else
				boostFactor = 1;
			
			chFlags |= FLAG_SPEED;
		}
	}
}