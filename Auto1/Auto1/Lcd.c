/*
 * comir_lcd.c
 *
 * Created: 11.01.2016 17:42:50
 *  Author: tiws-16-12
 */ 
#include "Lcd.h"
#include <avr/interrupt.h>
#include <string.h>

// globale private Daten
uint8_t LCD_dat[32];  // Ausgabetext
uint8_t lcd_idx;      // Indexvariable

void Lcd_init(char *text){ // LCD-Treiber initialisieren
	UCSR1C = 0b110;             // Übertragungsformat 8N1
	UBRR1 = 51;                 // 9600 Baud
	UCSR1B = (1<<TXEN1);	      // Sender ein
	
	// 8 Zeichen LC-Display-Initialisierung
	uint8_t lcd_init_dat[] = "\x1B[0h\x1B[j";
	for (lcd_idx=0; lcd_idx<7; lcd_idx++){
		while (!(UCSR1A&(1<<UDRE1)));
		UDR1 = lcd_init_dat[lcd_idx];
	}
	// Initialisierung des Hintergrundtextes
	//for (lcd_idx=0; lcd_idx<32; lcd_idx++) // Übernahme des
	//LCD_dat[lcd_idx] = text[lcd_idx];    // Init.-Texts
	uint8_t len = strlen(text);
	if(len < 32)
	{
		memset(LCD_dat,' ',32);
		memcpy(LCD_dat,text,len);
	}
	else // >= 32
	{
		memcpy(LCD_dat,text,32);
	}
	
	lcd_idx = 0;                   // Index auf Feldanfang

	UCSR1B |= (1<<UDRIE1);         // Puffer-frei-Interrupt ein
}

void Lcd_clear()
{
	memset(LCD_dat,' ',32);
}

ISR(USART1_UDRE_vect){	         // Puffer-frei ISR
	UDR1 = LCD_dat[lcd_idx];       // schicke nächstes
	lcd_idx++;                     // Zeichen
	// nach dem letzten folgt das erste Zeichen
	if (lcd_idx>=32) lcd_idx = 0;
}

// Zeichen auf LCD ausgeben
void Lcd_dispChr(uint8_t c, uint8_t pos){
	if (pos<0x20){                // bei zulässiger Position
		LCD_dat[pos & 0x1F] = c;    // Zeichen schreiben
	}
}

RESULT Lcd_dispText(uint8_t pos, char* txt)
{
	uint8_t len = 0;
	while(*txt != 0)
	{
		Lcd_dispChr(*txt,pos);
		pos++;
		txt++;
		len++;
		if(len > 32)
			return R_STRING_TO_LONG;
	}
	return R_OK;
}



// Zahl auf LCD ausgeben
RESULT Lcd_dispVal(int16_t num, uint8_t pos, uint8_t maxLen){
	/*
	int32_t temp = val;
	const uint8_t stdlen = len;
	if(temp < 0)
		temp *= -1;
	while (len && temp > 0){
		len--;                    // Ziffernanzahl verringern
		Lcd_dispChr((temp % 10) + '0', pos+len); // Rest mod 10
		temp = temp / 10;           // Ziffer und Wert durch 10
	}
	if(val < 0)
	{
		len--;
		Lcd_dispChr('-', pos+len);
	}
	while (len > 0){
		len--;
		Lcd_dispChr(' ', pos+len);
	}
	if(val == 0)
		Lcd_dispChr('0', pos+stdlen);
	//if (val)                    // wenn Stellenzahl zu klein,
	//lcd_disp_chr('?', pos);     // Ersatz 1. Ziffer durch '?'
	
	*/
	if(pos + maxLen > 32 ) return R_INVALID_PARAM;
	if(maxLen == 0) return R_INVALID_PARAM;
	
	//convert number to string
	char buffer[36]; //long enough for 32 bit
	itoa(num,buffer,10);
	uint8_t len = strlen(buffer);
	if(len > maxLen)
	{
		buffer[maxLen - 1] = '?'; //number too long
	}
	else if(len < maxLen)
	{
		//overwrite with spaces
		memset(LCD_dat + pos,' ',maxLen - len);
		pos += maxLen - len; //alignment right
	}
	
	//copy to lcdline
	memcpy(LCD_dat + pos, buffer, min(maxLen,len));
	return R_OK;
}

// ISR zur Behandlung ungewollter Interrupts
//ISR(BADISR_vect){            // Fehlerzäher (letztes
//	lcd_incErr(31);            // Zeichen) hochzählen
//}