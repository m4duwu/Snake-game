#pragma once
#include "snecc.h"
#include "cprocessing.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "Game.h"

//Define values so that code is easier to comprehend and maintain
#define UP 1 //direction
#define DOWN 2 //direction
#define LEFT 3 //direction
#define RIGHT 4 //direction
#define SIZE 100 //max snake size
#define CHARACTER_BUFFER_SIZE 40 //for string
#define CENTER_X GW/2 //width center
#define CENTER_Y GH/2 //height center
#define GRID_SIZE 80 //grid size
#define GRID_OFFSET 40 //gid offset, to center the sprite in box


//1920 by 1080
float ww = WINDOW_WIDTH; //1920
float wh = WINDOW_HEIGHT; //1080

//images
CP_Image headr;//head right
CP_Image headl;//head left
CP_Image headu;//head up
CP_Image headd;//head down
CP_Image body;//body
CP_Image tail;//tail right
CP_Image taill;//tail left
CP_Image tailu;//tail up
CP_Image taild;//tail down
CP_Image food;//food (apul)aww
CP_Image wall;//wall
CP_Image grass;//grass background
CP_Image peachy;//peach
CP_Image orangey;//orange

//sound
CP_Sound bgm;//background music
CP_Sound eatsound;//eat sound

float timeSurvived; //check for time survived
float timer = 0, interval = 0.15f, velocity = 6.67f, totalScore = 0;

int size = 5, direction, checkinit = 0;//size,direction used for snake //checkinit used to check if game has started or not
int xs = CENTER_X, ys = CENTER_Y, horizontal = 1, vertical = 0;//used for snake movement
int chk = 0, pause = 2, print = 0;//chk used for food spawning, pause used for pausing, print used for food printing
float print_delay = 0.8f;//used as timer for printing of score of food

char characterBuffer[CHARACTER_BUFFER_SIZE];//for velocity
char score[CHARACTER_BUFFER_SIZE];//for score of food
char point[CHARACTER_BUFFER_SIZE];// for overall score


//Background colour
CP_Color backgroundColour;

//struct used to determine coordinate
struct coordinate {
	float x;//x-axis (Values are in terms of GRID NUMBER)
	float y;//y-axis (Values are in terms of GRID NUMBER)
	float direction; //direction of snake 
};
typedef struct coordinate coordinate;
coordinate apul, orange, peach, snecc[SIZE];	//snecc[0] is head, middle body, snecc[last] is tail. apul orange and peach are food coordinates


//@brief : initialize snake game with intial start state of sprites and fonts
void snecc_init()
{
	//Images
	headr = CP_Image_Load("./Assets/Art/Head/snakehead.png");//head Right
	headl = CP_Image_Load("./Assets/Art/Head/snakeheal.png");//head Left
	headu = CP_Image_Load("./Assets/Art/Head/snakeheadu.png");//head UP
	headd = CP_Image_Load("./Assets/Art/Head/snakeheadd.png");//head Down
	body = CP_Image_Load("./Assets/Art/Body/snake.png");//Body
	tail = CP_Image_Load("./Assets/Art/Tail/tail.png");//Tail Right
	taill = CP_Image_Load("./Assets/Art/Tail/taill.png");//Tail Left
	tailu = CP_Image_Load("./Assets/Art/Tail/tailu.png");//Tail Up
	taild = CP_Image_Load("./Assets/Art/Tail/taild.png");//Tail Down
	food = CP_Image_Load("./Assets/Art/Food/food.png");//apple
	peachy = CP_Image_Load("./Assets/Art/Food/peach.png");//peach
	orangey = CP_Image_Load("./Assets/Art/Food/orange.png");//orange
	wall = CP_Image_Load("./Assets/Art/Wall/wall.jpg");//wall(boarder)
	grass = CP_Image_Load("./Assets/Art/Grass/grass.png");//grass(background)

	//sounds
	bgm = CP_Sound_LoadMusic("./Assets/Sound/littleidea.mp3");//Load music
	CP_Sound_PlayMusic(bgm);//Play music
	eatsound = CP_Sound_Load("./Assets/Sound/snake eat food.mp3");//load sound
	CP_Sound_Play(eatsound);//play sound
	interval = 0.12f;

	interval = 0.12f;//setting snake speed

	//initial position of snake head, body and tail
	for (int i = 0; i <= size - 1; ++i)
	{
		if (i == 0)//setting snake head position
		{
			snecc[i].direction = RIGHT;//init direction is right
			snecc[i].x = CENTER_X;//starts at center
			snecc[i].y = CENTER_Y;//starts at center
		}
		else if (i < size - 1)//setting snake body position
		{
			snecc[i].x = CENTER_X - (float)i;//each body is -i from head
			snecc[i].y = CENTER_Y;//starts at center
			snecc[i].direction = RIGHT;//init direction is right
		}
		else//setting snake tail position
		{
			snecc[i].x = CENTER_X - (float)i;//tail is the last from head
			snecc[i].y = CENTER_Y;//starts at center
			snecc[i].direction = RIGHT;//init direction is right
		}
	}

	//spawn apple randomly, and not on other fruit
	while (1) {
		apul.x = (float)CP_Random_RangeInt(2, GW - 1);//getting apple X coords
		apul.y = (float)CP_Random_RangeInt(2, GH - 1);//getting apple Y coords
		if (((peach.x == apul.x) && (peach.y == apul.y)) || ((apul.x == orange.x) && (apul.y == orange.y))) //check if apple is on peach or orange
		{
			apul.x = (float)CP_Random_RangeInt(2, GW - 1);//getting apple X coords if cond is TRUE
			apul.y = (float)CP_Random_RangeInt(2, GH - 1);//getting apple Y coordsif cond is TRUE
		}
		for (int i = 0; i < size; ++i)
		{
			if ((apul.x != snecc[i].x) || (apul.y != snecc[i].y)) { //checking if apple is NOT on snake 
				++chk;//if cond is true chk ++ (if chk is same as size that means condition is TRUE for WHOLE snake)
			}
		}
		if (chk == size)//if chk is the same as size
		{
			chk = 0;//reinit chk
			break;//break from loop
		}
		chk = 0;//reinit chk for next for loop instance

	}
	//spawn peach randomly, and not on other fruit
	while (1) {
		peach.x = (float)CP_Random_RangeInt(2, GW - 1);//getting peach X coords
		peach.y = (float)CP_Random_RangeInt(2, GH - 1);//getting peach X coords
		if (((peach.x == apul.x) && (peach.y == apul.y)) || ((peach.x == orange.x) && (peach.y == orange.y)))//check if peach is on apple or orange
		{
			peach.x = (float)CP_Random_RangeInt(2, GW - 1);//getting peach X coords if cond is TRUE
			peach.y = (float)CP_Random_RangeInt(2, GH - 1);//getting peach Y coords if cond is TRUE
		}
		for (int i = 0; i < size; ++i)
		{
			if ((peach.x != snecc[i].x) || (peach.y != snecc[i].y)) { //checking if peach is NOT on snake 
				++chk;//if cond is true chk ++ (if chk is same as size that means condition is TRUE for WHOLE snake)
			}
		}
		if (chk == size)//if chk is the same as size

		{
			chk = 0;//reinit chk
			break;//break from loop
		}
		chk = 0;//reinit chk for next for loop instance

	}
	//spawn orange randomly, and not on other fruit
	while (1) {
		orange.x = (float)CP_Random_RangeInt(2, GW - 1);//getting orange X coords
		orange.y = (float)CP_Random_RangeInt(2, GH - 1);//getting orange Y coords
		if (((peach.x == orange.x) && (peach.y == orange.y)) || ((apul.x == orange.x) && (apul.y == orange.y)))//check if orange is on apple or peach
		{
			orange.x = (float)CP_Random_RangeInt(2, GW - 1);//getting orange X coords if cond is TRUE
			orange.y = (float)CP_Random_RangeInt(2, GH - 1);//getting orange Y coords if cond is TRUE
		}
		for (int i = 0; i < size; ++i)
		{
			if ((orange.x != snecc[i].x) || (orange.y != snecc[i].y)) { //checking if orange is NOT on snake 
				++chk;//if cond is true chk ++ (if chk is same as size that means condition is TRUE for WHOLE snake)
			}
		}
		if (chk == size)//if chk is the same as size
		{
			chk = 0;//reinit chk
			break;//break from loop
		}
		chk = 0;//reinit chk for next for loop instance

	}

	//setting all to 0
	memset(characterBuffer, 0, CHARACTER_BUFFER_SIZE * sizeof(char));
	memset(score, 0, CHARACTER_BUFFER_SIZE * sizeof(char));
	memset(point, 0, CHARACTER_BUFFER_SIZE * sizeof(char));

	//setting text size and color
	CP_Settings_TextSize(70);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 175));
}

//@brief : set wall border of game and prints out scoreboard
void border()
{
	//draw walls
	for (int x = 0; x <= GW; ++x)
	{
		//for x axis TOP
		CP_Image_Draw(wall, ((float)x * GRID_SIZE) - GRID_OFFSET, (1 * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
	}
	for (int x = 0; x <= GW; ++x)
	{
		//for x axis BOTTOM
		CP_Image_Draw(wall, ((float)x * GRID_SIZE) - GRID_OFFSET, (GH * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
	}
	for (int x = 2; x < GH; ++x)
	{
		//y axis LEFT
		CP_Image_Draw(wall, (GRID_SIZE)-GRID_OFFSET, ((float)x * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
	}
	for (int x = 2; x < GH; ++x)
	{
		// y axis RIGHT
		CP_Image_Draw(wall, (GW * GRID_SIZE) - GRID_OFFSET, ((float)x * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
	}
	//velocity and score
	sprintf_s(characterBuffer, CHARACTER_BUFFER_SIZE, "%5.2f", velocity);//print velocity into characterbuffer
	sprintf_s(point, CHARACTER_BUFFER_SIZE, "%.f", totalScore);//print totalscore into point

	//print score
	CP_Font_DrawText("VELOCITY: ", ((GW - 7) * GRID_SIZE), (2 * GRID_SIZE)); //print velocity onto console
	CP_Font_DrawText(characterBuffer, ((GW - 3) * GRID_SIZE), (2 * GRID_SIZE)); //print velocity value onto console
	CP_Font_DrawText("SCORE: ", ((GW - 6) * GRID_SIZE), (3 * GRID_SIZE)); //print score onto console
	CP_Font_DrawText(point, ((GW - 3.2) * GRID_SIZE) + GRID_OFFSET, (3 * GRID_SIZE)); //print point onto console

	//set print state for fruits eaten
	if ((snecc[0].x == apul.x) && (snecc[0].y == apul.y))
		print = 1; //print state for apple
	if ((snecc[0].x == peach.x) && (snecc[0].y == peach.y))
		print = 2; //print state for peach
	if ((snecc[0].x == orange.x) && (snecc[0].y == orange.y))
		print = 3; //print state for orange

	if (print == 1)			//print +10 for apple
	{
		print_delay -= CP_System_GetDt(); //- delay by delta time
		CP_Font_DrawText("+10", ((GW - 3.2) * GRID_SIZE), (4 * GRID_SIZE));
		if (print_delay < 0) //if timer is finished, stop showing +10
		{
			print = 0; //change print state
			print_delay = 0.8f; //reinit delay time
		}
	}
	if (print == 2)			//print +50 for peach
	{
		print_delay -= CP_System_GetDt();//- delay by delta time
		CP_Font_DrawText("+50", ((GW - 3.2) * GRID_SIZE), (4 * GRID_SIZE));
		if (print_delay < 0)//if timer is finished, stop showing +50
		{
			print = 0;//change print state
			print_delay = 0.8f;//reinit delay time
		}

	}
	if (print == 3)			//print +30 for orange
	{
		print_delay -= CP_System_GetDt();//- delay by delta time

		CP_Font_DrawText("+30", ((GW - 3.2) * GRID_SIZE), (4 * GRID_SIZE));
		if (print_delay < 0)//if timer is finished, stop showing +30
		{
			print = 0;//change print state
			print_delay = 0.8f;//reinit delay time
		}
	}
}



//@brief : check for keyinput of player. 
void key_input()
{

	if (checkinit == 0) //check if game has started or not
	{
		if (CP_Input_KeyTriggered(KEY_D) || CP_Input_KeyTriggered(KEY_RIGHT)) //check if key pressed
		{
			++checkinit;//checking for initial state. Once button pressed, snake will move
			direction = RIGHT; //set direction for to RIGHT
			snecc[0].direction = RIGHT; //set snake head direction RIGHT
			horizontal = 1; //horizontal is set to 1 so that the condition (horizontal != 0) is TRUE
			vertical = 0; //vertical is set to 0 so that the condition (vertical != 0) is FALSE 
		}
	}
	if (snecc[0].y != snecc[1].y) {
		if (vertical != 0) //if snake is moving vertical (along y axis) only when snake is moving along y axis, snake can turn left or right
		{
			if (CP_Input_KeyTriggered(KEY_D) || CP_Input_KeyTriggered(KEY_RIGHT)) //check if key pressed
			{
				++checkinit;//checking for initial state. Once button pressed, snake will move
				direction = RIGHT; //set direction to RIGHT
				snecc[0].direction = RIGHT; //set snake head direction RIGHT
				horizontal = 1; //horizontal is set to 1 so that the condition (horizontal != 0) is TRUE
				vertical = 0; //vertical is set to 0 so that the condition (vertical != 0) is FALSE 
			}
			else if (CP_Input_KeyTriggered(KEY_A) || CP_Input_KeyTriggered(KEY_LEFT))
			{

				direction = LEFT;//set direction to LEFT
				snecc[0].direction = LEFT;//set snake head direction LEFT
				horizontal = 1; //horizontal is set to 1 so that the condition (horizontal != 0) is TRUE
				vertical = 0; //vertical is set to 0 so that the condition (vertical != 0) is FALSE 
			}
		}
	}
	if (snecc[0].x != snecc[1].x) {
		if (horizontal != 0) { //check if snake is moving horizontal (along x axis) only when snake is moving along x axis, snake can turn up and down
			if (CP_Input_KeyTriggered(KEY_S) || CP_Input_KeyTriggered(KEY_DOWN))
			{
				++checkinit;//checking for initial state. Once button pressed, snake will move
				direction = DOWN; //set direction to DOWN
				snecc[0].direction = DOWN;//set snake head direction DOWN
				horizontal = 0; //horizontal is set to 0 so that the condition (horizontal != 0) is FALSE
				vertical = 1; //vertical is set to 1 so that the condition (vertical != 0) is TRUE 
			}
			else if (CP_Input_KeyTriggered(KEY_W) || CP_Input_KeyTriggered(KEY_UP))
			{
				++checkinit;//checking for initial state. Once button pressed, snake will move
				direction = UP;//set direction to UP
				snecc[0].direction = UP;//set snake head direction UP
				horizontal = 0; //horizontal is set to 0 so that the condition (horizontal != 0) is FALSE
				vertical = 1; //vertical is set to 1 so that the condition (vertical != 0) is TRUE 	
			}
		}
	}
}

//@brief : get new coords of snake
void move()
{

	if (checkinit > 0)//check if game has started
	{
		if (direction == RIGHT)
			xs += 1;//x axis +1
		else if (direction == LEFT)
			xs -= 1;//x axis -1
		else if (direction == UP)
			ys -= 1;//y axis -1
		else if (direction == DOWN)
			ys += 1;//y axis +1

		for (int i = size - 1; i > 0; i--)
		{
			snecc[i] = snecc[i - 1];//setting each snecc instance to the prev snecc instance
		}
		snecc[0].x = (float)xs;//setting head X coords
		snecc[0].y = (float)ys;//setting head Y coords
		snecc[0].direction = (float)direction;//setting head direction
	}

}

//@brief : draw snake, food and background
void draw()
{
	//draw grass background
	CP_Image_Draw(grass, (CENTER_X * GRID_SIZE), (CENTER_Y * GRID_SIZE), (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight(), 255);
	//draw apple
	CP_Image_Draw(food, (apul.x * GRID_SIZE) - GRID_OFFSET, (apul.y * GRID_SIZE) - GRID_OFFSET, 60, 60, 255);
	//draw peach
	CP_Image_Draw(peachy, (peach.x * GRID_SIZE) - GRID_OFFSET, (peach.y * GRID_SIZE) - GRID_OFFSET, 60, 60, 255);
	//draw orange
	CP_Image_Draw(orangey, (orange.x * GRID_SIZE) - GRID_OFFSET, (orange.y * GRID_SIZE) - GRID_OFFSET, 60, 60, 255);

	//draw snake body and tail 
	for (int i = 0; i < size; ++i)
	{
		if (i == size - 1)//check for snake TAIL
		{
			//checking for snake TAIL direction
			if (snecc[i].direction == RIGHT)
				CP_Image_Draw(tail, (snecc[i].x * GRID_SIZE) - GRID_OFFSET, (snecc[i].y * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
			else if (snecc[i].direction == LEFT)
				CP_Image_Draw(taill, (snecc[i].x * GRID_SIZE) - GRID_OFFSET, (snecc[i].y * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
			else if (snecc[i].direction == UP)
				CP_Image_Draw(tailu, (snecc[i].x * GRID_SIZE) - GRID_OFFSET, (snecc[i].y * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
			else if (snecc[i].direction == DOWN)
				CP_Image_Draw(taild, (snecc[i].x * GRID_SIZE) - GRID_OFFSET, (snecc[i].y * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
		}
		else if (i == 0)//check for snake HEAD
		{
			//checking for snake HEAD direction
			if (snecc[0].direction == RIGHT)
				CP_Image_Draw(headr, (snecc[0].x * GRID_SIZE) - GRID_OFFSET, (snecc[0].y * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
			else if (snecc[0].direction == LEFT)
				CP_Image_Draw(headl, (snecc[0].x * GRID_SIZE) - GRID_OFFSET, (snecc[0].y * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
			else if (snecc[0].direction == UP)
				CP_Image_Draw(headu, (snecc[0].x * GRID_SIZE) - GRID_OFFSET, (snecc[0].y * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
			else if (snecc[0].direction == DOWN)
				CP_Image_Draw(headd, (snecc[0].x * GRID_SIZE) - GRID_OFFSET, (snecc[0].y * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
		}
		else if (i < size - 1)//check for snake BODY
		{
			CP_Image_Draw(body, (snecc[i].x * GRID_SIZE) - GRID_OFFSET, (snecc[i].y * GRID_SIZE) - GRID_OFFSET, GRID_SIZE, GRID_SIZE, 255);
		}

	}
}

//@brief : get new coords of food, increment size, calculate velocity, calculate totalscore and decrement interval
void grow()
{
	if ((snecc[0].x == apul.x) && (snecc[0].y == apul.y))	//if snake head coord is == apple
	{
		CP_Sound_Play(eatsound);//Play sound
		interval -= 0.0025f;//make snake faster
		velocity = 0.8f / interval;//calc velocity
		totalScore += 10;//add totalscore
		++size;//increment size
		
		while (1) {
			apul.x = (float)CP_Random_RangeInt(2, GW - 1);//getting apple X coords
			apul.y = (float)CP_Random_RangeInt(2, GH - 1);//getting apple Y coords
			if (((peach.x == apul.x) && (peach.y == apul.y)) || ((apul.x == orange.x) && (apul.y == orange.y)))//check if apple is on peach or orange
			{
				apul.x = (float)CP_Random_RangeInt(2, GW - 1);//getting apple X coords if cond is TRUE
				apul.y = (float)CP_Random_RangeInt(2, GH - 1);//getting apple Y coords if cond is TRUE
			}
			for (int i = 0; i < size; ++i)
			{
				if ((apul.x != snecc[i].x) || (apul.y != snecc[i].y)) { //checking if apple is NOT on snake 
					++chk;//if cond is true chk ++ (if chk is same as size that means condition is TRUE for WHOLE snake)
				}
			}
			if (chk == size)//if chk is the same as size
			{
				chk = 0;//reinit chk
				break;//break from loop
			}
			chk = 0;//reinit chk for next for loop instance
		}
	}
	if ((snecc[0].x == peach.x) && (snecc[0].y == peach.y))	//if snake head coord is == peach
	{
		CP_Sound_Play(eatsound);//Play sound
		interval -= 0.0025f;//make snake faster
		velocity = 0.8f / interval;//calc velocity
		totalScore += 10;//add totalscore
		++size;//increment size
		while (1) {
			peach.x = (float)CP_Random_RangeInt(2, GW - 1);//getting peach X coords
			peach.y = (float)CP_Random_RangeInt(2, GH - 1);//getting peach Y coords
			if (((peach.x == apul.x) && (peach.y == apul.y)) || ((peach.x == orange.x) && (peach.y == orange.y)))//check if peach is on apple or orange
			{
				peach.x = (float)CP_Random_RangeInt(2, GW - 1);//getting peach X coords if cond is TRUE
				peach.y = (float)CP_Random_RangeInt(2, GH - 1);//getting peach Y coords if cond is TRUE
			}
			for (int i = 0; i < size; ++i)
			{
				if ((peach.x != snecc[i].x) || (peach.y != snecc[i].y)) {//checking if peach is NOT on snake 
					++chk;//if cond is true chk ++ (if chk is same as size that means condition is TRUE for WHOLE snake)
				}
			}
			if (chk == size)//if chk is the same as size
			{
				chk = 0;//reinit chk
				break;//break from loop
			}
			chk = 0;//reinit chk for next for loop instance
		}
	}
	if ((snecc[0].x == orange.x) && (snecc[0].y == orange.y))	//if snake head coord is == orange
	{
		CP_Sound_Play(eatsound);//Play sound
		interval -= 0.0025f;//make snake faster
		velocity = 0.8f / interval;//calc velocity
		totalScore += 10;//add totalscore
		++size;//increment size
		while (1) {
			orange.x = (float)CP_Random_RangeInt(2, GW - 1);//getting orange X coords
			orange.y = (float)CP_Random_RangeInt(2, GH - 1);//getting orange Y coords
			if (((peach.x == orange.x) && (peach.y == orange.y)) || ((apul.x == orange.x) && (apul.y == orange.y)))//check if orange is on apple or peach
			{
				orange.x = (float)CP_Random_RangeInt(2, GW - 1);//getting orange X coords if cond is TRUE
				orange.y = (float)CP_Random_RangeInt(2, GH - 1);//getting orange Y coords if cond is TRUE
			}
			for (int i = 0; i < size; ++i)
			{
				if ((orange.x != snecc[i].x) || (orange.y != snecc[i].y)) {//checking if orange is NOT on snake 
					++chk;//if cond is true chk ++ (if chk is same as size that means condition is TRUE for WHOLE snake)
				}
			}
			if (chk == size)//if chk is the same as size
			{
				chk = 0;//reinit chk
				break;//break from loop
			}
			chk = 0;//reinit chk for next for loop instance
		}
	}
}


//@brief : check if player meets gameover conditions
void gameover() {

	for (int x = 1; x < size; ++x)		//if snake hit itself
	{
		if ((snecc[0].x == snecc[x].x) && (snecc[0].y == snecc[x].y))//check for snake head with every instance of snake
		{
			CP_Sound_StopAll();//stop music
			CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);//launch game over menu
		}
	}

	if (snecc[0].y <= 1)				//if snake hit wall top
	{
		CP_Sound_StopAll();//stop music
		CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);//launch game over menu
	}
	else if (snecc[0].y >= GH)			//if snake hit wall bottom
	{
		CP_Sound_StopAll();//stop music
		CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);//launch game over menu
	}
	if (snecc[0].x <= 1)				//if snake hit wall left
	{
		CP_Sound_StopAll();//stop music
		CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);//launch game over menu
	}
	else if (snecc[0].x >= GW)			//if snake hit wall right
	{
		CP_Sound_StopAll();//stop music
		CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);//launch game over menu
	}


}

//@brief : update snake
void snecc_update()
{
	//activate pause
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		++pause;//change pause state
	}

	//if pause
	if (pause == 3)
	{
		draw();//call function draw
		border();//call function border
		grow();//call function grow
		CP_Font_DrawText("PAUSED", (ww / 2) - GRID_OFFSET, (wh / 2));//show pause on game screen
	}
	else
	{
		timeSurvived += CP_System_GetSeconds();//get total time survived
		if (((int)timeSurvived % 15 == 0))//for every 15 sec passed, score +1
		{
			if (checkinit > 0)//check if game has started
				totalScore += 1;//totalscore add 1
		}

		key_input();//call function key_input
		timer += CP_System_GetDt();//timer += delta time
		if (timer >= interval)//check if timer is more than interval
		{
			timer -= interval;//timer -= interval to make game faster
			grow();//call function grow
			move();//call function move
		}
		draw();//call function draw
		border();//call function border
		gameover();//call function gameover
		pause = 2;//set pause state
	}
}

//@brief : free loaded resources
void snecc_exit()
{
	//free images
	CP_Image_Free(&headr);
	CP_Image_Free(&headl);
	CP_Image_Free(&headu);
	CP_Image_Free(&headd);
	CP_Image_Free(&body);
	CP_Image_Free(&tail);
	CP_Image_Free(&taill);
	CP_Image_Free(&tailu);
	CP_Image_Free(&taild);
	CP_Image_Free(&food);
	CP_Image_Free(&wall);
	CP_Image_Free(&grass);

	//free sound
	CP_Sound_Free(eatsound);
	CP_Sound_Free(bgm);

	//set values of snecc to all 0
	memset(snecc, 0, sizeof(snecc));

	size = 5;//reinit size
	snecc[0].direction = RIGHT;//reinit head direction
	snecc[0].x = CENTER_X;//reininit head x coord
	snecc[0].y = CENTER_Y;//reinint head y coord

	horizontal = 1;//reinit horizontal state
	vertical = 0;//reinit vertical state
	checkinit = 0;//reiinit checkinit
	xs = CENTER_X;//set head to center
	ys = CENTER_Y;//set head to center
	timer = 0;//reinit timer
	chk = 0;//reinit chk
	interval = 0.12f;//reinit speed of snake
	velocity = 6.67f;//reinint velocity
	totalScore = 0;//reinit total score
	timeSurvived = 0;//reinint time survived
}