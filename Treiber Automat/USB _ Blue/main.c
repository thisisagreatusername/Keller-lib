/*
 * USB_Driver.c
 *
 * Created: 30.11.2015 18:02:59
 * Author : tiws-16-12
 */ 

#include <avr/io.h>
#include "USB_Driver.h"

int main(void)
{
    uint8_t msg;
	uint8_t step = 1;
	usb_init();
    while (1) 
    {
		usb_step();

		switch (step)
		{
			case 1:
				if(usb_get(&msg))
					step = 2;
				break;
			case 2:
				if(usb_send(&msg))
					step = 1;
				break;
		}
    }
}

