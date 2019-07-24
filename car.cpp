#include "car.h"
#include "object.h"
#include "sl.h"
#include "global.h"
//#include "game.h"


Car::Car(double px,double py)
{
	posX=px;
	posY=py;
}

void Car::loadTexture()
{	
		texture = slLoadTexture(TEX_CAR);	
}

void Car::draw()
{
	slSprite(texture,posX,posY,50,85);
}

void Car::update()
{
	posX+=velX;
	if(posX-23 <=30 || posX+20 >=360)
		velX*=-0.5;
}

void Car::control(double cx)
{
	velX+=cx;
}