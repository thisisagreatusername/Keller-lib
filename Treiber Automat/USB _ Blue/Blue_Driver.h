/*
 * Blue_Driver.h
 *
 * Created: 30.11.2015 18:21:38
 *  Author: tiws-16-12
 */ 


#ifndef BLUE_DRIVER_H_
#define BLUE_DRIVER_H_
#include <avr/io.h>
void blue_init();
uint8_t blue_get(uint8_t *msg);
uint8_t blue_send(uint8_t *msg);
uint8_t blue_step();

#endif /* BLUE_DRIVER_H_ */