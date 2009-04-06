#pragma once
typedef struct{
	u8 life
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
