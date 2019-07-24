#include "misc.h"
#include <sl.h>
#include "global.h"
#include <cstdlib>

misc::misc(double x,double y,double v)
{
	posX=x;
	posY=y;
	velY=v;
};

void misc::loadTexture()
{
	MiscTex = slLoadTexture(TEX_TREE);
}

void misc::loadTextureCoins()
{
	MiscTexCoins=slLoadTexture(TEX_COINS);
}

void misc::loadTextureGasoline()
{
	MiscTexGasoline=slLoadTexture(TEX_GASOLINE);
}

void misc::draw()
{
	slSprite(MiscTex,posX,posY,100,100);
}

void misc::drawcoins()
{
	slSprite(MiscTexCoins,posX,posY,40,40);
}

void misc::drawgasoline()
{
	slSprite(MiscTexGasoline,posX,posY,40,40);
}

void misc::update()
{
	posY+=misc_spd;
	if(posY <= -40)
		{
			reset();
		}	
}
void misc::updatecoins()
{
	posY+=misc_spd;
	if(posY <= -40)
		{
			resetCoins();
		}	
}

void misc::updategasoline()
{
	posY+=misc_spd;
	if(posY <= -40)
		{
			resetGasoline();
		}	
}

void misc::setMiscSpd(double s)
{
	misc_spd=s;
}

void misc::reset()
{
	posY=700;
	int arr[]={365,30};
	int ran=rand() % 2 ;
	posX=arr[ran];
}	

void misc::resetCoins()
{
	int arr[]={100,132,200,245};
	int ran=rand() % 4 ;
	posY=2000;
	posX=arr[ran];
}

void misc::resetGasoline()
{
	int arr[]={100,132,200,245};
	int ran=rand() % 4 ;
	posY=3000;
	posX=arr[ran];
}

