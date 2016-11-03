/*
 * Point.c
 *
 * Created: 01.02.2016 19:37:47
 *  Author: tiws-16-11
 */ 
#include <math.h>
#include "Point.h"

inline Point pt_add(Point a, Point b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}
inline Point pt_scale(Point a, float s)
{
	a.x *= s;
	a.y *= s;
	return a;
}

// rotation
inline Point pt_CW90(Point a)
{
	Point b;
	b.x = a.y;
	b.y = -a.x;
	return b;
}
inline Point pt_CCW90(Point a)
{
	Point b;
	b.x = -a.y;
	b.y = a.x;
	return b;
}

inline float sqrtfast(float val)
{
	float seed = val;
	for(uint8_t i = 0; i < 15; i++)
	{
		seed = (val / seed + seed) / 2.0f;
	}
	return seed;
}
inline float pt_lengthSq(Point a)
{
	return a.x * a.x + a.y * a.y;
}
//normalize
inline Point pt_norm(Point a)
{
	//return pt_scale(a,1.0f / pt_length(a));
	float len = pt_length(a);
	//if(len != 0.0f)
	//{
		a.x /= len;
		a.y /= len;
		return a;
	/*}
	else
	{
		Point b;
		b.x = 0.0f;
		b.y = 1.0f;
		return b;
	}*/
}

inline float pt_length(Point a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
	//return sqrtfast(a.x * a.x + a.y * a.y);
}

inline Point pt_rot(Point a, float angle)
{
	float cosa = cosf(angle);
	float sina = sinf(angle);
	
	Point res;
	res.x = a.x * cosa - a.y * sina;
	res.y = a.x * sina + a.y * cosa;
	return res;
}