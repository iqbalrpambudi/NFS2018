#ifndef MISC
#define MISC

#include "object.h"

class misc:public object
{
private:
	double misc_spd;
	int MiscTexCoins;
	int MiscTex;
	int MiscTexGasoline;
public:
	misc(double x,double y,double v);
	void draw();
	void drawcoins();
	void drawgasoline();
	void update();
	void updatecoins();
	void updategasoline();
	void reset();
	void resetCoins();
	void resetGasoline();
	void loadTexture()override;
	void loadTextureCoins();
	void loadTextureGasoline();
	void setMiscSpd(double s);
};



#endif