#pragma once

#include "captions.h"
#include "efs_lib.h"
//#include <fat.h>
#define TOP 1
#define TOUCH 0

#define _PLAYER "X"
#define _NPC01 "Elke"


#define STOP_HERE while(1)\
{PA_WaitForVBL();}

#define _BGBLUE 0
#define _BGTITLE 1
#define _BGOPTIONS 2
#define _CASTLE1 101
#define _CASTLE2 102
#define _WOOD1 103
#define _WOOD2 104
#define _WOOD3 105
#define _TOWN 106
#define _LIVINGROOM 107
#define _BOOKDESK 108
#define _BOOKPG1 109
#define _ENVELOPE 110
#define _PAINTING_LR 111
#define _STUDYDOOR 112
#define _STUDYLARGE 113
#define _STUDY 114
#define _STUDYPAINT 115
#define _STUDYBOOKS 116
#define _CORRIDOR 117

#define _LOCKPUZZLE 401

#define _LAURA 801

#define _TITLE 1000
#define _WHITE 2000
#define _BLACK 2001
#define _MAP 3000


typedef struct{
	int map;
} inventory;

typedef struct{
	int	place;				// status
	char	name[10];			// name
} savedata;

enum STATUS 
{	
	START = 0,
	INTRO_PRE,
	INTRO_POST,
	CHAP_1_PRE,
	CHAP_1_POST,
	CHAP_2_PRE,
	CHAP_2_POST,
	CHAP_3_PRE,
	CHAP_3_POST,
	CHAP_4_PRE,
	CHAP_4_POST,
	CHAP_5_PRE,
	CHAP_5_POST,
	CHAP_6_PRE,
	CHAP_6_POST,
	END_1,
	END_2,
	END_3,
	CREDITS
};

class glitchTools
{
public:
	glitchTools(void);

	~glitchTools(void);

	int ChoiceButtons(char *choices[], int nButtons);
	int SaveData(int stage, int score);
	void SlowType(char text[]);
	int SlowIntroType(char text[]);
	void PrintCredits(char credit[]);
	void SlowQuote(char text[], char name[]);

	void SlpThrd(int frames);
	int SlpIntroThrd(int frames);


	void LoadTopBackground(int bgN);

	void LoadTouchBackground(int bgN);
	void loadBackground(int screen, int bg);
	void LoadNPCSprite(int spriteNum);
	void LoadNoise();
	
	void LoadIntro();
	void UnLoadNPCSprite(int spriteNum);
	void EraseButtons(int num);
	void InputToContinue();
	void showMap();
	void showSave();
	void showOptions();
	void LoadPuzzle();
	inventory inv;
	savedata sav;
	STATUS status;
	void fadeIn(int screen, int duration);
	void fadeOut(int screen, int duration);
	
};
