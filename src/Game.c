#pragma once
#include "game.h"
#include "cprocessing.h"
#include "MainMenu.h"
#include <stdlib.h>
#include "snecc.h"
#include "controls.h"


static const float halfX = 120.0f;																		//half of buttons's width
static const float halfY = 60.0f;																		//half of button's height
static float centerXSTART, centerYSTART, centerXCONTROLS, centerYCONTROLS, centerXQUIT, centerYQUIT;	//centre of button, to get area where mouse clicks
static float STARTbuttonLeft, STARTbuttonRight, STARTbuttonTop, STARTbuttonBottom;						//sides of start button
static float QUITbuttonLeft, QUITbuttonRight, QUITbuttonTop, QUITbuttonBottom;							//sides of quit button
static float CONTROLSbuttonLeft, CONTROLSbuttonRight, CONTROLSbuttonTop, CONTROLSbuttonBottom;			//sides of quit button

CP_Image GameOver, retry1, retry2, controls1, controls2, quit1, quit2;		//buttons to change to game, to controls, to exit game
CP_Sound lose;																//sound when losing

//@brief : set init settings of menu
void Game_Init(void)
{
	//play sound once when enter lose screen
	lose = CP_Sound_Load("./Assets/Sound/lose.wav");
	CP_Sound_Play(lose);

	//images
	GameOver = CP_Image_Load("./Assets/Art/Background/gameover.png");
	retry1 = CP_Image_Load("./Assets/Art/Background/retrybutton.png");
	retry2 = CP_Image_Load("./Assets/Art/Background/retrybuttonhover.png");
	controls1 = CP_Image_Load("./Assets/Art/Background/controlsbutton.png");
	controls2 = CP_Image_Load("./Assets/Art/Background/controlsbuttonhover.png");
	quit1 = CP_Image_Load("./Assets/Art/Background/quitbutton.png");
	quit2 = CP_Image_Load("./Assets/Art/Background/quitbuttonhover.png");

	//to position the center of retry button
	centerXSTART = CP_System_GetWindowWidth() / 2.9f;
	centerYSTART = CP_System_GetWindowHeight() / 1.25f;

	//get perimeter of retry button
	STARTbuttonLeft = centerXSTART - halfX;
	STARTbuttonRight = centerXSTART + halfX;
	STARTbuttonTop = centerYSTART - halfY;
	STARTbuttonBottom = centerYSTART + halfY;

	//to position the center of controls button
	centerXCONTROLS = CP_System_GetWindowWidth() / 2.0f;
	centerYCONTROLS = CP_System_GetWindowHeight() / 1.25f;

	//get perimeter of controls button
	CONTROLSbuttonLeft = centerXCONTROLS - halfX;
	CONTROLSbuttonRight = centerXCONTROLS + halfX;
	CONTROLSbuttonTop = centerYCONTROLS - halfY;
	CONTROLSbuttonBottom = centerYCONTROLS + halfY;

	//position center of quit button
	centerXQUIT = CP_System_GetWindowWidth() / 1.52f;
	centerYQUIT = CP_System_GetWindowHeight() / 1.25f;

	//perimeter of quit button
	QUITbuttonLeft = centerXQUIT - halfX;
	QUITbuttonRight = centerXQUIT + halfX;
	QUITbuttonTop = centerYQUIT - halfY;
	QUITbuttonBottom = centerYQUIT + halfY;
}

//@brief : update menu
void Game_Update(void)
{
	//background
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));

	//game over display
	CP_Image_Draw(GameOver, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2.5f, 959, 550, 255);

	CP_Image_Draw(retry1, centerXSTART, centerYSTART, halfX * 2, halfY * 2, 255);			//retry button
	CP_Image_Draw(controls1, centerXCONTROLS, centerYCONTROLS, halfX * 2, halfY * 2, 255);	//controls button
	CP_Image_Draw(quit1, centerXQUIT, centerYQUIT, halfX * 2, halfY * 2, 255);				//quit button

	//detect mouse
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	//cursor in range of retry button
	if (((mouseX >= STARTbuttonLeft) && (mouseX <= STARTbuttonRight)) && ((mouseY >= STARTbuttonTop) && (mouseY <= STARTbuttonBottom)))
	{
		//hover effect
		CP_Image_Draw(retry2, centerXSTART, centerYSTART, halfX * 2, halfY * 2, 255);

		//launch game
		if (CP_Input_MouseClicked())
		{

			CP_Engine_SetNextGameState(snecc_init, snecc_update, snecc_exit); //launch snake game
		}
	}

	//cursor in range of controls button
	else if (((mouseX >= CONTROLSbuttonLeft) && (mouseX <= CONTROLSbuttonRight)) && ((mouseY >= CONTROLSbuttonTop) && (mouseY <= CONTROLSbuttonBottom)))
	{
		//hover effect
		CP_Image_Draw(controls2, centerXCONTROLS, centerYCONTROLS, halfX * 2, halfY * 2, 255);

		//launch controls screen
		if (CP_Input_MouseClicked())
		{

			CP_Engine_SetNextGameState(controls_init, controls_update, controls_exit);//launch controls menu
		}
	}

	//cursor in range of quit button
	else if (((mouseX >= QUITbuttonLeft) && (mouseX <= QUITbuttonRight)) && ((mouseY >= QUITbuttonTop) && (mouseY <= QUITbuttonBottom)))
	{
		//hover effect
		CP_Image_Draw(quit2, centerXQUIT, centerYQUIT, halfX * 2, halfY * 2, 255);

		//quit game
		if (CP_Input_MouseClicked())
		{
			CP_Engine_Terminate();//end game
		}
	}
}

//@brief : exit menu. free loaded resources
void Game_Exit(void)
{
	//Free images
	CP_Image_Free(&GameOver);
	CP_Image_Free(&retry1);
	CP_Image_Free(&retry2);
	CP_Image_Free(&controls1);
	CP_Image_Free(&controls2);
	CP_Image_Free(&quit1);
	CP_Image_Free(&quit2);

	//Free sounds
	CP_Sound_Free(lose);
}
