#include "Moth.h"
#include <PA9.h> 
Moth::Moth(void)
{
	X = (float)PA_RandMax(50)/100;
	Y = (float)PA_RandMax(50)/100;
	Z = (float)PA_RandMax(50)/100;
	vX = (float)PA_RandMax(50)/100;
	vY = (float)PA_RandMax(50)/100;
	vZ = (float)PA_RandMax(50)/100;
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
