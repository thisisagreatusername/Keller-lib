/*
 * Map.c
 *
 * Created: 01.02.2016 22:27:20
 *  Author: tiws-16-10
 */ 
#include "Map.h"
#include "Result.h"
#include "Point.h"
#include "Led.h"

/*
#define multvorne 0.9346
#define multseite 0.00514
#define rotangle 0.005499623559444234f
#define rotangle2 (rotangle * 2.0f)
*/

typedef Point Vector;
Point position = {0, 0};
Vector direction = {0, 1};

//#define VX	0.0929370203f
//#define VY	0.000258603491f
//#define W 0.0929375f

#define VX	0.1858711623f / 2.0f
#define VY	0.001034406f / 2.0f
#define W 0.185875f

void Map_init()
{
	position.x = 0.0;
	position.y = 0.0;
	direction.x = 0.0;
	direction.y = 1.0;
}



void Map_update(float left, float right)
{
	Vector v;
	if(left == right)
	{
		if(left == 0.0f)
			return;
			
		if(left == 1.0f)
		{
			// both forward
			v = pt_scale(direction,W);
			position = pt_add(position,v);
		}
		else
		{
			// both backward
			v = pt_scale(direction,-W);
			position = pt_add(position,v);
		}
	}
	else
	{
		// left != right
		if( left * right == -1.0f)
		{
			// auf der stell
			if(right == 1.0f)
			{
				/*
				v = pt_add(
				pt_scale(direction,VX), // x part
				pt_scale(pt_CCW90(direction),VY)); // y part
				//position = pt_add(position,v);
				direction = pt_norm(v);
				v = pt_add(
				pt_scale(direction,VX), // x part
				pt_scale(pt_CCW90(direction),VY)); // y part
				direction = pt_norm(v);
				*/
				// right 1
				v = pt_add(
				pt_scale(direction,VX), // x part
				pt_scale(pt_CCW90(direction),VY)); // y part
				//position = pt_add(position,v);
				direction = pt_norm(v);
				
				/*
				// left - 1 
				v = pt_add(
				pt_scale(direction,VX), // x part
				pt_scale(pt_CCW90(direction),VY)); // y part
				
				direction = pt_norm(v);
				*/
				//v = pt_scale(v,-1.0f);
				//position = pt_add(position,v);
			}
			else
			{	
				/*
				// right -1 
				v = pt_add(
				pt_scale(direction,VX), // x part
				pt_scale(pt_CW90(direction),VY)); // y part
				
				direction = pt_norm(v);
				//v = pt_scale(v,-1.0f);
				//position = pt_add(position,v);
				*/
				
				// left +1
				v = pt_add(
				pt_scale(direction,VX), // x part
				pt_scale(pt_CW90(direction),VY)); // y part
				//position = pt_add(position,v);
				direction = pt_norm(v);
			}
			
		}
		else if(left != 0.0f)
		{
			// left wheel
			if(left == 1.0f)
			{
				v = pt_add(
				pt_scale(direction,VX), // x part
				pt_scale(pt_CW90(direction),VY)); // y part
				position = pt_add(position,v);
				direction = pt_norm(v);
			}
			else
			{
				// right forward
				v = pt_add(
				pt_scale(direction,VX), // x part
				pt_scale(pt_CCW90(direction),VY)); // y part
				
				direction = pt_norm(v);
				
				v = pt_scale(v,-1.0f);
				position = pt_add(position,v);
			}
		}
		else
		{
			// right wheel
			if(right == 1.0f)
			{
				v = pt_add(
				pt_scale(direction,VX), // x part
				pt_scale(pt_CCW90(direction),VY)); // y part
				position = pt_add(position,v);
				direction = pt_norm(v);
			}
			else
			{
				// left forward
				v = pt_add(
				pt_scale(direction,VX), // x part
				pt_scale(pt_CW90(direction),VY)); // y part
				
				direction = pt_norm(v);
				v = pt_scale(v,-1.0f);
				position = pt_add(position,v);
			}
		}
	}
}

Point Map_getPos()
{
	return position;
}

Point Map_getDir()
{
	return pt_norm(direction);
}

PointI_16 Map_getSmallPos()
{
	static const int16_t divider = 2;
	
	PointI_16 res;
	res.x = (int16_t)(position.x + 0.5f);
	res.y = (int16_t)(position.y + 0.5f);
	res.x /= divider;
	res.y /= divider;
	return res;
}