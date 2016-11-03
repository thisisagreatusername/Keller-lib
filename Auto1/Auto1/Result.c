/*
 * Result.c
 *
 * Created: 23.11.2015 16:03:48
 *  Author: tiws-16-11
 */ 
#include <avr/io.h>
#include "Result.h"
#include "Lcd.h"

char res_errbuff[50];

const char* getErrDesc(RESULT r)
{
	res_errbuff[0] = '\0';
	
	switch(r)
	{
		case R_OK:
		strcpy(res_errbuff,"OK");
		break;
		
		case R_M_NOT_INIT:
		strcpy(res_errbuff,"modul not initialized");
		break;
		
		case R_NULL:
		strcpy(res_errbuff,"pointer to NULL");
		break;
		
		case R_BUFF_NOT_READY:
		strcpy(res_errbuff,"buffer not ready");
		break;
		
		case R_INVALID_PARAM:
		strcpy(res_errbuff,"invalid parameters");
		break;
		
		case R_TIMEOUT:
		strcpy(res_errbuff,"timeout");
		break;
		
		case R_ALREADY_INIT:
		strcpy(res_errbuff,"modul already init");
		break;
		
		case R_STRING_TO_LONG:
		strcpy(res_errbuff,"string to long");
		break;
		
		case R_ENGINE_ERROR:
		strcpy(res_errbuff,"engine failure");
		break;
		
		default:
		strcpy(res_errbuff,"unknown");
		break;
	}
	return res_errbuff;
}

void SetError(RESULT res)
{
	Lcd_clear();
	const char* desc = getErrDesc(res);
	Lcd_dispText(0,"Error: ");
	Lcd_dispText(8,desc);
}