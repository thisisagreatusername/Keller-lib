/*
 * Ser.h
 *
 * Created: 21.01.2016 01:36:01
 *  Author: Henrik
 */ 


#ifndef SER_H_
#define SER_H_

#include "Kodierer.h"

RESULT Ser_init_pc();	//PC Kommunikation via Kabel initialisieren
uint8_t ser_get();		//zuletzt empfangene Nachricht auslesen
RESULT Ser_send(uint8_t code, uint2_t typ);	//Nachricht zum senden übergeben


#endif /* SER_H_ */