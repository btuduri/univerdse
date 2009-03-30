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
	void init(void);
	void move(void);
};
