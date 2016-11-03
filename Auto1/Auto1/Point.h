/*
 * Point.h
 *
 * Created: 01.02.2016 19:37:35
 *  Author: tiws-16-11
 */ 


#ifndef POINT_H_
#define POINT_H_
#include <avr/io.h>

typedef struct 
{
	float x,y;
} Point;

typedef struct
{
	int16_t x,y;
} PointI_16;

extern Point pt_add(Point a, Point b);
extern Point pt_scale(Point a, float s);

// rotation
extern Point pt_CW90(Point a);
extern Point pt_CCW90(Point a);

//normalize
extern Point pt_norm(Point a);
extern float pt_length(Point a);
extern Point pt_rot(Point a, float angle);
extern float pt_lengthSq(Point a);

#endif /* POINT_H_ */