#pragma once

class Ruin
{
public:
	Ruin(void);
	~Ruin(void);
	float X;
	float Y;
	float Z;
	float vX;
	float vY;
	float vZ;
	float radius;
	
	bool isColliding(float,float,float);
};
