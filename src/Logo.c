#include "Logo.h"
#include "cprocessing.h"
#include "MainMenu.h"

CP_Image logo;//image 
int fade, state = 1; //fade is used for image transparency //state is used to check for fade in and fade out

//@brief : set init settings of menu
void logo_Init(void)
{
	logo = CP_Image_Load("./Assets/Art/Logo/DigiPen_WHITE.png");//image of logo
	fade = 0;//initialized for fade in 
}

//@brief : update menu
void logo_Update(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255)); //setting background color

	//fade in
	if (state == 1)
	{
		//draw image according to transparency(fade)
		CP_Image_Draw(logo, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, 1026, 249, fade);
		fade += 2; //adding transparency to logo
		if (fade > 255)
			state = 2; //if logo is fully faded in, state = 2
	}

	//fade out
	if (state == 2)
	{
		//draw image according to transparency(fade)
		CP_Image_Draw(logo, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2, 1026, 249, fade);
		fade -= 2; //substracting transparency to logo
		if (fade < 0)
			state = 3; //if logo is fully faded out, state = 3 
	}

	//finish fade in and fade out, go to main menu
	if (state == 3)
		CP_Engine_SetNextGameState(MainMenu_Init, MainMenu_Update, MainMenu_Exit);

	//hidden key to use to skip logo intro
	if (CP_Input_KeyTriggered(KEY_ENTER))
		CP_Engine_SetNextGameState(MainMenu_Init, MainMenu_Update, MainMenu_Exit);
}

//@brief : exit menu. free loaded resources
void logo_Exit(void)
{
	CP_Image_Free(&logo); //free image
}