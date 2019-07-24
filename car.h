#ifndef CAR
#define CAR

#include "object.h"

class Car: public object
{
private:
	int texture;
public:
	Car(double px,double py);
	void draw();
	void update();
	void control(double cx);
	void loadTexture();
};
#endif