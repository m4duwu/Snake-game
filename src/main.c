//---------------------------------------------------------
// file:	main.c
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "snecc.h"
#include "MainMenu.h"
#include "Logo.h"
#include <stdio.h>

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	// initialize variables and CProcessing settings for this gamestate
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	// check input, update simulation, render etc.
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}

static const int ww = WINDOW_WIDTH;
static const int wh = WINDOW_HEIGHT;
// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{


	CP_System_SetWindowTitle("Snake");//Setting the window title
	CP_System_SetWindowSize(ww, wh);//Setting the window size and position
	CP_System_SetFrameRate(60);//Setting Frame Rate
	CP_System_ShowConsole();//Show console
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	CP_Engine_SetNextGameState(logo_Init, logo_Update, logo_Exit);//open with logo screen
	CP_Engine_Run();//Starts game
	return 0;
}
