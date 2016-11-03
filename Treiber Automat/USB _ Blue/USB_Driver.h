/*
 * USB_Driver.h
 *
 * Created: 30.11.2015 18:03:30
 *  Author: tiws-16-12
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#include <avr/io.h>
void usb_init();
uint8_t usb_get(uint8_t *msg);
uint8_t usb_send(uint8_t *msg);
uint8_t usb_step();

#endif /* INCFILE1_H_ */