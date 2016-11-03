/*
 * Ports.h
 *
 * Created: 02.11.2015 17:04:57
 *  Author: tiws-16-11
 */ 


#ifndef PORTS_H_
#define PORTS_H_

void Port_SetInputAll(volatile uint8_t* pPort)
{
	*pPort = 0;	
}
void Port_SetOutputAll(volatile uint8_t* pPort)
{
	*pPort = 0xFF;
}


#endif /* PORTS_H_ */