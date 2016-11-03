/*
 * Bit.h
 *
 * Created: 02.11.2015 16:05:53
 *  Author: tiws-16-11
 */ 


#ifndef _BIT_H_
#define _BIT_H_

#define LOOP(max) for(uint32_t i = 0; i < max; ++i)

uint8_t GetBit(uint32_t src, uint8_t bit);
uint32_t SetBit(uint32_t src, uint8_t bit, uint8_t val);

#endif /* BIT_H_ */