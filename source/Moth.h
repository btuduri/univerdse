#pragma once

class Moth
{
public:
	Moth(void);
	~Moth(void);
	float X;
	float Y;
	float Z;
	float vX;
	float vY;
	float vZ;
	float radius;
	void init(void);
	void move(void);
	bool isColliding(float,float,float);
};
