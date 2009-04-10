#pragma once
typedef struct{
	int life;
	char message[];
} slot;

class Console3d
{
public:
	Console3d(void);
	~Console3d(void);

	slot messages[];

	void refresh(void);
};
