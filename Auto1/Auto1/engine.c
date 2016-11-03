/*
 * engine.c
 *
 * Created: 26.01.2016 21:22:13
 *  Author: tiws-16-10
 */ 
#include "engine.h"
#include "Result.h"
#include "Map.h"

#define MAXPWM 0x2000

int32_t left, right;
int32_t diffLeft, diffRight;
uint16_t stepsA, stepsB;
int8_t sens_A, sens_B;

uint8_t err = 1;

void pwm_init();
void pwm_start();
void pwm_stop();
void pwm_set_A(int16_t pwm);
void pwm_set_B(int16_t pwm);
void clearCounter();
void rotation_init();
int8_t QuadEnc(uint8_t sensdat);
void rotationGet(int16_t* spA, int16_t* spB);
void engineInit();
void engineStart();
void engineStop();
void engineStep();

int16_t pwmA = 0;
int16_t pwmB = 0;
uint8_t engine_getErrCount()
{
	return err;
}

void pwm_init()
{
	DDRL  =0b00110011;   // EN und Dir als Ausgänge
	pwm_stop();          // Zähltakt und PWM aus ...
	TCCR5C = 0b00000000;

	OCR5A = 0x2000;      // Zählperiode  (ca. 1 ms)
	OCR5B = 0;           // PWM_A = 0
	OCR5C = 0;           // PWM_B = 0
}
void pwm_start()
{
	TCCR5A = 0b00101011; //
	TCCR5B = 0b00011001; // zähle IO-Takt ohne Vorteiler
}
void pwm_stop()
{
	TCCR5A = 0;         // PWM ausschalten
	TCCR5B = 0;         // Zähltakt aus
	PORTL  = 0;         // Enable ausschalten
}
void pwm_set_A(int16_t pwm)
{
	pwmA = pwm;
	if (pwm>=0){
		OCR5C = pwm;
		PORTL |=(1<<1);   //dir-Bit (PL1) setzen
	}
	else{
		OCR5C = -pwm;
		PORTL &=~(1<<1);  //dir-Bit (PL1) löschen
	}
}
void pwm_set_B(int16_t pwm)
{
	pwmB = pwm;
	if (pwm>=0){
		OCR5B =pwm;
		PORTL |=1;       //dir-Bit (PL0) setzen
	}
	else{
		OCR5B = -pwm;
		PORTL &= ~1;     //dir-Bit (PL0) löschen;
	}
}
void engineRight(int16_t speed)
{
	right = speed;
	//diffRight = 0;
}
void engineLeft(int16_t speed)
{
	left = speed;
	//diffLeft = 0;
}
void clearCounter()
{
	stepsA = 0;
	stepsB = 0;
}
void rotation_init()
{
	TCCR0A  = 0b10;		// WGM = 0b010 (CTC Mode mit OCR0A)
	TCCR0B  = 0b011;	// CS  = 0b011 (Vorteiler 64)
	OCR0A   = 62;     // OCR = (0,5 ms*8MHz)/64-1
	TIMSK0 |= 1<<OCIE0A;
	sens_A = (PINL>>4) & 0b1100;
	sens_B =  PINL     & 0b1100;
	clearCounter();
}
int8_t QuadEnc(uint8_t sensdat)
{
	switch (sensdat)
	{
		case 0b0010:
		case 0b0100:
		case 0b1011:
		case 0b1101:
		return -1;
		case 0b0001:
		case 0b0111:
		case 0b1000:
		case 0b1110:
		return 1;
		case 0b0011:
		case 0b0110:
		case 0b1100:
		case 0b1001:
		err++;
		default:
		return 0;
	}
}

ISR(TIMER0_COMPA_vect)
{	
	sens_A = (sens_A>>2) | ((PINL>>4) & 0b1100);
	sens_B = (sens_B>>2) |  (PINL & 0b1100);
	int8_t va = QuadEnc(sens_A);
	int8_t vb = QuadEnc(sens_B);
	Map_update((float)va, -(float)vb);
	stepsA += /*(uint16_t)*/va;
	stepsB += /*(uint16_t)*/vb;
}


void rotationGet(int16_t* spA, int16_t* spB)
{
	uint8_t tmp = TIMSK0;   // ISR, die dieselben Daten
	TIMSK0 &= ~(1<<OCIE0A); // bearbeitet sperren
	*spA = stepsA;         // Ergebnisse kopieren
	*spB = stepsB;
	TIMSK0	= tmp;          // Interrupts wieder freigeben

}
void engineInit()
{
	pwm_init();
	rotation_init();
}

//uint8_t left, right;
//int16_t diffLeft, diffRight;
//uint16_t stepsA, stepsB;
void engineStart()
{
	pwm_start();
	left = 0;
	right = 0;
	diffLeft = 0;
	diffRight = 0;
	stepsA = 0;
	stepsB = 0;
}
void engineStop()
{
	pwm_stop();
}
void engineStep()
{
	int16_t stepsleft, stepsright;
	int32_t pwmLeft, pwmRight;
	
	rotationGet(&stepsleft, &stepsright);
	clearCounter();
	
	if(left == 0 && right == 0)
	{
		// abort correction
		pwm_set_A(0);
		pwm_set_B(0);
	}
	else
	{
		diffLeft += ((int16_t)left - stepsleft);
		diffRight += ((int16_t)right + stepsright);
	
		static const int16_t PWMSPEED = 200;
		const int16_t PWMLIMIT = 0x2000 / PWMSPEED;
	
		diffLeft = clamp(diffLeft,-PWMLIMIT,PWMLIMIT);
		diffRight = clamp(diffRight,-PWMLIMIT,PWMLIMIT);
	
		pwmLeft = diffLeft * PWMSPEED;
		pwmRight = diffRight * PWMSPEED;
	
		pwmLeft = clamp(pwmLeft,-MAXPWM, MAXPWM);
		pwmRight = clamp(pwmRight,-MAXPWM, MAXPWM);
	
		pwm_set_A(pwmLeft);
		pwm_set_B(-pwmRight);	
	}
}