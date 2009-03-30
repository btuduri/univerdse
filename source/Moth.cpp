#include "Moth.h"
#include <PA9.h> 
#include <math.h>
Moth::Moth(void)
{
	X = 0;//(float)(PA_RandMax(50) - 25)/100;
	Y = 0;//(float)(PA_RandMax(50) - 25)/100;
	Z = 0;//(float)(PA_RandMax(50) - 25)/100;
	vX = (float)(PA_RandMax(50))/300;
	vY = (float)(PA_RandMax(50))/300;
	vZ = (float)(PA_RandMax(50))/300;
}

Moth::~Moth(void)
{
}

void Moth::init(void)
{
	this->X = PA_RandMax(50)/1;
	this->Y = PA_RandMax(50)/1;
	this->Z = PA_RandMax(50)/1;
	this->vX = PA_RandMax(50)/100;
	this->vY = PA_RandMax(50)/100;
	this->vZ = PA_RandMax(50)/100;
}
void Moth::move(void)
{
	X += vX;
	Y += vY;
	Z += vZ;
	if(X>=5.0 || X<-5)
		vX = -vX;
	if(Y>=5.0 || Y<-5)
		vY = -vY;
	if(Z>=5.0 || Z<-5)
		vZ = -vZ;
}
