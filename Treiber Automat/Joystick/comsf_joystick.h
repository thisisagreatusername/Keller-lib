/*
 * comsf_joystick.h
 *
 * Created: 30.11.2015 17:41:44
 *  Author: tiws-16-4
 */ 


#ifndef COMSF_JOYSTICK_H_
#define COMSF_JOYSTICK_H_

#include <avr/io.h>

void joystick_init(uint8_t deadzone);
void joystick_step();
//0 = no change, 2 = +x, 3 = -x, 4 = +y, 5= -y
void joystick_enable_gen_xy_change(uint8_t x);
uint8_t joystick_get_xy_change(); 
uint16_t joystick_get_x_val();
uint16_t joystick_get_y_val();
uint8_t joystick_get_buttons_val();


#endif /* COMSF_JOYSTICK_H_ */