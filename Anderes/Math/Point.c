/*
 * Point.c
 *
 * Created: 01.02.2016 19:37:47
 *  Author: tiws-16-11
 */ 
#include <math.h>

Point pt_add(Point a, Point b)
{
	a.x + b.x;
	a.y += b.y;
	return a;
}
Point pt_scale(Point a, float s)
{
	a.x *= s;
	a.y *= s;
	return a;
}

// rotation
Point pt_CW90(Point a)
{
	Point b;
	b.x = a.y;
	b.y = -a.x;
}
Point pt_CCW90(Point a)
{
	Point b;
	b.x = -a.y;
	b.y = a.x;
}

//normalize
Point pt_norm(Point a)
{
	return pt_scale(a,1.0f / pt_length(a));
}
float pt_length(Point a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
}