// PALib Template Application

// Includes
#include <PA9.h>       // Include for PA_Lib
// PAGfxConverter Include

#include "glitchTools.h"
//#include "fall.h"
#include "shist2.h"
//#include "captions.h"

#include "introbg1.h"



glitchTools tool;
u32 mapAcquired = 0;
u8 switch_ = 0;

char *scelte[4];










int main(int argc, char ** argv)
{
	
	
	PA_Init();    // Initializes PA_Lib
	PA_InitVBL(); // Initializes a standard VBL
	//PA_InitASLibForMP3(AS_MODE_MP3 | AS_NO_DELAY | AS_MODE_16CH);	// The parameter is passed to AS_Init(). Call this function only once!!!  Default settings are: AS_SetDefaultSettings(AS_PCM_8BIT, 11025, AS_SURROUND);
	//AS_SetMP3Loop(true);
	//PA_InitASLibForMP3(AS_MODE_MP3 | AS_MODE_SURROUND | AS_MODE_16CH);	// The parameter is passed to AS_Init(). Call this function only once!!!  Default settings are: AS_SetDefaultSettings(AS_PCM_8BIT, 11025, AS_SURROUND);
	AS_MP3DirectPlay((u8*)shist2, (u32)shist2_size);
	
	/****************************/
	//here starts the fucking game!!!
	/****************************/
	tool.LoadTouchBackground(_BGBLUE);
	
	
	
	tool.LoadTopBackground(_WHITE);
	tool.LoadIntro();
	
	tool.LoadTopBackground(_TITLE);
	tool.LoadTouchBackground(_BGTITLE);
	
	//tool.InputToContinue();
	while (1)
	{
		if (Stylus.Held)
		{
			if (Stylus.Y<96)
				//tool.status=START;
				tool.status=NIGHT_AT_CASTLE;
			else
				tool.status=(STATUS)PA_Load32bit(0);
			break;
		}
		PA_WaitForVBL();
	}

	AS_MP3Stop();
	tool.LoadTouchBackground(_BGBLUE);
	AS_SetMP3Loop(true);	
	AS_MP3DirectPlay((u8*)introbg1, (u32)introbg1_size);  		// Play a given mod
	
	
	PA_InitText(1,0);
	//PA_OutputText(1,0,0,"hai scelto: %d", x+1);
	//char buf[15];
	//buf = "hai scelto: %d", x;
	//tool.SlowType(buf);
	// Infinite loop to keep the program running
	tool.status = START;//NIGHT_AT_CASTLE;//HARRIS_SHOWING_BOOK;
	
	while (1)
	{
		switch(tool.status)
		{
		case START:
			tool.LoadTopBackground(_LIVINGROOM);
			
			//arraycpy(tool.choices,scelte);
			//tool.DisplayText();
			
			tool.SlowType(_CH1_LR_00);
			tool.InputToContinue();
			tool.SlowType(_CH1_LR_01);
			tool.InputToContinue();
			
			/*//puzzle
			tool.SlowType("");
			tool.LoadPuzzle();
			//*/
			tool.SlowQuote(_CH1_LR_02, _PLAYER);
			tool.InputToContinue();
			tool.SlowType(_CH1_LR_03);
			
			scelte[0]= _CH1_LR_03_c0;
			scelte[1]= _CH1_LR_03_c1;
			if(tool.ChoiceButtons(scelte, 2))
			{
				tool.EraseButtons(2);
				tool.SlowType(_CH1_LR_03_r1);
				tool.InputToContinue();
			}
			tool.EraseButtons(2);
			tool.LoadTopBackground(_PAINTING_LR);
			tool.SlowType(_CH1_LR_04);
			tool.InputToContinue();
			tool.SlowType(_CH1_LR_05);
			scelte[0]= _CH1_LR_05_c0;
			scelte[1]= _CH1_LR_05_c1;
			if(tool.ChoiceButtons(scelte, 2))
			{
				tool.EraseButtons(2);
				tool.SlowType(_CH1_LR_05_r1);
				tool.InputToContinue();
			}
			tool.EraseButtons(2);
			tool.SlowType(_CH1_LR_06);
			tool.InputToContinue();
			tool.LoadTopBackground(_LIVINGROOM);
			tool.LoadNPCSprite(1);
			tool.SlowQuote(_CH1_LR_07, _NPC01);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_LR_08, _PLAYER);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_LR_09, _NPC01);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_LR_10, _PLAYER);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_LR_11, _NPC01);
			tool.InputToContinue();

			
		
			tool.status=LAURA_BOOK_QUESTIONS;

			PA_ClearTextBg(0);
			tool.EraseButtons(4);
			break;
		case LAURA_BOOK_QUESTIONS:
			//tool.LoadTopBackground(_LIVINGROOM);
			tool.SlowQuote(_CH1_LBQ_01, _NPC01);
			scelte[0]= _CH1_LBQ_01_c0;
			scelte[1]= _CH1_LBQ_01_c1;
			scelte[2]= _CH1_LBQ_01_c2;
			scelte[3]= _CH1_LBQ_01_c3;
			switch (2000+tool.ChoiceButtons(scelte, 4))
			{
				case 2000:
					tool.EraseButtons(4);
					tool.SlowQuote(_CH1_LBQ_01_r0, _PLAYER);
					tool.InputToContinue();
					tool.SlowQuote(_CH1_LBQ_01_r0b, _NPC01);
					tool.InputToContinue();
					break;
				case 2001:
					tool.EraseButtons(4);
					tool.SlowQuote(_CH1_LBQ_01_r1, _PLAYER);
					tool.InputToContinue();
					tool.SlowQuote(_CH1_LBQ_01_r1b, _NPC01);
					tool.InputToContinue();
					break;
				case 2002:
					tool.EraseButtons(4);
					tool.SlowQuote(_CH1_LBQ_01_r2, _PLAYER);
					tool.InputToContinue();
					tool.SlowQuote(_CH1_LBQ_01_r2b, _NPC01);
					tool.InputToContinue();
					tool.SlowQuote(_CH1_LBQ_01_r2c, _PLAYER);
					tool.InputToContinue();
					tool.SlowQuote(_CH1_LBQ_01_r2d, _NPC01);
					tool.InputToContinue();
					break;
				case 2003:
					tool.EraseButtons(4);
					tool.SlowQuote(_CH1_LBQ_01_r3, _PLAYER);
					tool.InputToContinue();
					tool.SlowQuote(_CH1_LBQ_01_r3b, _NPC01);
					tool.InputToContinue();
					tool.SlowQuote(_CH1_LBQ_01_r3c, _NPC01);
					tool.InputToContinue();
					tool.SlowQuote(_CH1_LBQ_02, _NPC01);
					tool.status = LAURA_SHOWING_BOOK;
					tool.InputToContinue();
					break;

			}
			
			
			break;
		case LAURA_SHOWING_BOOK:
			tool.UnLoadNPCSprite(1);
			tool.SlowType(_CH1_LSB_00);
			tool.InputToContinue();
			tool.LoadTopBackground(_STUDYDOOR);
			tool.SlowType(_CH1_LSB_01);
			tool.InputToContinue();
			tool.LoadNPCSprite(1);
			tool.SlowQuote(_CH1_LSB_02,_NPC01);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_LSB_03,_PLAYER);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_LSB_04,_NPC01);
			tool.InputToContinue();
			tool.UnLoadNPCSprite(1);
			tool.LoadTopBackground(_STUDYLARGE);
			tool.SlowType(_CH1_LSB_05);
			tool.InputToContinue();
			tool.LoadNPCSprite(1);
			tool.SlowQuote(_CH1_LSB_06,_NPC01);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_LSB_07,_PLAYER);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_LSB_08,_NPC01);
			tool.InputToContinue();
			tool.UnLoadNPCSprite(1);
			tool.SlowType(_CH1_LSB_09);
			tool.InputToContinue();
			tool.SlowType(_CH1_LSB_10);
			tool.InputToContinue();
			switch_=0;
			
			while(switch_ != 4)
			{
				scelte[0] = _CH1_LSB_11_c0;
				scelte[1] = _CH1_LSB_11_c1;
				scelte[2] = _CH1_LSB_11_c2;
				tool.SlowType(_CH1_LSB_11);
				switch_=tool.ChoiceButtons(scelte, 3);
				if (switch_==0)
				{
					tool.LoadTopBackground(_STUDYBOOKS);
					tool.EraseButtons(3);
					tool.SlowType(_CH1_LSB_11_r0);
					tool.InputToContinue();
					tool.LoadTopBackground(_STUDYLARGE);
				}
				if (switch_==1)
				{
					tool.LoadTopBackground(_STUDYPAINT);
					tool.EraseButtons(3);
					tool.SlowType(_CH1_LSB_11_r1);
					tool.InputToContinue();
					tool.LoadTopBackground(_STUDYLARGE);
				}
				if (switch_==2)
				{
					tool.LoadTopBackground(_STUDY);
					tool.EraseButtons(3);
					tool.SlowType(_CH1_LSB_11_r2);
					tool.InputToContinue();
					tool.SlowType(_CH1_LSB_11_r2b);
					scelte[0] = _CH1_LSB_11_r2b_c0;
					scelte[1] = _CH1_LSB_11_r2b_c1;
					if (tool.ChoiceButtons(scelte,2)==0)
					{
						tool.EraseButtons(2);
						tool.SlowType(_CH1_LSB_11_r2b_r0);
						tool.InputToContinue();
					}
					tool.EraseButtons(2);
					tool.SlowType(_CH1_LSB_11_r2b_r1);
					tool.InputToContinue();
					switch_=4;
					tool.LoadTopBackground(_STUDYLARGE);
				}
			
			}
			
			tool.SlowType(_CH1_LSB_12);
			tool.InputToContinue();
			tool.LoadNPCSprite(1);
			tool.SlowQuote(_CH1_LSB_13, _NPC01);
			tool.InputToContinue();
			tool.SlowType(_CH1_LSB_14);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_LSB_15, _NPC01);
			tool.InputToContinue();
			tool.UnLoadNPCSprite(1);
			tool.LoadTopBackground(_BOOKDESK);
			tool.SlowType(_CH1_LSB_16);
			tool.InputToContinue();
			tool.SlowType(_CH1_LSB_17);
			tool.InputToContinue();
			tool.SlowType(_CH1_LSB_18);
			tool.InputToContinue();
			tool.SlowType(_CH1_LSB_19);
			tool.InputToContinue();
			tool.status=GETTING_BOOK;
			
			break;

		case GETTING_BOOK:
			tool.LoadTopBackground(_STUDYLARGE);
			tool.LoadNPCSprite(1);
			tool.SlowQuote(_CH1_GB_01, _NPC01);
			tool.InputToContinue();
			tool.SlowType(_CH1_GB_02);
			tool.InputToContinue();
			tool.SlowType(_CH1_GB_03);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_GB_04, _PLAYER);
			tool.InputToContinue();
			tool.UnLoadNPCSprite(1);

		case NIGHT_AT_CASTLE:
			tool.LoadTopBackground(_BLACK);
			tool.SlowType(_CH1_NAC_00);
			tool.InputToContinue();
			tool.SlowType(_CH1_NAC_01);
			tool.InputToContinue();
			tool.SlowType(_CH1_NAC_02);
			tool.InputToContinue();
			tool.SlowType(_CH1_NAC_03);
			tool.InputToContinue();
			tool.SlowType(_CH1_NAC_04);
			tool.InputToContinue();
			tool.SlowType(_CH1_NAC_05);
			tool.InputToContinue();
			tool.SlowQuote(_CH1_NAC_06, _PLAYER);
			tool.InputToContinue();
			tool.SlowType(_CH1_NAC_07);
			tool.InputToContinue();
			tool.LoadTopBackground(_CORRIDOR);
			tool.SlowType(_CH1_NAC_08);
			tool.InputToContinue();
			tool.status=SEARCH_FOR_NOISE;
			break;
		case SEARCH_FOR_NOISE:
			tool.SlowType(_CH1_SFN_01);
			scelte[0]= _CH1_SFN_01_c0;
			scelte[1]= _CH1_SFN_01_c1;
			scelte[2]= _CH1_SFN_01_c2;
			
			switch (4000+tool.ChoiceButtons(scelte, 3))
			{
				case 4000:
					tool.EraseButtons(3);
					tool.LoadTopBackground(_STUDY);
					tool.SlowType(_CH1_SFN_01_r0);
					tool.InputToContinue();
					break;
				case 4001:
					tool.EraseButtons(3);
					tool.LoadTopBackground(_LIVINGROOM);
					tool.SlowType(_CH1_SFN_01_r1);
					tool.InputToContinue();
					break;
				
				case 4002:
					tool.EraseButtons(3);
					tool.LoadTopBackground(_ENVELOPE);
					tool.SlowType(_CH1_SFN_01_r2);
					tool.status = LAURAS_BEDROOM;
					tool.InputToContinue();
					break;

			}
			
			
			break;
		case LAURAS_BEDROOM:
			tool.SlowType(_CH1_LBD_01);
			tool.InputToContinue();
			tool.SlowType(_CH1_LBD_02);
			tool.InputToContinue();
			tool.SlowType(_CH1_LBD_03);
			tool.InputToContinue();
			
			

			STOP_HERE
			break;
		
		}
				
			
		PA_WaitForVBL();
	}
	
	return 0;
} // End of main()
