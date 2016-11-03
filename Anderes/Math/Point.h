/*
 * Point.h
 *
 * Created: 01.02.2016 19:37:35
 *  Author: tiws-16-11
 */ 


#ifndef POINT_H_
#define POINT_H_

typedef struct 
{
	float x,y;
} Point;

Point pt_add(Point a, Point b);
Point pt_scale(Point a, float s);

// rotation
Point pt_CW90(Point a);
Point pt_CCW90(Point a);

//normalize
Point pt_norm(Point a);
float pt_length(Point a);

#endif /* POINT_H_ */