// PALib Template Application

// Includes
#include <PA9.h>       // Include for PA_Lib
#include <NEMain.h>
#include <mikmod9.h>
#include "glitchtools.h"

//#include "gfx/all_gfx.c"

#include "nitrocat.h"
#include "texture.h"
#include "cubo.h"
#include "sphere.h"
#include "texcubo.h"
#include "test_pal.h"
#include "test_tex.h"
#include "music.h"
#include "intro.h"
#include "Moth.h"


//Samples
#include "samp.h"

#define NUMBER_OF_MOTHS 6


NE_Camera * Camera;     //We use pointers to waste less ram if we finish 3D mode.

//Models for Chapter II
NE_Model * Sphere; 
NE_Material * Material; 
NE_Material * Metal; 
NE_Material * Rainbow;
NE_Model  * Cube;
NE_Model  * Moth_mod[NUMBER_OF_MOTHS];

//Sound System
SAMPLE* sample;
MODULE* module;

//Moving Object structures
Moth moths[NUMBER_OF_MOTHS];

glitchTools tool;

void Forever()
{
	while(1)
	{
		PA_WaitForVBL();
	}
}
void RotoTranslate(float* translation, int rotX, int rotY, int rotZ, float distance)
{
	

	translation[0] = distance * ( -(PA_Cos(rotX)^2 * PA_Sin(rotX) / (256 * 256 * 256)) + (PA_Sin(rotZ)^2 * PA_Cos(rotZ) / (256 * 256 * 256) ) );
	translation[1] = distance * ( -(PA_Cos(rotY)^2 * PA_Sin(rotY) / (256 * 256 * 256)) + (PA_Sin(rotX)^2 * PA_Cos(rotX) / (256 * 256 * 256) ) );
	translation[2] = distance * ( -(PA_Cos(rotZ)^2 * PA_Sin(rotZ) / (256 * 256 * 256)) + (PA_Sin(rotY)^2 * PA_Cos(rotY) / (256 * 256 * 256) ) );

	return;
}
void MikMod9_SendCommand(u32 command)
{
	// this sends the value passed in as a parameter via the FIFO to the arm7
	while (REG_IPC_FIFO_CR & IPC_FIFO_SEND_FULL);
	REG_IPC_FIFO_TX = command;
}

// Needs to be called regularly
void TimerInterrupt()
{
	// player tick
	MikMod_Update();
	
	// the bpm can change in the middle of the song
	TIMER0_DATA = TIMER_FREQ_256(md_bpm * 50 / 125);
}



int InitSound()
{
	MikMod_RegisterDriver(&drv_nds_hw);
	//MikMod_RegisterAllLoaders();
	
	PA_OutputText(0, 1, 1, "Initializing mikmod ...\n");
	if (MikMod_Init(""))
	{
		PA_OutputText(0, 1, 2, "Could not initialize mikmod, reason:\n%s\n", MikMod_strerror(MikMod_errno));
		return 1;
	}
	
	module = Player_LoadMemory(music, (u32)music_size, 64, 0);
	if (!module)
	{
		PA_OutputText(0, 1, 2, "Could not load module, reason:\n%s\n", MikMod_strerror(MikMod_errno));
		return 1;
	}

	
		
	// call update with correct timing
	TIMER0_CR = 0;
	irqSet(IRQ_TIMER0, TimerInterrupt);
	irqEnable(IRQ_TIMER0);
	TIMER0_DATA = TIMER_FREQ_256(md_bpm * 50 / 125);
	TIMER0_CR = TIMER_DIV_256 | TIMER_IRQ_REQ | TIMER_ENABLE;
	Player_Start(module);
}

void PlaySFX(char samplename[])
{
	sample = Sample_Load(samplename);
	Sample_Play(sample, 0, 0);
}

void Player_FadeOut()
{
	for(int i=128;i>0;i--)
	{
		Player_SetVolume(i);
		tool.SlpThrd(1);

	}
	Player_Stop();
	Player_SetVolume(128);
}

void Draw3DSceneChapter2(void)
{
	NE_CameraUse(Camera);   //Set camera
	NE_ModelDraw(Sphere); //Draw model...
	NE_PolyFormat(31,0,NE_LIGHT_ALL,NE_CULL_NONE,NE_USE_FOG );
	NE_ModelDraw(Cube); //Draw model...
	for(int i=0;i<NUMBER_OF_MOTHS;i++)
	{
		NE_ModelDraw(Moth_mod[i]); //Draw model...
	}

}


void Init3DSystem()
{
 irqEnable(IRQ_HBLANK);
	irqSet(IRQ_VBLANK, NE_VBLFunc); //This is needed for special screen effects
	irqSet(IRQ_HBLANK, NE_HBLFunc);
	NE_Init3D();
}

void End3DSystem()
{
	NE_End();
}

void InitModelsChapter2()
{
	//Sphere
	Sphere = NE_ModelCreate(NE_Static);  //Create space for the things we will use.
	NE_ModelLoadStaticMesh(Sphere,(u32*)sphere);
	Rainbow = NE_MaterialCreate();
	NE_MaterialTexLoad(Rainbow, GL_RGB, 128, 128, TEXGEN_TEXCOORD, (u8*) test_tex);
	NE_ModelSetMaterial(Sphere, Rainbow);
	NE_ModelScale(Sphere, .6, .6, .6);

	//Ambience/BoundingBox
	Cube = NE_ModelCreate(NE_Static);
	NE_ModelLoadStaticMesh(Cube,(u32*)cubo);
	Metal = NE_MaterialCreate();
	NE_MaterialTexLoad(Metal, GL_RGB, 128, 128, TEXGEN_TEXCOORD, (u8*) texcubo);
	NE_ModelSetMaterial(Cube, Metal);	
	NE_ModelScale(Cube, 5.0, 5.0, 5.0);


	//Moths
	
	Material = NE_MaterialCreate();
	NE_MaterialTexLoad(Material, GL_RGB, 128, 128, TEXGEN_TEXCOORD, (u8*) texture);
	
	for(int i=0;i<NUMBER_OF_MOTHS;i++)
	{
		Moth_mod[i] = NE_ModelCreate(NE_Static);
		NE_ModelLoadStaticMesh(Moth_mod[i],(u32*)cubo);
		NE_ModelSetMaterial(Moth_mod[i], Material);
		NE_ModelScale(Moth_mod[i], .1, .1, .1);
		NE_ModelSetCoord(Moth_mod[i],moths[i].X+1,moths[i].Y+1,moths[i].Z+1);
	}
}

void Init3DSceneChapter2()
{
	Camera = NE_CameraCreate();      //If you don't do this, the game will crash.
	//Set coordinates for the camera
	NE_CameraSet(Camera, -1,-1,1, //Position
		                  0,0,0, //Look at
						  0,1,0);//Up direction
	//We set up a light and its color
	NE_LightSet(0,NE_DarkBlue,0,-1,0);
	//NE_LightSet(1,NE_White,0,0,0);
	char buffer[1024];
	u8 collisions = 0;
	bool done = false;
	PA_InitText(1,1);
	while (!done)
	{
		scanKeys();  //Get keys information
		u8 keys = keysHeld();
		int x1, y1, z1;	
		
		NE_ModelGetCoordI(Sphere, &x1, &y1, &z1);
		
		if(keys & KEY_UP && x1>-4)
		{
			NE_ModelTranslate(Sphere, -0.05, 0, 0);//moves the model
		}
		if(keys & KEY_DOWN && x1<4)
		{
			NE_ModelTranslate(Sphere, 0.05, 0, 0);//moves the model
		}
		if(keys & KEY_RIGHT && y1>-4)
		{	
			NE_ModelTranslate(Sphere, 0, -0.05, 0);//moves the model
		}
		if(keys & KEY_LEFT && y1<4) 
		{
			NE_ModelTranslate(Sphere, 0, 0.05, 0);//moves the model
		}
		if(keys & KEY_A && z1>-4)
		{	
			NE_ModelTranslate(Sphere, 0, 0, -0.05);//moves the model
		}
		if(keys & KEY_B && z1<4) 
		{
			NE_ModelTranslate(Sphere, 0, 0, 0.05);//moves the model
		}
		if (keys)
		{
			NE_CameraSet(Camera, 1,2,2, f32tofloat(x1), f32tofloat(y1), f32tofloat(z1), -1,0,0);
		}
		
		//NE_CameraSet(Camera, 1,2,2, f32tofloat(x1), f32tofloat(y1), f32tofloat(z1), -1,0,0);
		for(int i=0;i<NUMBER_OF_MOTHS;i++)
		{
			moths[i].move();
			NE_ModelSetCoord(Moth_mod[i],moths[i].X,moths[i].Y,moths[i].Z);
			sprintf(buffer, "%d: c %1.2f,%1.2f,%1.2f    ", i, moths[i].X, moths[i].Y, moths[i].Z);
			//strcat(coords,buffer);
			PA_OutputText(TOUCH, 0, i, buffer);
			if(moths[i].isColliding(x1,y1,z1))
				collisions++;
		}
		PA_OutputText(1, 0, NUMBER_OF_MOTHS + 2, "%d collisions so far.  ", collisions);
		if (collisions> 22)
		{
			
			PA_OutputText(1, 0, NUMBER_OF_MOTHS + 3, "Model has crashed");
			while(1)
			{}
		}
		if (x1 == 3 && y1 == 3 && z1 == 3)
			
		{
			done = true;
			PA_OutputText(1, 0, NUMBER_OF_MOTHS + 4, "Waypoint reached!");
			tool.SlpThrd(29);
		}
		NE_Process(Draw3DSceneChapter2); //Draws scene
		//NE_WaitForVBL(NE_UPDATE_ANIMATIONS); //Wait for next frame
		PA_WaitForVBL();
		
	}

	return;

}

void Init3DSceneChapter3()
{
	Camera = NE_CameraCreate();      //If you don't do this, the game will crash.
	//Set coordinates for the camera
	NE_CameraSet(Camera, -1,-1,1, //Position
		                  0,0,0, //Look at
						  0,1,0);//Up direction
	//We set up a light and its color
	NE_LightSet(0,NE_DarkBlue,0,-1,0);
	//NE_LightSet(1,NE_White,0,0,0);
	char buffer[1024];
	u8 collisions = 0;
	bool done = false;
	PA_InitText(1,1);
	while (!done)
	{
		scanKeys();  //Get keys information
		u8 keys = keysHeld();
		int x1, y1, z1;	
		
		NE_ModelGetCoordI(Sphere, &x1, &y1, &z1);
		
		if(keys & KEY_UP)
		{
			NE_ModelTranslate(Sphere, -0.05, 0, 0);//moves the model
		}
		if(keys & KEY_DOWN)
		{
			NE_ModelTranslate(Sphere, 0.05, 0, 0);//moves the model
		}
		if(keys & KEY_RIGHT)
		{	
			NE_ModelTranslate(Sphere, 0, -0.05, 0);//moves the model
		}
		if(keys & KEY_LEFT) 
		{
			NE_ModelTranslate(Sphere, 0, 0.05, 0);//moves the model
		}
		
		if (keys)
		{
			NE_CameraSet(Camera, 1,2,2, f32tofloat(x1), f32tofloat(y1), f32tofloat(z1), -1,0,0);
		}
		
		//NE_CameraSet(Camera, 1,2,2, f32tofloat(x1), f32tofloat(y1), f32tofloat(z1), -1,0,0);
		for(int i=0;i<NUMBER_OF_MOTHS;i++)
		{
			moths[i].move();
			NE_ModelSetCoord(Moth_mod[i],moths[i].X,moths[i].Y,moths[i].Z);
			sprintf(buffer, "%d: c %1.2f,%1.2f,%1.2f    ", i, moths[i].X, moths[i].Y, moths[i].Z);
			//strcat(coords,buffer);
			PA_OutputText(TOUCH, 0, i, buffer);
			if(moths[i].isColliding(x1,y1,z1))
				collisions++;
		}
		PA_OutputText(1, 0, NUMBER_OF_MOTHS + 2, "%d collisions so far.  ", collisions);
		if (x1>4)
		{
			
			//PA_OutputText(1, 0, NUMBER_OF_MOTHS + 3, "Model crashed.");
			done = true;
		}

		NE_Process(Draw3DSceneChapter2); //Draws scene
		//NE_WaitForVBL(NE_UPDATE_ANIMATIONS); //Wait for next frame
		PA_WaitForVBL();
		
	}

	return;

}



void Init2DSystem()
{
	PA_Init();    // Initializes PA_Lib
	PA_InitVBL(); // Initializes a standard VBL
	PA_InitText(0,1);
	return;
}

int main()
{
	PA_Init();    // Initializes PA_Lib
	PA_InitVBL(); // Initializes a standard VBL
	PA_InitText(0,1);
	
	//InitSound();

	char *scelte[4];
	u8 score = 0;

	
	//INTRO
	tool.status=INTRO_PRE;
	while (1)
	{
		switch(tool.status)
		{
			case(INTRO_PRE):
			{
				tool.SlowIntroType(_INTRO_00);
				//Forever();
				tool.SlpIntroThrd(50);
				PlaySFX("samp");
				tool.SlowIntroType(_INTRO_01);
				tool.SlpIntroThrd(50);
				/*
				tool.SlowIntroType(_INTRO_02);
				tool.SlpIntroThrd(50);
				tool.SlowIntroType(_INTRO_03);
				tool.SlpIntroThrd(50);
				tool.SlowIntroType(_INTRO_04);
				tool.SlpIntroThrd(50);
				tool.SlowIntroType(_INTRO_05);
				tool.SlpIntroThrd(50);
				tool.SlowIntroType(_INTRO_06);
				tool.SlpIntroThrd(50);
				tool.SlowIntroType(_INTRO_07);
				tool.SlpIntroThrd(50);
				tool.SlowIntroType(_INTRO_08);
				tool.SlpIntroThrd(50);
				tool.SlowIntroType(_INTRO_09);
				tool.SlpIntroThrd(50);
				tool.SlowIntroType(_INTRO_10);
				tool.SlpIntroThrd(50);
				tool.SlowIntroType(_INTRO_11);
				tool.SlpIntroThrd(50);
				//*/
				tool.SlowIntroType(_INTRO_12);
				tool.SlpThrd(50);

				tool.status = CHAP_2_PRE;//INTRO_POST;
				break;

			}
			case INTRO_POST:
			{
				Player_FadeOut();
				MODULE* intro_thm = Player_LoadMemory(intro, (u32)intro_size, 64, 0);
				//Player_Start(intro_thm);
				tool.SlowType(_OPTIONS);
				scelte[0]=_NEWGAME;
				scelte[1]=_LOAD;
				if(tool.ChoiceButtons(scelte, 2)==1);
				{
					tool.EraseButtons(2);
					tool.SlowType("Load Complete.");
				}
				//Chapter I
				tool.status = CHAP_1_PRE;
				break;
			}
			case CHAP_1_PRE:
			{
				tool.SlowType(_CH1_00);
				tool.InputToContinue();
				tool.SlowType(_CH1_01);
				tool.InputToContinue();
				tool.SlowType(_CH1_02);
				tool.InputToContinue();
				tool.SlowType(_CH1_03);
				tool.InputToContinue();
				tool.status = CHAP_1_POST;
				break;
			}
			case CHAP_1_POST:
			{
				tool.status = CHAP_2_PRE;
				break;
			}
			case CHAP_2_PRE:
			{
				tool.SlowType(_CH2_00);
				tool.InputToContinue();
				tool.SlowType(_CH2_01);
				tool.InputToContinue();

				Init3DSystem();
				InitModelsChapter2();
				Init3DSceneChapter2();
				End3DSystem();
				Init2DSystem();
				tool.status = CHAP_2_POST;
				break;
			}
			case CHAP_2_POST:
			{
				tool.status = CHAP_3_PRE;
				break;
			}
			case CHAP_3_PRE:
			{
				tool.SlowType(_CH3_00);
				tool.InputToContinue();
				tool.status = CHAP_3_POST;
				break;
			}
			case CHAP_3_POST:
			{
				tool.status = CHAP_4_PRE;
				break;
			}
			case CHAP_4_PRE:
			{
				tool.SlowType(_CH4_00);
				tool.InputToContinue();
				tool.status = CHAP_4_POST;
				break;
			}
			case CHAP_4_POST:
			{
				tool.status = CHAP_5_PRE;
				break;
			}
			case CHAP_5_PRE:
			{
				tool.SlowType(_CH5_00);
				tool.InputToContinue();
				tool.SlowQuote(_CH5_01,_NPC01);
				tool.InputToContinue();
				tool.SlowQuote(_CH5_02, _PLAYER);
				tool.InputToContinue();
				tool.SlowQuote(_CH5_03, _NPC01);
				tool.InputToContinue();
				tool.SlowQuote(_CH5_04, _PLAYER);
				tool.InputToContinue();
				tool.SlowQuote(_CH5_05, _NPC01);
				tool.InputToContinue();
				tool.SlowQuote(_CH5_06, _PLAYER);
				tool.InputToContinue();
				tool.SlowQuote(_CH5_07, _NPC01);
				scelte[0] = _CH5_07_0;
				scelte[1] = _CH5_07_1;
				if(tool.ChoiceButtons(scelte,2) == 0)
				{
					tool.EraseButtons(2);
					tool.SlowQuote(_CH5_07_0_0, _PLAYER);
					tool.InputToContinue();
					tool.SlowQuote(_CH5_07_0_1, _NPC01);
					scelte[0] = _CH5_07_0_1_0;
					scelte[1] = _CH5_07_0_1_1;
					if(tool.ChoiceButtons(scelte,2) == 0)
					{
						tool.EraseButtons(2);
						tool.SlowQuote(_CH5_07_0_1_0_0, _PLAYER);
						tool.InputToContinue();
						tool.SlowQuote(_CH5_07_0_1_0_1, _NPC01);
						tool.InputToContinue();
						tool.SlowQuote(_CH5_07_0_1_0_2, _PLAYER);
						tool.InputToContinue();
					}
					else
					{
						tool.EraseButtons(2);
						tool.SlowQuote(_CH5_07_0_1_1_0, _PLAYER);
						tool.InputToContinue();
						tool.SlowQuote(_CH5_07_0_1_1_1, _NPC01);
						tool.InputToContinue();
					}
					tool.SlowQuote(_CH5_07_0_2, _PLAYER);
					tool.InputToContinue();
				}
				else
				{
					tool.EraseButtons(2);
					tool.SlowQuote(_CH5_07_1_0, _PLAYER);
					tool.InputToContinue();
					tool.SlowQuote(_SUS, _NPC01);
					tool.InputToContinue();
					tool.SlowQuote(_SUS, _PLAYER);
					tool.InputToContinue();
				}
				tool.SlowQuote(_CH5_08, _NPC01);
				tool.InputToContinue();
				tool.SlowQuote(_CH5_09, _PLAYER);
				tool.InputToContinue();
				tool.SlowQuote(_CH5_10, _NPC01);
				tool.InputToContinue();
				

				//3d scene for chapter V
				tool.status = CHAP_5_POST;
				break;
			}
			case CHAP_5_POST:
			{
				tool.status = CHAP_6_PRE;
				break;
			}
			case CHAP_6_PRE:
			{
				tool.SlowType(_CH6_00);
				tool.InputToContinue();
				tool.status = CHAP_6_POST;
				break;
			}
			case CHAP_6_POST:
			{
				tool.status = END_1;
				break;
			}
			case END_1:
			{
				tool.status = CREDITS;
				break;
			}
			case END_2:
			{
				tool.status = CREDITS;
				break;
			}
			case END_3:
			{
				tool.status = CREDITS;
				break;
			}
			case CREDITS:
			{
				tool.PrintCredits(_CRD_00);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_01);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_02);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_03);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_04);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_05);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_06);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_07);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_08);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_09);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_10);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_11);
				tool.SlpThrd(30);
				tool.PrintCredits(_CRD_12);
				Forever();
				break;
			}
			default:
			{
				break;
			}

		}

			
	}
		
	
		
		/*
		PA_MoveSprite(0);
		if (!PA_SpriteTouched(0))
		{
			if(abs(PA_GetSpriteX(0,0) - 128)<3 && abs(PA_GetSpriteY(0,0) - 96)<3)
			{
				PA_SetSpriteX(0, 0, 128);
				PA_SetSpriteY(0, 0, 92);
			}
			else
			{
				int new_x = (int)(PA_GetSpriteX(0,0) * 0.95);
				int new_y = (int)(PA_GetSpriteY(0,0) * 0.95);
				PA_SetSpriteX(0, 0, new_x);
				PA_SetSpriteY(0, 0, new_y);
				
			}


		}
		*/
		


	
	return 0;
}
