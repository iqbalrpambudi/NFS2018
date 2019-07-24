#include "object.h"
#include "truck.h"
#include "global.h"
#include <sl.h>
#include <cstdlib>


truck::truck(double px,double py,double vx)
{
	posX=px;
	posY=py;
	velX=vx;
}

void truck::loadTexture()
{
	texture = slLoadTexture(TEX_TRUCK);
}

void truck::draw()
{
	slSprite(texture,posX,posY,50,85);
}

void truck::update()
{
	posY+=truck_spd;
	if(posY <= -40)
		{
			reset();
			truck_spd-=0.2;
		}	
}

//fungsi untuk reset posisi truk
void truck::reset()
{
	int arr[]={66,132,200,266};
	int random;
	random=rand() % 4 ;
	posY=700;
	posX=arr[random];
}

void truck::setTruckSpd(double s)
{
	truck_spd=s;
}