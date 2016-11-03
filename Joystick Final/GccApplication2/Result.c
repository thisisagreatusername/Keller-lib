/*
 * Result.c
 *
 * Created: 23.11.2015 16:03:48
 *  Author: tiws-16-11
 */ 
#include <avr/io.h>
#include "Result.h"
#include "Bit.h"

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
		
		default:
		strcpy(res_errbuff,"unknown");
		break;
	}
	return res_errbuff;
}