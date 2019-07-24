#ifndef TRUCK
#define TRUCK
#include "object.h"

class truck:public object
{
private:
	int texture;
	double truck_spd;
public:
	truck(double px,double py,double vx);
	void draw();
	void update();
	void reset();
	void loadTexture()override;
	void setTruckSpd(double s);
};
#endif