/*
 * Lcd.h
 *
 * Created: 16.11.2015 17:27:45
 *  Author: tiws-16-11
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "Result.h"

void Lcd_init(const char* initTxt);
RESULT Lcd_step();
RESULT Lcd_dispChar(char c, uint8_t pos);

// num = Number | pos = start position | maxLen = max display length
RESULT Lcd_dispNum(int16_t num, uint8_t pos, uint8_t maxLen);
RESULT Lcd_dispString(const char* txt, uint8_t pos);

#endif /* LCD_H_ */