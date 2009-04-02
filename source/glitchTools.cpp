#include "glitchTools.h"
#include <PA9.h>       // Include for PA_Lib
#include "gfx/all_gfx.c"
#include "gfx/all_gfx.h"
#include "captions.h"

//sounds
/*
#include "blip.h"
#include "bleep.h"
#include "switchs.h"

*/


u8 wait =0;
glitchTools::glitchTools(void)
{
	//constructor
	/*PA_LoadNPCSpritePal(0, // Screen
			1, // Palette number
			(void*)arrow2_Pal);	// Palette name
	PA_CreateSprite(0, 1,(void*)arrow2_Sprite, OBJ_SIZE_8X16,1, 1, 238, 176);*/

	this->inv.map=0;
	//fatInitDefault();
}

glitchTools::~glitchTools(void)
{
	//destructor
}


int glitchTools::SaveData(int stage, int score)
{
	//PA_InitFat();
	char * data;
	sprintf(data, "%d %d", stage, score);
	//PA_WriteTextFile("moths.sav", data);


	return 0;
}

int glitchTools::ChoiceButtons(char *choices[], int nButtons)
{

	//PA_InitCustomText(0,0,aafontq);
	PA_InitText(TOUCH,0);
	
	for (int i=0;i<nButtons; i++)
	{
		//print the options from the last but 'nButtons', one per line
		PA_OutputText(0,1,(23-(nButtons-i)), choices[i]);
	}
	//to have nButtons<>0
	int g=nButtons+10;
	
	///CURSOR VERSION
	PA_LoadSpritePal(TOUCH, // Screen
			0, // Palette number
			(void*)cursor_Pal);	// Palette name
					
	PA_CreateSprite(TOUCH, // Screen
			0, // Sprite number
			(void*)cursor_Sprite, // Sprite name
			OBJ_SIZE_8X8, // Sprite size
			1, // 256 color mode
			0, // Sprite palette number
			0, (184-(8*nButtons))); // X and Y position on the screen
	int y =PA_GetSpriteY(0, 0);
	while (g==nButtons+10)
	{
		//if the user touches the screen...

		if (Stylus.Held)
		{
			//...and it's one of the last 'nButton' lines
			if(Stylus.Y>(184-(8*nButtons)))
			{
				//gets the index of the chosen line
				g=(Stylus.Y-(184-(8*nButtons)))/8;
				//PA_InitText(TOUCH,0);
				
			}
		}
		if(Pad.Newpress.Start&&inv.map)
			showMap();
		y += (Pad.Newpress.Down - Pad.Newpress.Up)*8;
		if(y<184-(8*nButtons))
		{
			y=184-(8*nButtons);
		}
		else if(y>176)
		{
			y=176;
		}
		else
		{
			PA_SetSpriteXY(0, 0, 0,	y);
		}
		if (Pad.Newpress.A)
			g=(PA_GetSpriteY(0, 0)-(184-(8*nButtons)))/8;
		PA_WaitForVBL();
	}
	PA_DeleteSprite(0,0);
	//AS_MP3DirectPlay((u8*)switchs, (u32)switchs_size);
	return g;
}

void glitchTools::EraseButtons( int num)
{
	for (int i=0; i<num; i++)
	{
		PA_OutputSimpleText(TOUCH,1,(22-i), "                                 ");
	}
}
void glitchTools::SlowType(char text[])
{
	wait=2;
	//initializes text on touch screen, bg layer 1
	PA_InitText(TOUCH,1);
	//PA_InitCustomText(TOUCH,1,aafontq);
	
    PA_SetTextCol(TOUCH,31,31,0);
	//prints the text one char per frame
	for (u32 i=0; i<=strlen(text); i++)
	{
		
		PA_BoxText(TOUCH,1,2,30,22,text,i);
		
		SlpThrd(wait);
	}

}

void glitchTools::SlowQuote(char text[], char name[])
{
	wait=0;
	//initializes text on touch screen, bg layer 1
	PA_InitText(TOUCH,1);
	//PA_InitCustomText(TOUCH,1,aafontq);
	//PA_SetTextCol(TOUCH,0,0,31);
	PA_OutputText(TOUCH,1,1,"- %s:",name);
    //PA_SetTextCol(TOUCH,31,0,0);
	//prints the text one char per frame
	for (u32 i=0; i<=strlen(text); i++)
	{
		//if(Stylus.Held||Pad.Newpress.A) wait=0;
		PA_BoxText(TOUCH,1,3,30,22,text,i);
		//AS_SoundQuickPlay(bleep);
//		AS_MP3DirectPlay((u8*)blip, (u32)blip_size);
		SlpThrd(wait);
	}

}

//sleeps for given frames
void glitchTools::SlpThrd(int frames)
{
	for (int i=0; i<=frames; i++)
		PA_WaitForVBL();
}


void glitchTools::LoadTouchBackground(int bgN)
{
	fadeOut(TOUCH, 1);
	loadBackground(0, bgN);
	fadeIn(TOUCH, 1);
}



void glitchTools::LoadTopBackground(int bgN)
{
	fadeOut(TOP, 1);
	loadBackground(1, bgN);
	fadeIn(TOP, 1);
}



void glitchTools::loadBackground(int screen, int bg)
{
/*	switch (bg)
	{
		case _BGBLUE:
			PA_EasyBgLoad(screen, 3, bgblue);
			break;
		case _CASTLE1:
			PA_EasyBgLoad(screen, 3, castle1);
			break;
		case _CASTLE2:
			PA_EasyBgLoad(screen, 3, castle2);
			break;
		case _WOOD1:
			PA_EasyBgLoad(screen, 3, radura1);
			break;
		case _WOOD2:
			PA_EasyBgLoad(screen, 3, radura2);
			break;
		case _WOOD3:
			PA_EasyBgLoad(screen, 3, radura3);
			break;
		case _TOWN:
			PA_EasyBgLoad(screen, 3, brattemberg);
			break;
		case _LIVINGROOM:
			PA_EasyBgLoad(screen, 3, salotto);
			break;
		case _BOOKDESK:
			PA_EasyBgLoad(screen, 3, bookdesk);
			break;
		case _BOOKPG1:
			PA_EasyBgLoad(screen, 3, bookpg1);
			break;
		case _ENVELOPE:
			PA_EasyBgLoad(screen, 3, envelope);
			break;
		case _WHITE:
			PA_EasyBgLoad(screen, 3, white);
			break;
		case _TITLE:
			PA_EasyBgLoad(screen, 3, title);
			break;
		case _MAP:
			PA_EasyBgLoad(screen, 3, map);
			break;
		case _STUDYDOOR:
			PA_EasyBgLoad(screen, 3, studydoor);
			break;
		case _PAINTING_LR:
			PA_EasyBgLoad(screen, 3, painting);
			break;
		case _STUDYLARGE:
			PA_EasyBgLoad(screen, 3, studylarge);
			break;
		case _STUDY:
			PA_EasyBgLoad(screen, 3, study);
			break;
		case _STUDYPAINT:
			PA_EasyBgLoad(screen, 3, studypaint);
			break;
		case _STUDYBOOKS:
			PA_EasyBgLoad(screen, 3, studybooks);
			break;
		case _BGTITLE:
			PA_EasyBgLoad(screen, 3, bgtitle);
			break;
		case _BGOPTIONS:
			PA_EasyBgLoad(screen, 3, bgoptions);
			break;
		case _BLACK:
			PA_EasyBgLoad(screen, 3, black);
			break;
		case _CORRIDOR:
			PA_EasyBgLoad(screen, 3, corridor);
			break;

		case _LOCKPUZZLE:
			PA_EasyBgLoad(screen, 3, lockpuzzle);
			break;


		case _LAURA:
			PA_EasyBgLoad(screen, 3, laura);
			break;
		case _MAD1:
			PA_EasyBgLoad(screen, 3, mad1);
			break;
		case _MAD2:
			PA_EasyBgLoad(screen, 3, mad2);
			break;
		case _MAD4:
			PA_EasyBgLoad(screen, 3, mad4);
			break;
		case _MAD5:
			PA_EasyBgLoad(screen, 3, mad5);
			break;

	}
*/
}
/*
void glitchTools::LoadNPCSprite(int spriteNum)
{
	
	PA_EasyBgLoad(1, 2, laura);
}


void glitchTools::LoadPuzzle()
{
	LoadTouchBackground(_LOCKPUZZLE);
	PA_LoadSpritePal(0, // Screen
			1, // Palette number
			(void*)puzzlepiece1_Pal);	// Palette name
	PA_CreateSprite(0, // Screen
			1, // Sprite number
			(void*)puzzlepiece1_Sprite, // Sprite name
			OBJ_SIZE_32X64, // Sprite size
			1, // 256 color mode
			1, // Sprite palette number
			10, 120); // X and Y position on the screen


	PA_LoadSpritePal(0, 2, (void*)puzzlepiece2_Pal);
	PA_CreateSprite(0, 2, (void*)puzzlepiece2_Sprite, OBJ_SIZE_64X32, 1, 2,	90, 120);
	PA_LoadSpritePal(0, 3, (void*)puzzlepiece3_Pal);
	PA_CreateSprite(0, 3, (void*)puzzlepiece3_Sprite, OBJ_SIZE_32X64, 1, 3,	160, 120);
	PA_LoadSpritePal(0, 4, (void*)puzzlepiece4_Pal);
	PA_CreateSprite(0, 4, (void*)puzzlepiece4_Sprite, OBJ_SIZE_32X32, 1, 4,	200, 120);

	u8 p1 =0;
	u8 p2 =0;
	u8 p3 =0;
	u8 p4 =0;

	while(1)
	{
		if (!p1) PA_MoveSprite(1);
		if (!p2) PA_MoveSprite(2);
		if (!p3) PA_MoveSprite(3);
		if (!p4) PA_MoveSprite(4);

		if (PA_GetSpriteX(0,1)<55 && PA_GetSpriteX(0,1)>45 && PA_GetSpriteY(0,1)<38 && PA_GetSpriteY(0,1)>28)
		{
			PA_SetSpriteX(0,1,50);
			PA_SetSpriteY(0,1,33);
			p1=1;
		}
		if (PA_GetSpriteX(0,2)<71 && PA_GetSpriteX(0,2)>61 && PA_GetSpriteY(0,2)<70 && PA_GetSpriteY(0,2)>60)
		{
			PA_SetSpriteX(0,2,66);
			PA_SetSpriteY(0,2,65);
			p2=1;
		}
		if (PA_GetSpriteX(0,3)<87 && PA_GetSpriteX(0,3)>77 && PA_GetSpriteY(0,3)<38 && PA_GetSpriteY(0,3)>28)
		{
			PA_SetSpriteX(0,3,82);
			PA_SetSpriteY(0,3,33);
			p3 =1;
		}
		if (PA_GetSpriteX(0,4)<71 && PA_GetSpriteX(0,4)>61 && PA_GetSpriteY(0,4)<38 && PA_GetSpriteY(0,4)>28)
		{
			PA_SetSpriteX(0,4,66);
			PA_SetSpriteY(0,4,33);
			p4=1;
		}
		//PA_OutputText(0,1,1,"- %d   ",PA_GetSpriteX(0,2));
		if (p1&&p2&&p3&&p4)
			PA_OutputText(0,1,1,"- %s   ","Opening...");
		PA_WaitForVBL();
	}
	
}



void glitchTools::UnLoadNPCSprite(int spriteNum)
{
	
	PA_DeleteBg(1, 2);
}

*/


void glitchTools::InputToContinue()
{
	PA_LoadSpritePal(TOUCH, // Screen
			1, // Palette number
			(void*)arrow_Pal);	// Palette name
	PA_CreateSprite(TOUCH, // Screen
			1, // Sprite number
			(void*)arrow_Sprite, // Sprite name
			OBJ_SIZE_8X8, // Sprite size
			1, // 256 color mode
			1, // Sprite palette number
			238, 176); // X and Y position on the screen
	u8 i=0;
	u8 cnt = 0;
	while(i!=2)
	{
		PA_UpdateStylus();
		cnt++;
		//blinking cursor	
		if(cnt%20<10)
			//i--;
			PA_SetSpriteAnim(TOUCH, 1, 0);
		else
			//i++;
			PA_SetSpriteAnim(TOUCH, 1, 1);
		//PA_SetSpriteAnim(1, 1, i); // screen, sprite, frame
		if(Stylus.Held||Pad.Newpress.A)
			i=2;
		if(Pad.Newpress.Select&&inv.map)
			showMap();
		if (Pad.Newpress.Start)
			showOptions();
		PA_WaitForVBL();
		//to make sure cnt does not overflow
		cnt=cnt%20;

	}
//	AS_SoundQuickPlay(switchs);
	PA_DeleteSprite(0,1);
}
void glitchTools::fadeIn(int screen, int duration)
{
	for (int i=-31;i<1;i++)
	{
		PA_SetBrightness( screen, i );
		SlpThrd(duration);
	}
}
void glitchTools::fadeOut(int screen, int duration)
{
	for (int i=0;i>-32;i--)
	{
		PA_SetBrightness( screen, i );
		SlpThrd(duration);
	}
}
void glitchTools::showMap()
{
	/*
	fadeOut(TOP,1);
	PA_EasyBgLoad(TOP, 0, map);		
	fadeIn(TOP,1);
	while(1)
	{
		if (Stylus.Held||Pad.Newpress.B)
		{
			fadeOut(TOP,1);
			PA_DeleteBg(TOP,0);
			//loadBackground(0, _BGBLUE);
			fadeIn(TOP, 1);
			
			break;
		}
		PA_WaitForVBL();
	}
	*/
}
void glitchTools::showSave()
{
	SlowType("Do you want to save?");
	char *sc[2];
	sc[0]="YES";
	sc[1]="NO";
	if (ChoiceButtons(sc,2))
	{
		EraseButtons(2);
		SlowType("Press A or touch the screen to resume game.                                                        ");
		
		return;
	}
	EraseButtons(2);
	//sav.name="player";
	//sav.place=status;
	//PA_Save32bit(0,status);
	
	SlowType("Save Completed                                                           ");
	
	return;

}
void glitchTools::showOptions()
{
	PA_InitText(TOUCH,1);
	LoadTouchBackground(_BGOPTIONS);
	PA_SetTextCol(TOUCH,30,10,0);
	PA_OutputSimpleText(TOUCH,9,5,_SAVE);
	PA_OutputSimpleText(TOUCH,9,11,_LOAD);
	PA_OutputSimpleText(TOUCH,9,17,_OPTIONS);
	STOP_HERE
	LoadTouchBackground(_BGBLUE);
	
}



int glitchTools::SlpIntroThrd(int frames)
{
	for (int i=0; i<=frames; i++)
	{
		if(Stylus.Held||Pad.Newpress.A)
			return 1;
		PA_WaitForVBL();
	}
	return 0;
}


int glitchTools::SlowIntroType(char text[])
{
	wait=0;
	//initializes text on touch screen, bg layer 1
	PA_InitText(TOUCH,1);
//	PA_InitCustomText(TOUCH,1,aafontq);
    //PA_SetTextCol(TOUCH,31,31,0);
	//prints the text one char per frame
	for (u32 i=0; i<=strlen(text); i++)
	{
		if(Stylus.Held||Pad.Newpress.A)
		{
			PA_BoxText(TOUCH,1,2,30,22,text,i);
			return 1;
		}
		PA_BoxText(TOUCH,1,2,30,22,text,strlen(text));
		
		SlpIntroThrd(wait);
	}
 return 0;
}
