/*
 * Map.h
 *
 * Created: 01.02.2016 22:27:05
 *  Author: tiws-16-10
 */ 


#ifndef MAP_H_
#define MAP_H_

#include <avr/io.h>
#include "Point.h"

void Map_init();
void Map_update(float left, float right);
Point Map_getPos();
PointI_16 Map_getSmallPos();
Point Map_getDir();

#endif /* MAP_H_ */