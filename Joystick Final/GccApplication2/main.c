/*
 * GccApplication2.c
 *
 * Created: 26.10.2015 17:53:36
 * Author : tiws-16-11
 */ 
#include <avr/io.h>
#include "Led.h"
#include "Ctrl.h"
#include "Joystick.h"

int main(void)
{
	Led_Init();
	DLed_Init();
	Ctrl_init();
	Joystick_init();
	
	while(1)
	{
		DLed_Set(0);
		Led_Set(0xAA);
		uint16_t timer = 0;
		 while(!Ctrl_connect())
		 {
			 // wait
			 if(!(timer++))
				Led_ShiftLeft();
		 }
		 Led_Set(0x0F);
		 RESULT res = R_OK;
		 while(Ctrl_isConnected())
		 {
			res = Ctrl_Update();
			if(FAILED(res))
				DLed_Set(res);
		 
			while( Joystick_step() == R_BUFF_NOT_READY);
		 
			int8_t x = Joystick_get_x();
			int8_t y = Joystick_get_y();
			BOOL pb = Joystick_get_b2();
			BOOL boost = Joystick_get_b1();
			
			Ctrl_UpdateData(y,x,pb,boost);
			
			timer++;
			if(Ctrl_GetBoostFactor() == 2)
			{
				if((timer % 128) == 0)
				{
					Led_ShiftRight();
				}
			}
			else
			{
				if((timer % 256) == 0)
					Led_ShiftLeft();	
			}
		 }
	}
	/*
	Car_init();	
	
    Led_OffAll();
	
	while(Car_connect() == CAR_NOT_CONNECTED)
	{
		//waiting
	}
	
	Led_OnAll();
	while (1) 
    {
		Car_update();
		
		struct carmsg msg;
		if(Car_GetMessage(&msg) == R_OK)
		{
			Led_Set(msg.data);
		}

    }*/
}

