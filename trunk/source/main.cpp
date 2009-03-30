// PALib Template Application

// Includes
#include <PA9.h>       // Include for PA_Lib
#include <NEMain.h>
#include <mikmod9.h>
//#include "gfx/all_gfx.c"

#include "nitrocat.h"
#include "texture.h"
#include "cubo.h"
#include "texcubo.h"
#include "music.h"
#include "Moth.h"





NE_Camera * Camera;     //We use pointers to waste less ram if we finish 3D mode.
NE_Model * Model; 
NE_Material * Material; 
NE_Material * MaterialCubo; 
NE_Model  * Cubo;
NE_Model  * Moth_mod[10];

Moth moths[10];


void RotoTranslate(float* translation, int rotX, int rotY, int rotZ, float distance)
{
	

	translation[0] = distance * ( -(PA_Cos(rotX)^2 * PA_Sin(rotX) / (256 * 256 * 256)) + (PA_Sin(rotZ)^2 * PA_Cos(rotZ) / (256 * 256 * 256) ) );
	translation[1] = distance * ( -(PA_Cos(rotY)^2 * PA_Sin(rotY) / (256 * 256 * 256)) + (PA_Sin(rotX)^2 * PA_Cos(rotX) / (256 * 256 * 256) ) );
	translation[2] = distance * ( -(PA_Cos(rotZ)^2 * PA_Sin(rotZ) / (256 * 256 * 256)) + (PA_Sin(rotY)^2 * PA_Cos(rotY) / (256 * 256 * 256) ) );

	return;
}
void Draw3DScene(void)
{
	NE_CameraUse(Camera);   //Set camera
	NE_ModelDraw(Model); //Draw model...
	NE_PolyFormat(31,0,NE_LIGHT_ALL,NE_CULL_NONE,NE_MODULATION );
	NE_ModelDraw(Cubo); //Draw model...
	for(int i=0;i<10;i++)
	{
		NE_ModelDraw(Moth_mod[i]); //Draw model...
	}

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


int main()
{
	PA_Init();    // Initializes PA_Lib
	PA_InitVBL(); // Initializes a standard VBL
	irqEnable(IRQ_HBLANK);
	irqSet(IRQ_VBLANK, NE_VBLFunc); //This is needed for special screen effects
	irqSet(IRQ_HBLANK, NE_HBLFunc);
	NE_Init3D();

	PA_InitText(1, 2);
	//PA_OutputSimpleText(1, 1, 2, "Hello World!");


	Model = NE_ModelCreate(NE_Static);  //Create space for the things we will use.
	Camera = NE_CameraCreate();      //If you don't do this, the game will crash.
	Material = NE_MaterialCreate();
	MaterialCubo = NE_MaterialCreate();
	
	//Set coordinates for the camera
	NE_CameraSet(Camera, -8,-6,1, //Position
		                  0,0,0, //Look at
						  0,1,0);//Up direction
	
	//Load mesh from RAM and assign it to the object "Model".
	NE_ModelLoadStaticMesh(Model,(u32*)cubo);
	//Load a RGB texture from RAM and assign it to "Material".
	NE_MaterialTexLoad(Material, GL_RGB, 128, 128, TEXGEN_TEXCOORD, (u8*) texture);
	//Assign texture to model...
	NE_ModelSetMaterial(Model, Material);
	
	Cubo = NE_ModelCreate(NE_Static);
	NE_ModelLoadStaticMesh(Cubo,(u32*)cubo);
	NE_MaterialTexLoad(MaterialCubo, GL_RGB, 128, 128, TEXGEN_TEXCOORD, (u8*) texcubo);
	NE_ModelSetMaterial(Cubo, MaterialCubo);
	NE_ModelScale(Model, .2, .2, .2);
	NE_ModelScale(Cubo, 5.0, 5.0, 5.0);
	//We set up a light and its color
	NE_LightSet(0,NE_White,0,-1,0);


	float translations[] = {0,0,0};
	float a = 0;
	char coords[1024] = "";
	char buffer[1024];
	for(int i=0;i<10;i++)
	{
		//Moth c;// = new Moth();
		//c.init();
		//moths[i] = c;
		sprintf(buffer, "%d: c %1.2f,%1.2f,%1.2f s %1.2f,%1.2f,%1.2f  ", i, moths[i].X, moths[i].Y, moths[i].Z, moths[i].vX, moths[i].vY, moths[i].vZ);
		strcat(coords,buffer);
	}


	for(int i=0;i<10;i++)
	{
		Moth_mod[i] = NE_ModelCreate(NE_Static);
		NE_ModelLoadStaticMesh(Moth_mod[i],(u32*)cubo);
		NE_ModelSetMaterial(Moth_mod[i], Material);
		NE_ModelScale(Moth_mod[i], .1, .1, .1);
	}

	PA_OutputText(1, 2, 3, coords);
	
	
	while (1)
	{
		
		scanKeys();  //Get keys information
		int keys = keysHeld();

		float translations[] = {0,0,0};

		if(keys & KEY_UP)
		{

			//NE_ModelRotate(Model, 0, 0, 2);
			//RotoTranslate(translations, 0, 0, 2, 8);

			//PA_OutputText(1, 2, 3, "UP!");
			//NE_ModelRotate(Model, 0, 0, 2);
			//RotoTranslate(translations, 0, 0, 2, 8);

			NE_CameraRotate (Camera, 0, 0, 2);
		}
		if(keys & KEY_DOWN)
		{
			//PA_OutputText(1, 2, 3, "Down!");
			//NE_ModelRotate(Model, 0, 0, -2);
			NE_CameraRotate (Camera, 0, 0, -2);
			//RotoTranslate(translations, 0, 0, -2, 8);
		}
		if(keys & KEY_RIGHT)
		{	
			//PA_OutputText(1, 2, 3, "Right!");
			//NE_ModelRotate(Model, 0, 2, 0);
			NE_CameraRotate (Camera, 0, 2, 0);
			//RotoTranslate(translations, 0, 2, 0, 8);
		}
		if(keys & KEY_LEFT) 
		{
			//PA_OutputText(1, 2, 3, "left!!");
			//NE_ModelRotate(Model, 0, -2, 0);
			NE_CameraRotate (Camera, 0, -2, 0);
			//RotoTranslate(translations, 0, -2, 0, 8);
		}

		NE_CameraMoveFree(Camera, (int)translations[0], (int)translations[1], (int)translations[2]);

		//NE_CameraMoveFree(Camera, (int)translations[0], (int)translations[1], (int)translations[2]);
		int x1, y1, z1;	
		NE_ModelTranslate(Model, -0.01, 0, 0);//moves the model
		NE_ModelGetCoordI(Model, &x1, &y1, &z1);
		PA_OutputText(1, 2, 3, "Position is x: %d, y:%d, z:%d", x1, y1, z1);
		NE_CameraSet(Camera, -8,-6,1, f32tofloat(x1), f32tofloat(y1), f32tofloat(z1), 0,1,0);
		for(int i=0;i<10;i++)
		{
			moths[i].move();
			NE_ModelSetCoord(Moth_mod[i],moths[i].X,moths[i].Y,moths[i].Z);
			
		}
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

	

		NE_Process(Draw3DScene); //Draws scene
		//NE_WaitForVBL(NE_UPDATE_ANIMATIONS); //Wait for next frame
		PA_WaitForVBL();
		//PA_WaitForVBL();
	}
	
	return 0;
}
