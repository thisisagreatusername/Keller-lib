/*
 * Auto1.c
 *
 * Created: 25.01.2016 17:01:38
 * Author : tiws-16-12
 */ 
/*
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Car_Defines.h"
#include "comir_lcd.h"
#include "Blue_Driver.h"
#include "rotmess.h"
#include "pwm.h"

int32_t integA = 0, integB = 0;
int8_t left = 0;
int8_t right = 0;
uint8_t run = 0;*/
#include <avr/interrupt.h>
#include "Led.h"
#include "Lcd.h"
#include "Car.h"
#include "engine.h"
#include "Map.h"

ISR(TIMER1_COMPA_vect)
{
	uint8_t  tmp = TIMSK1;    // Int.-Zustand sichern
	TIMSK1 &= ~(1<<OCIE1A);	// Vergleichs-Interrupt A aus
	//int16_t l, r;
	//rotationGet(&l, &r);
	//Lcd_dispVal(l, 0, 5);
	//Lcd_dispVal(-r, 16, 5);
	engineStep();
	
	TIMSK1 = tmp;             // Int.-Zustand wiederherst.
}
void tmr_init()
{
	TCCR1A = 0b0100 & 0b11;  // Betriebsart & Zähltakt
	TCCR1B = (0b0100 & 0b1100)<<1 | (0b100 & 0b111);
	OCR1A  = 3125 / 6;            // Vergleichswert für 100 ms
	TIMSK1 |= 1<<OCIE1A;	    // Vergleichs-Interrupt A ein
}


int main(void)
{
	Led_Init();
	Car_init();
	engineInit();
	tmr_init();
	
	Lcd_init("init");
	
	//Point ptDir;
	//ptDir.x = 200.0f;
	//ptDir.y = 400.0f;
	//ptDir = pt_norm(ptDir);
	//float len = sqrtf(ptDir.x * ptDir.x + ptDir.y * ptDir.y);
	//ptDir.x /= len;
	//ptDir.y /= len;
	
	sei();
	
	while(1)
	{
		// init phase
		
		Lcd_clear();
		Lcd_dispText(0,"waiting patiently");
		Led_Set(0xAA);
		uint16_t timer = 0;
		//cool animation
		const uint8_t pointStart = 17;
		uint8_t pointOff = 0;
		Lcd_dispChr('.',pointStart);
		
		while(!Car_connect())
		{
			//wait...
			timer++;
			if(timer == 0)
			{
				Led_ShiftLeft();
				pointOff++;
				if(pointOff > 2)
				{
					for(uint8_t i = 0; i < 3; i++)
					{
						Lcd_dispChr(' ',pointStart + i);
					}
					pointOff = -1;
				}
				else
				{
					Lcd_dispChr('.',pointStart + pointOff);
				}
			}

		}
		
		Lcd_clear();
		Led_OffAll();
		engineStart();
		Map_init();
	
		
		engineLeft(0);
		engineRight(0);
		
		RESULT res = R_OK;
		while(Car_isConnected())
		{
			PointI_16 pt = Map_getSmallPos();
			Point ptDir = Map_getDir();
					
			Lcd_dispVal(pt.x,8,6);
			Lcd_dispVal(pt.y,24,6);
			
			Lcd_dispVal(ptDir.x * 100.0f,0,6);
			Lcd_dispVal(ptDir.y * 100.0f,16,6);
			
			res = Car_update();
			if(FAILED(res))
			{
				Led_Set(res);
				break; //Leave Loop
			}
			
			BOOL bChange = FALSE;
			
			const uint8_t flags = Car_getFlags();
			if(flags & FLAG_SPEED)
			{

				//Lcd_dispVal(Car_getSpeed(),2,3);
				bChange = TRUE;
			}
			if(flags & FLAG_DIR)
			{
				//Lcd_dispVal(Car_getDir(),18,3);
				bChange = TRUE;
			}
			/*
			if(flags & FLAG_STOP)
			{}*/
			
			Led_Set(engine_getErrCount());
			if(engine_getErrCount() > 200)
			{
				res = R_ENGINE_ERROR;
				break; //Leave Loop
			}
			
			// engine
			
			//calculate left and right speed
			if(bChange)
			{
				//speed left and right
				int16_t sl = 10 *  clamp(Car_getSpeed(),-20,20);
				int16_t sr = sl;
				
				int16_t dir = Car_calcDir( 10 * Car_getDir() );
				int16_t dirh = dir / 2;			
				
				sl += dirh;
				sr -= dirh;
				
				sl /= 16;
				sr /= 16;
				
				
				
				engineLeft(sl);
				engineRight(sr);
			}
		}
		
		engineStop();
		
		if(FAILED(res))
		{
			SetError(res);
			while(1)
			{
				
			}
		}
	}

			/*rotmess_get(&r, &l);
			if((blue_sendbuff_free() == R_OK) && (ra != r))
			{
				ra = r;
				blue_send(0x80|to6Bit(l));
			}
			if((blue_sendbuff_free() == R_OK) && (la != l))
			{
				la = l;
				blue_send(0x80|to6Bit(l));
			}*/
			/*if(blue_sendbuff_free()´&& (ra != r) && (la != la))
			{
				c = 1-c;
				rotmess_get(&r, &l);
				ra = r;
				la = l;
				if(c)
					blue_send(0x80|to6Bit(l));
				else
					blue_send(0x40|to6Bit(r));
			}*/
		//}
    //}*/
}
/*
void tmr_init(){
	TCCR1A = 0b0100 & 0b11;  // Betriebsart & Zähltakt
	TCCR1B = (0b0100 & 0b1100)<<1 | (0b100 & 0b111);
	OCR1A  = 3125;            // Vergleichswert für 100 ms
	TIMSK1 |= 1<<OCIE1A;	    // Vergleichs-Interrupt A ein
}

void limit(int32_t *val, int32_t max){
	if (*val >  max)
	*val = max;
	else if (*val < -max)
	*val = -max;
}

void Step()
{
	int16_t sa, sb;
	int32_t diffA = 0, diffB = 0;      // Schrittdifferenz
	int32_t pwmA = 0, pwmB = 0;    // Integralanteile
	
	if (rotmess_get(&sa, &sb))
	{
		clear_counter();
		lcd_disp_val(sa, 0, 3);
		lcd_disp_val(-sb, 16, 3);
		
		lcd_disp_val(left, 3, 3);
		lcd_disp_val(right, 16+3, 3);
		
		lcd_disp_val(integA, 7, 4);
		lcd_disp_val(integB, 16+7, 4);
	}
	else
	{
		//sa = 0;
		//sb = 0;
	}
	diffA = left - sa;
	integA += diffA;
	limit(&integA, 100);
	pwmA = integA*200;
	limit(&pwmA, 0x2000);
	diffB = right + sb;
	integB += diffB;
	limit(&integB, 100);
	pwmB = integB*200;
	limit(&pwmB, 0x2000);
	pwm_set_A(pwmA);
	pwm_set_B(-pwmB);
}

ISR(TIMER1_COMPA_vect)
{
	uint8_t  tmp = TIMSK1;    // Int.-Zustand sichern
	TIMSK1 &= ~(1<<OCIE1A);	// Vergleichs-Interrupt A aus
	if(run)
		Step();
	PORTJ = rotmess_err_ct;
	TIMSK1 = tmp;             // Int.-Zustand wiederherst.
}*/