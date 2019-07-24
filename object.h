#ifndef OBJECT
#define OBJECT

class object
{
protected:
	double posX;
	double posY;
	double velX;
	double velY;
public:

	double getX() { return posX;}
	double getY() { return posY;}

	virtual void draw()= 0;
	virtual void update()=0;
	virtual void loadTexture() = 0;
};
#endif