/*
 * Lcd.c
 *
 * Created: 16.11.2015 17:37:09
 *  Author: tiws-16-11
 */ 
#include <avr/io.h>
#include "Lcd.h"
#include <string.h>

BOOL lcdIsInit = FALSE;
uint8_t lcdLine[32];

uint8_t lcdCounter = 0;

void Lcd_init(const char* initTxt)
{
	if(lcdIsInit) return;
	 // Initialisierung von USART1
	 UCSR1C = 0b110;                  // Übertragungsformat 8N1
	 UBRR1  = 51;                     // 9600 Baud
	 UCSR1B |= (1<<TXEN1);             // Sender ein
	const char lcdInitString[] = "\x1B[0h\x1B[j";
	//send init string
	for(uint8_t i = 0; i < 7;i++)
	{
		while (!(UCSR1A&(1<<UDRE1)));  // warte, bis Puffer frei
		UDR1 = lcdInitString[i];
	}
	uint8_t len = 0;
	
	if(initTxt != NULL)
	{
			// copy init text
			len = strlen(initTxt);
			memcpy(lcdLine,initTxt,min(32,len));
	}
	
	if(len < 32)
	{
		memset(lcdLine + len,' ',32 - len);
	}
	
	for(uint8_t i = 0; i < 32; i++)
	{
		while (!(UCSR1A&(1<<UDRE1)));  // warte, bis Puffer frei
		UDR1 = initTxt[i];
	}
	
	lcdIsInit = TRUE;
}
RESULT Lcd_step()
{
	if(!lcdIsInit) return R_M_NOT_INIT;
	
	if((UCSR1A&(1<<UDRE1))) //Puffer frei
	{
		UDR1 = lcdLine[lcdCounter];
		lcdCounter = (++lcdCounter) % 32;
	}
	return R_OK;
}
RESULT Lcd_dispChar(char c, uint8_t pos)
{
	if(!lcdIsInit) return R_M_NOT_INIT;
	if(pos > 32 || c == 0) return R_INVALID_PARAM;
	
	lcdLine[pos] = c;
	return R_OK;
}

// num = Number | pos = start position | maxLen = max display length
RESULT Lcd_dispNum(int16_t num, uint8_t pos, uint8_t maxLen)
{
	if(!lcdIsInit) return R_M_NOT_INIT;
	if(pos + maxLen > 32 ) return R_INVALID_PARAM;
	if(maxLen == 0) return R_INVALID_PARAM;
	
	//convert number to string
	char buffer[10]; //long enough for 16 bit
	itoa(num,buffer,10);
	uint8_t len = strlen(buffer);
	if(len > maxLen)
	{
		buffer[maxLen - 1] = '?'; //number too long
	}
	else if(len < maxLen)
	{
		//overwrite with spaces
		memset(lcdLine + pos,' ',maxLen - len);
		pos += maxLen - len; //alignment right
	}
	
	//copy to lcdline
	memcpy(lcdLine + pos, buffer, min(maxLen,len));
	return R_OK;
}

RESULT Lcd_dispString(const char* txt, uint8_t pos)
{
	if(!lcdIsInit) return R_M_NOT_INIT;
	uint8_t len = strlen(txt);
	if(pos + len > 32) return R_INVALID_PARAM;
	if(txt == NULL) return R_OK;
	
	// copy to lcd line
	memcpy(lcdLine + pos, txt, len);
	return R_OK;
}