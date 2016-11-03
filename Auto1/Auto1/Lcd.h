/*
 * comir_lcd.h
 *
 * Created: 11.01.2016 17:42:18
 *  Author: tiws-16-12
 */ 


#ifndef COMIR_LCD_H_
#define COMIR_LCD_H_


#include <avr/io.h>
#include "Result.h"

void Lcd_init(char *text); // LCD-Objekt initialisieren
void Lcd_clear();
// Zeichen auf LCD ausgeben
void Lcd_dispChr(uint8_t c, uint8_t pos);
// Text auf LCD ausgeben
RESULT Lcd_dispText(uint8_t pos, char* txt);
// Zahl auf LCD ausgeben
RESULT Lcd_dispVal(int16_t val, uint8_t pos, uint8_t len);



#endif /* COMIR_LCD_H_ */