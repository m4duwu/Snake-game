#include "credits.h"
#include "MainMenu.h"
#include "cprocessing.h"

static const float halfX = 120.0f;			//half of buttons's width
static const float halfY = 60.0f;			//half of button's height
static float centerXbutton, centerYbutton;  //buttons
static float left, right, top, bottom;      //use to check mouse location

CP_Image credits, button1, button2; //images
CP_Sound eatsound; //sound

//@brief : set init settings of menu
void credits_init(void)
{
	//play sound once when enter credit screen
	eatsound = CP_Sound_Load("./Assets/Sound/snake eat food.mp3");
	CP_Sound_Play(eatsound);

	//images
	credits = CP_Image_Load("./Assets/Art/Background/credits.png");
	button1 = CP_Image_Load("./Assets/Art/Background/menubutton.png");
	button2 = CP_Image_Load("./Assets/Art/Background/menubuttonhover.png");

	//to position the center of button
	centerXbutton = CP_System_GetWindowWidth() / 2.0f;
	centerYbutton = CP_System_GetWindowHeight() / 1.15f;

	//get perimeter of button
	left = centerXbutton - halfX;
	right = centerXbutton + halfX;
	top = centerYbutton - halfY;
	bottom = centerYbutton + halfY;
}

//@brief : update menu
void credits_update(void)
{
	//background
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	//draw image
	CP_Image_Draw(credits, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2.5f, 1300, 750, 255);

	//draw button
	CP_Image_Draw(button1, centerXbutton, centerYbutton, halfX * 2, halfY * 2, 255);

	//detect mouse
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	//cursor in range of button
	if (((mouseX >= left) && (mouseX <= right)) && ((mouseY >= top) && (mouseY <= bottom)))
	{
		//hover effect
		CP_Image_Draw(button2, centerXbutton, centerYbutton, halfX * 2, halfY * 2, 255);

		//return to menu
		if (CP_Input_MouseClicked())
		{
			CP_Engine_SetNextGameState(MainMenu_Init, MainMenu_Update, MainMenu_Exit);//enter main menu
		}
	}

}

//@brief : exit menu. free loaded resources
void credits_exit(void)
{
	//free images
	CP_Image_Free(&credits);
	CP_Image_Free(&button1);
	CP_Image_Free(&button2);

	//free sounds
	CP_Sound_Free(eatsound);
}