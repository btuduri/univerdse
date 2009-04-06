#include "Ruin.h"
#include <PA9.h> 
#include <math.h>
Ruin::Ruin(void)
{
	X = 0;//(float)(PA_RandMax(50) - 25)/100;
	Y = 0;//(float)(PA_RandMax(50) - 25)/100;
	Z = 0;//(float)(PA_RandMax(50) - 25)/100;
	X = (float)(PA_RandMax(50))/50;
	Y = (float)(PA_RandMax(50))/50;
	Z = (float)(PA_RandMax(50))/50;
	vX = (float)(PA_RandMax(50))/300;
	vY = (float)(PA_RandMax(50))/300;
	vZ = (float)(PA_RandMax(50))/300;

	radius = 1;
}

Ruin::~Ruin(void)
{
}



bool Ruin::isColliding(float x, float y, float z)
{
	float distance = sqrt(pow(X-x,2) + pow(Y-y,2) + pow(Z-z,2));
	return (distance < radius);

}
