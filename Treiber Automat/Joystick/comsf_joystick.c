/*
 * comsf_joystick.c
 *
 * Created: 30.11.2015 17:41:10
 *  Author: tiws-16-4
 */ 
#include "comsf_joystick.h"

uint8_t led_dat = 0;
uint8_t joy_idx = 6;
uint8_t joy_dat[5];
uint8_t deadzone = 0;
uint8_t xy_change = 0;
uint8_t enable_gen_xy_change = 0;

void joystick_init(uint8_t dz){
	deadzone = dz;
	DDRB = 0xf7;
	PORTB |= 0x1;
	SPCR = (1<<SPE)|(1<<MSTR)|(0b11<<SPR0);
}

void joystick_step(){
	switch(joy_idx){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			if(SPSR & (1<<SPIF)){
				joy_dat[joy_idx] = SPDR;
				if(joy_idx<4) SPDR = 0;
				joy_idx++;
			}			
			break;
			
		case 5: //end
			PORTB |= 1;
			joy_idx++;
			
			if(enable_gen_xy_change)
				joystick_generate_xy_change();
			break;
		
		case 6: //start
			PORTB &=~1;			
			SPDR = 0b10000000 | (led_dat & 0b11);
			joy_idx = 0;
			break;
		
		default:
			break;
	}
}

void joystick_enable_gen_xy_change(uint8_t x){
	enable_gen_xy_change = x;
}

void joystick_generate_xy_change(){
	if(joystick_get_x_val() > (512 + deadzone))
		xy_change = 2;
	if(joystick_get_x_val() < (512 - deadzone))
		xy_change = 3;
	if(joystick_get_y_val() > (512 + deadzone))
		xy_change = 4;
	if(joystick_get_y_val() < (512 - deadzone))
		xy_change = 5;
}

uint8_t joystick_get_xy_change(){
	uint8_t xyc = xy_change;
	xy_change = 0;
	return xyc;
}

uint16_t joystick_get_x_val(){
	return *(uint16_t*)(joy_dat);
}

uint16_t joystick_get_y_val(){
	return *(uint16_t*)(joy_dat + 2);
}

uint8_t joystick_get_buttons_val(){
	return joy_dat[4];
}