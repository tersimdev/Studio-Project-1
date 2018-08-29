// This is the main file for the game logic and function
//
//
#include "game.h"
#include <iostream>
#include <iomanip>
#include <sstream>



double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
bool    g_abFlags[flagCount] = { 0 };
int		g_menuSelection;

string filename1 = "Saves/SAVE 1.txt";
string mapname1 = "Saves/MAP 1.txt";
string filename2 = "Saves/SAVE 2.txt";
string mapname2 = "Saves/MAP 2.txt";
string filename3 = "Saves/SAVE 3.txt";
string mapname3 = "Saves/MAP 3.txt";

string temporary1 = "Saves/Temporary save.txt";// save data and map when player enters minigame
string temporarymap1 = "Saves/Temporary map.txt";

/*For Snake*/
unsigned int i;
unsigned int j;
bool goleft;
bool goright;
bool goup;
bool godown;
bool spawnapple;
unsigned int lastbutton; //1=up,2=left,3=right,4=down
unsigned int score = 0;
unsigned int index = 0;
bool spawnonsnake;
std::vector<unsigned int> snakepart;
int snakeini = 0;
COORD PrevLoc;//previous location of apple
int Snakewincondition = 3;
string playerscore = "Score: ";
SNAKELAD g_snake;
SNAKELAD g_apple;
std::vector<SNAKELAD> SnakeBody;

/*For pong*/
unsigned int pongScore = 0;
int pongWinCondition = 2;
/* For pacman*/
int countCoin = 10;
PacmanMonster    g_monster1; // monster1 
PacmanMonster    g_monster2; // monster2
PacmanMonster    g_monster3; // monster3
PacmanMonster    g_monster4; // monster4
PacmanMonster    g_monster5; // monster5

// Console object
Console g_Console(199, 51, "RISE OF THE TOMB EXPLORING N00BS");
// Game specific variables here
//Map		g_map("Levels/astarTest.txt"); //map for astar testing
Map			g_map(0); //map
aStar		astar(g_map.cols, g_map.rows, &g_Console, &g_map);
vector<Node>path; //for astar path visualization
SGameChar	g_sChar1((char)3, 0x0C, &g_map, 1); //player1
SGameChar	g_sChar2((char)3, 0x0A, &g_map, 2); //player2
Pong		g_sPuck1((char)254, 0x0E, { 90, 22 }, { 1, 1 });
Pong		g_sPuck2((char)254, 0x0E, { 50, 22 }, { -1, 1 });
Slider		g_sSlider1(0x0C, { 35, 20 });
Slider		g_sSlider2(0x0A, { 133, 20 });
Trigger		g_trigger(&g_map, &g_Console);
Quiz		g_quiz(0); //quiz
Boss*		g_boss = NULL; //boss
Cube		g_cube; //cube reward
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
// these are to prevent key bouncing, so we won't trigger keypresses more than once
double	g_dBounceTimeNorm;
double  g_dBounceTimeUI;
double  g_dBounceTimeMove[NumOfPlayers];
double  g_dBounceTimeAction[NumOfPlayers];
double  g_dBounceTimeEnemy[NumOfPlayers];
double  g_dBounceTimeMonster;
double	g_dBounceTimePuck;

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init(void)
{
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTimeNorm = 0.0;
	g_dBounceTimeUI = 0.0;
	for (int i = 0; i < NumOfPlayers; i++)
	{
		g_dBounceTimeMove[i] = 0.0;
		g_dBounceTimeAction[i] = 0.0;
	}

	//
	PlaySound(TEXT("Sounds/bgm.wav"), NULL, SND_LOOP | SND_ASYNC);
	// Beep(523, 500);

	// pacman monster
	g_monster1.m_cLocation.X = 98;
	g_monster1.m_cLocation.Y = 28;

	g_monster2.m_cLocation.X = 98;
	g_monster2.m_cLocation.Y = 35;

	g_monster3.m_cLocation.X = 121;
	g_monster3.m_cLocation.Y = 43;

	g_monster4.m_cLocation.X = 115;
	g_monster4.m_cLocation.Y = 33;

	g_monster5.m_cLocation.X = 76;
	g_monster5.m_cLocation.Y = 43;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;

	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");

	//prevent selection of text- disable quick edit mode
	g_Console.setConsoleMode(ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

	//to pass tutorial level
	g_abFlags[tutoDone] = true;

	//init variables
	g_menuSelection = 0;

	/*Snake*/
	spawnapple = true;
	applelocation(spawnapple);
	g_snake.m_cLocation.X = g_Console.getConsoleSize().X / 2;
	g_snake.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
	g_snake.m_bActive = true;
	g_apple.m_cLocation.X;
	g_apple.m_cLocation.Y;
	g_apple.m_bActive = true;
	spawnapple = false;

}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: //none
		break;
	case S_MENU: //ui
	case S_LOADSAVE: //ui
	case S_GAME: //game
	case S_SNAKEMINIGAME: //snek
	case S_PACMAN://pacman
	case S_BOSS: //boss
	case S_RUBIKS: //rubiks cube
	case S_SAVE:
	{
		g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
		g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
		g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
		g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
		g_abKeyPressed[K_RCTRL] = isKeyPressed(VK_RCONTROL);
		g_abKeyPressed[K_W] = isKeyPressed(0x57);
		g_abKeyPressed[K_A] = isKeyPressed(0x41);
		g_abKeyPressed[K_S] = isKeyPressed(0x53);
		g_abKeyPressed[K_D] = isKeyPressed(0x44);
		g_abKeyPressed[K_LSHIFT] = isKeyPressed(VK_LSHIFT);

		g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
		g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
		g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
		g_abKeyPressed[K_BACKSPACE] = isKeyPressed(VK_BACK);

		//cheats
		g_abKeyPressed[K_0] = isKeyPressed(0x30);
	}
	break;
	case S_QUIZ_B:
	case S_QUIZ_E:
	{
		g_abKeyPressed[K_A] = isKeyPressed(0x41);
		g_abKeyPressed[K_B] = isKeyPressed(0x42);
		g_abKeyPressed[K_C] = isKeyPressed(0x43);
		g_abKeyPressed[K_D] = isKeyPressed(0x44);
		g_abKeyPressed[K_E] = isKeyPressed(0x45);
		g_abKeyPressed[K_F] = isKeyPressed(0x46);
		g_abKeyPressed[K_G] = isKeyPressed(0x47);
		g_abKeyPressed[K_H] = isKeyPressed(0x48);
		g_abKeyPressed[K_I] = isKeyPressed(0x49);
		g_abKeyPressed[K_J] = isKeyPressed(0x4A);
		g_abKeyPressed[K_K] = isKeyPressed(0x4B);
		g_abKeyPressed[K_L] = isKeyPressed(0x4C);
		g_abKeyPressed[K_M] = isKeyPressed(0x4D);
		g_abKeyPressed[K_N] = isKeyPressed(0x4E);
		g_abKeyPressed[K_O] = isKeyPressed(0x4F);
		g_abKeyPressed[K_P] = isKeyPressed(0x50);
		g_abKeyPressed[K_Q] = isKeyPressed(0x51);
		g_abKeyPressed[K_R] = isKeyPressed(0x52);
		g_abKeyPressed[K_S] = isKeyPressed(0x53);
		g_abKeyPressed[K_T] = isKeyPressed(0x54);
		g_abKeyPressed[K_U] = isKeyPressed(0x55);
		g_abKeyPressed[K_V] = isKeyPressed(0x56);
		g_abKeyPressed[K_W] = isKeyPressed(0x57);
		g_abKeyPressed[K_X] = isKeyPressed(0x58);
		g_abKeyPressed[K_Y] = isKeyPressed(0x59);
		g_abKeyPressed[K_Z] = isKeyPressed(0x5A);
		g_abKeyPressed[K_0] = isKeyPressed(0x30);
		g_abKeyPressed[K_1] = isKeyPressed(0x31);
		g_abKeyPressed[K_2] = isKeyPressed(0x32);
		g_abKeyPressed[K_3] = isKeyPressed(0x33);
		g_abKeyPressed[K_4] = isKeyPressed(0x34);
		g_abKeyPressed[K_5] = isKeyPressed(0x35);
		g_abKeyPressed[K_6] = isKeyPressed(0x36);
		g_abKeyPressed[K_7] = isKeyPressed(0x37);
		g_abKeyPressed[K_8] = isKeyPressed(0x38);
		g_abKeyPressed[K_9] = isKeyPressed(0x39);

		g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
		g_abKeyPressed[K_BACKSPACE] = isKeyPressed(VK_BACK);
		g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
		break;
	}
	case S_PONG:
	{
		g_abKeyPressed[K_S] = isKeyPressed(0x53);
		g_abKeyPressed[K_W] = isKeyPressed(0x57);
		g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
		g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
		break;
	}
	break;
	}
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_MENU: mainMenu();
		break;
	case S_LOADSAVE: loadSave();
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	case S_BOSS: bossMode();
		break;
	case S_QUIZ_B:
	case S_QUIZ_E: quizMode();
		break;
	case S_SNAKEMINIGAME:SnakeGameplay();
		break;
	case S_RUBIKS: cubeControl();
		break;
	case S_PACMAN: pacmanMode();
		break;
	case S_PONG: pongMode();
		break;
	case S_SAVE: SAVEUI();
		break;
	}
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: renderSplashScreen();
		break;
	case S_MENU: renderMainMenu();
		break;
	case S_LOADSAVE: renderLoadSave();
		break;
	case S_GAME: renderGame();
		break;
	case S_BOSS: renderBossMode();
		break;
	case S_QUIZ_B:
	case S_QUIZ_E: renderQuiz();
		break;
	case S_SNAKEMINIGAME: snakeminigame();
		break;
	case S_RUBIKS: renderCube();
		break;
	case S_PACMAN: renderPacmanMode();
		break;
	case S_PONG: renderPong();
		break;
	case S_SAVE: RenderSAVEUI();
		break;
	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_dElapsedTime > 1.0) // wait for 3 seconds to switch to main menu mode, else do nothing
		g_eGameState = S_MENU;
}

void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "s";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());
}

void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x00);
}







/******************************************MAIN GAME******************************************/


void gameplay()         // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
	moveCharacter();    // moves the character, collision detection, physics, etc
	checkForTiles();	// checks for special tiles which player can interact with
	actionsListener();	// other action keys like shooting, etc
	enemyMovement();	//enemy movement
}

void moveCharacter()
{
	g_abFlags[moving1] = false;
	g_abFlags[moving2] = false;
	if (g_dBounceTimeMove[0] < g_dElapsedTime && g_sChar1.m_bActive)
	{
		//player 1
		if (g_abKeyPressed[K_W] && g_sChar1.m_cLocation.Y > 1)
		{
			//Beep(1440, 30);
			g_sChar1.direction = { 0,-1 };
			g_abFlags[moving1] = true;
		}
		else if (g_abKeyPressed[K_S] && g_sChar1.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
		{
			//Beep(1440, 30);
			g_sChar1.direction = { 0, 1 };
			g_abFlags[moving1] = true;
		}
		else if (g_abKeyPressed[K_A] && g_sChar1.m_cLocation.X > 0)
		{
			//Beep(1440, 30)
			g_sChar1.direction = { -1, 0 };
			g_abFlags[moving1] = true;
		}
		else if (g_abKeyPressed[K_D] && g_sChar1.m_cLocation.X < g_Console.getConsoleSize().X - 1)
		{
			//Beep(1440, 30);
			g_sChar1.direction = { 1, 0 };
			g_abFlags[moving1] = true;
		}
	}
	if (g_dBounceTimeMove[1] < g_dElapsedTime&& g_sChar2.m_bActive)
	{
		//player 2
		if (g_abKeyPressed[K_UP] && g_sChar2.m_cLocation.Y > 1)
		{
			//Beep(1440, 30);
			g_sChar2.direction = { 0,-1 };
			g_abFlags[moving2] = true;
		}
		else if (g_abKeyPressed[K_DOWN] && g_sChar2.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
		{
			//Beep(1440, 30);
			g_sChar2.direction = { 0, 1 };
			g_abFlags[moving2] = true;
		}
		else if (g_abKeyPressed[K_LEFT] && g_sChar2.m_cLocation.X > 0)
		{
			//Beep(1440, 30)
			g_sChar2.direction = { -1, 0 };
			g_abFlags[moving2] = true;
		}
		else if (g_abKeyPressed[K_RIGHT] && g_sChar2.m_cLocation.X < g_Console.getConsoleSize().X - 1)
		{
			//Beep(1440, 30);
			g_sChar2.direction = { 1, 0 };
			g_abFlags[moving2] = true;
		}
	}

	if (g_abFlags[moving1])
	{
		//calculating future location
		g_sChar1.m_futureLocation = ADDCOORDS(g_sChar1.m_cLocation, g_sChar1.direction);
		//check if colliding with collidables in map, or if moving towards player 2
		if (!g_map.collideWithWall(g_sChar1.m_futureLocation)
			&& !EQUCOORDS(g_sChar1.m_futureLocation, g_sChar2.m_cLocation))
			g_sChar1.m_cLocation = ADDCOORDS(g_sChar1.m_cLocation, g_sChar1.direction);
		//check bounce time

		g_dBounceTimeMove[0] = g_dElapsedTime + 0.05; // fazt
	}
	if (g_abFlags[moving2])
	{
		//calculating future location
		g_sChar2.m_futureLocation = ADDCOORDS(g_sChar2.m_cLocation, g_sChar2.direction);
		//check if colliding with collidables in map, or if moving towards player 2
		if (!g_map.collideWithWall(g_sChar2.m_futureLocation)
			&& !EQUCOORDS(g_sChar2.m_futureLocation, g_sChar1.m_cLocation))
			g_sChar2.m_cLocation = ADDCOORDS(g_sChar2.m_cLocation, g_sChar2.direction);
		//check bounce time

		g_dBounceTimeMove[1] = g_dElapsedTime + 0.05; // fazt
	}
}

void actionsListener()
{
	bool eventHappened[NumOfPlayers] = { false, false };
	if (g_dBounceTimeAction[0] < g_dElapsedTime)
	{
		if (g_abKeyPressed[K_LSHIFT] && (g_sChar1.gun == NULL || !g_abFlags[shooting]))
		{
			g_abFlags[shooting] = true;
			g_sChar1.gun = new Gun(g_sChar1.m_cLocation, g_sChar1.direction);
			eventHappened[0] = true;
			PlaySound(TEXT("Sounds/shoot.wav"), NULL, SND_SYNC | SND_ASYNC);
		}
	}
	if (g_dBounceTimeAction[1] < g_dElapsedTime)
	{
		if (g_abKeyPressed[K_SPACE])
		{
			//temp key to test stuff
			eventHappened[1] = true;
		}
	}
	if (eventHappened[0])
		g_dBounceTimeAction[0] = g_dElapsedTime + 0.8; // slow
	if (eventHappened[1])
		g_dBounceTimeAction[1] = g_dElapsedTime + 0.5; // slow

	if (g_sChar1.m_bActive == false && g_sChar2.m_bActive == false)//test
	{
		g_eGameState = S_MENU;
	}
}

void processUserInput()
{
	bool eventHappened = false;
	if (g_dBounceTimeNorm > g_dElapsedTime)
		return;
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
	{
		switch (g_eGameState)
		{
		case S_SAVE:
			g_eGameState = S_GAME;
			break;
		case S_GAME:
			g_eGameState = S_SAVE;
			break;
		}
		eventHappened = true;
	}
	if (g_abKeyPressed[K_BACKSPACE])
	{
		switch (g_eGameState)
		{
		case S_BOSS:
			LOAD(temporary1);
			LOADMAP(temporarymap1);
			g_eGameState = S_GAME;
			PlaySound(TEXT("Sounds/bgm.wav"), NULL, SND_SYNC | SND_ASYNC);
			countCoin = 10;
			break;
		case S_SNAKEMINIGAME:
		case S_RUBIKS:
			g_eGameState = S_GAME;
			PlaySound(TEXT("Sounds/bgm.wav"), NULL, SND_SYNC | SND_ASYNC);
			break;
		}
		eventHappened = true;
	}
	if (g_abKeyPressed[K_0])
	{
		g_map.updateMap(); //loads next map, wraping around
		g_trigger.initTrigger(&g_map, &g_Console); //reinits all triggers for new map
		g_abFlags[hasKey] = false; //lose key
		g_abFlags[tutoDone] = false;
		g_abFlags[snakeDone] = false; //lose key
		g_abFlags[bossDone] = false; //lose key
		g_abFlags[pacmanDone] = false; //lose key
		g_abFlags[pongDone] = false;
		g_sChar1.m_cLocation = g_map.findChar('P');
		g_sChar2.m_cLocation = g_map.findChar('S');
		eventHappened = true;
	}


	if (eventHappened)
		g_dBounceTimeNorm = g_dElapsedTime + 0.5; // avg
}

void checkForTiles()
{
	if (g_abFlags[moving1] || g_abFlags[moving2])
	{
		SGameChar* player = &g_sChar1;
		if (g_abFlags[moving2])
			player = &g_sChar2;

		if (g_map.findCharExists(player->m_futureLocation, 'N')
			&& (g_abFlags[tutoDone] || g_abFlags[bossDone] || g_abFlags[snakeDone] || g_abFlags[pacmanDone] || g_abFlags[pongDone]))
		{
			g_map.updateMap(); //loads next map, wraping around
			g_trigger.initTrigger(&g_map, &g_Console); //reinits all triggers for new map
			g_abFlags[hasKey] = false; //lose key
			g_abFlags[tutoDone] = false;
			g_abFlags[snakeDone] = false; //lose key
			g_abFlags[bossDone] = false; //lose key
			g_abFlags[pacmanDone] = false; //lose key
			g_abFlags[pongDone] = false;
			//moving the player that triggered it
			if (player->m_cLocation.X > g_Console.getConsoleSize().X * 0.9)
			{
				player->m_cLocation.X = 3;
			}
			else if (player->m_cLocation.X < g_Console.getConsoleSize().X * 0.1)
			{
				player->m_cLocation.X = g_Console.getConsoleSize().X - 4;
			}
			else if (player->m_cLocation.Y > g_Console.getConsoleSize().Y * 0.75)
			{
				player->m_cLocation.Y = 3;
			}
			else if (player->m_cLocation.Y < g_Console.getConsoleSize().Y * 0.25)
			{
				player->m_cLocation.Y = g_Console.getConsoleSize().Y - 4;
			}
			//moving the otehr player
			if (g_abFlags[moving2])
			{
				g_sChar1.m_cLocation.X = player->m_cLocation.X + 1;
				g_sChar1.m_cLocation.Y = player->m_cLocation.Y;
			}
			else
			{
				g_sChar2.m_cLocation.X = player->m_cLocation.X - 1;
				g_sChar2.m_cLocation.Y = player->m_cLocation.Y;
			}
			PlaySound(TEXT("Sounds/tada.wav"), NULL, SND_SYNC | SND_ASYNC);
		}
		//gates
		if (!g_abFlags[bossDone] && g_abFlags[hasKey] && g_map.findCharExists(player->m_futureLocation, 'U')) //boss
		{
			SAVE(temporary1);
			SAVEMAP(temporarymap1);
			//
			g_boss = new Boss(&g_map, &g_Console, &g_sChar1.m_cLocation, &g_sChar2.m_cLocation, g_dElapsedTime);
			g_trigger = Trigger(&g_map, &g_Console); //to access leftover enemies
			for (auto i : g_trigger.allEnemies)
			{
				i->destroyEnemy(&g_map);
			}
			g_eGameState = S_BOSS;
			// PlaySound(TEXT("Sounds/minigame.wav"), NULL, SND_SYNC | SND_ASYNC);-> not running this
			PlaySound(TEXT("Sounds/boss.wav"), NULL, SND_SYNC | SND_ASYNC);
		}
		else if (!g_abFlags[snakeDone] && g_abFlags[hasKey] && g_map.findCharExists(player->m_futureLocation, 'M')) //snake
		{
			g_eGameState = S_SNAKEMINIGAME;
			PlaySound(TEXT("Sounds/minigame.wav"), NULL, SND_SYNC | SND_ASYNC);
		}
		else if (!g_abFlags[pacmanDone] && g_abFlags[hasKey] && g_map.findCharExists(player->m_futureLocation, 'R')) //pacman
		{
			SAVE(temporary1);
			SAVEMAP(temporarymap1);
			//
			//intialising position of player
			g_sChar1.m_cLocation.X = 99;
			g_sChar1.m_cLocation.Y = 30;
			g_sChar2.m_cLocation.X = 98;
			g_sChar2.m_cLocation.Y = 31;
			g_map.loadMap("Levels/PACMAN.txt");

			/* If this is added: there is null ptr error */
			g_trigger = Trigger(&g_map, &g_Console);
			for (auto i : g_trigger.allEnemies)
			{
				i->destroyEnemy(&g_map);
			}
			g_eGameState = S_PACMAN;
			PlaySound(TEXT("Sounds/minigame.wav"), NULL, SND_SYNC | SND_ASYNC);
		}
		else if (!g_abFlags[pongDone] && g_abFlags[hasKey] && g_map.findCharExists(player->m_futureLocation, 'F')) // pong
		{
			SAVE(temporary1);
			SAVEMAP(temporarymap1);
			//
			g_map.loadMap("Levels/pong.txt");
			g_trigger = Trigger(&g_map, &g_Console);
			for (auto i : g_trigger.allEnemies)
			{
				i->destroyEnemy(&g_map);
			}
			g_eGameState = S_PONG;
			PlaySound(TEXT("Sounds/minigame.wav"), NULL, SND_SYNC | SND_ASYNC);
		}
		else if (g_map.findCharExists(player->m_futureLocation, 'T')) //rubiks cube
		{
			g_eGameState = S_RUBIKS;
			PlaySound(TEXT("Sounds/minigame.wav"), NULL, SND_SYNC | SND_ASYNC);
		}
		//boulders
		if (g_map.findCharExists(g_sChar1.m_futureLocation, 'B'))
		{
			g_trigger.boulder = g_trigger.findBoulder(g_sChar1.m_futureLocation);
			g_trigger.boulder->moveBoulder(&g_map, &g_sChar1, &g_Console);
			PlaySound(TEXT("Sounds/moveboulder.wav"), NULL, SND_SYNC | SND_ASYNC);

		}
		if (g_map.findCharExists(g_sChar2.m_futureLocation, 'B'))
		{
			if (g_abFlags[hasPickaxe] && g_abKeyPressed[K_RCTRL])
			{
				g_trigger.boulder = g_trigger.findBoulder(g_sChar2.m_futureLocation);
				g_trigger.boulder->destroyBoulder(&g_map);
				PlaySound(TEXT("Sounds/pickaxe.wav"), NULL, SND_SYNC | SND_ASYNC);
			}
		}
		//pickaxe
		if (g_map.findCharExists(g_sChar2.m_futureLocation, 'I'))
		{
			g_abFlags[hasPickaxe] = true;
			g_map.removeChar(g_sChar2.m_futureLocation);
			PlaySound(TEXT("Sounds/pickup.wav"), NULL, SND_SYNC | SND_ASYNC);
		}
		//key
		if (g_map.findCharExists(g_sChar2.m_futureLocation, 'K'))
		{
			g_abFlags[hasKey] = true;
			g_map.removeChar(g_sChar2.m_futureLocation);
			PlaySound(TEXT("Sounds/pickup.wav"), NULL, SND_SYNC | SND_ASYNC);
		}
		else if (g_map.findCharExists(g_sChar1.m_futureLocation, 'K'))
		{
			g_abFlags[hasKey] = true;
			g_map.removeChar(g_sChar1.m_futureLocation);
			PlaySound(TEXT("Sounds/pickup.wav"), NULL, SND_SYNC | SND_ASYNC);

		}
	}
}

void enemyMovement()
{
	bool bMoving = false;
	Node start, dest;
	if (g_dBounceTimeEnemy[0] > g_dElapsedTime)
		return;
	for (unsigned int i = 0; i < g_trigger.allEnemies.size(); i++)
	{
		//randomise location
		g_trigger.allEnemies[i]->direction = g_trigger.allEnemies[i]->directionGen(g_dBounceTimeEnemy[0]);

		if (g_trigger.allEnemies[i]->isAggro(g_sChar2.m_cLocation))
		{
			//A* to find best path
			start.X = g_trigger.allEnemies[i]->m_cLocation.X;
			start.Y = g_trigger.allEnemies[i]->m_cLocation.Y;
			dest.X = g_sChar2.m_cLocation.X;
			dest.Y = g_sChar2.m_cLocation.Y;
			path = astar.aStarSearch(start, dest);
			if (!path.empty()) //find direction based on A* path
				g_trigger.allEnemies[i]->pathFindDir(path);
		}

		else if (g_trigger.allEnemies[i]->isAggro(g_sChar1.m_cLocation))
		{
			//A* to find best path
			start.X = g_trigger.allEnemies[i]->m_cLocation.X;
			start.Y = g_trigger.allEnemies[i]->m_cLocation.Y;
			dest.X = g_sChar1.m_cLocation.X;
			dest.Y = g_sChar1.m_cLocation.Y;
			path = astar.aStarSearch(start, dest);
			if (!path.empty()) //find direction based on A* path
				g_trigger.allEnemies[i]->pathFindDir(path);
		}

		//calculating future location
		g_trigger.allEnemies[i]->m_futureLocation
			= ADDCOORDS(g_trigger.allEnemies[i]->m_cLocation, g_trigger.allEnemies[i]->direction);
		if (!g_map.collideWithWall(g_trigger.allEnemies[i]->m_futureLocation))
		{
			g_trigger.allEnemies[i]->moveEnemy(&g_map, &g_Console);
			bMoving = true;
		}

		//if quiz triggered
		if (g_trigger.allEnemies[i]->enemyAttack(g_sChar1.m_cLocation) || g_trigger.allEnemies[i]->enemyAttack(g_sChar2.m_cLocation))
		{
			g_trigger.allEnemies[i]->destroyEnemy(&g_map);
			g_quiz.query();
			g_eGameState = S_QUIZ_E;
			PlaySound(TEXT("Sounds/collidemonster.wav"), NULL, SND_SYNC | SND_ASYNC);
		}
	}

	if (bMoving)
	{
		g_dBounceTimeEnemy[0] = g_dElapsedTime + 0.1;
	}

}


void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = (SHORT)(c.X * 0.5 - 7);
	g_Console.writeToBuffer(c, "Starting in 3s", 0x03);
	c.Y += 1;
	c.X = (SHORT)(g_Console.getConsoleSize().X * 0.5 - 21);
	g_Console.writeToBuffer(c, "Change console font-size to suit your needs", 0x09);
	c.Y += 1;
	c.X = (SHORT)(g_Console.getConsoleSize().X * 0.5 - 9);
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
	renderMap();        // renders the map to the buffer first
	renderCharacter();  // renders the character into the buffer
	renderHealth();		// render character health bar
	renderItems();		// renders items into buffer

	if (g_abFlags[shooting]) // renders bullet if shooting
		renderBullet();
	if (g_abKeyPressed[K_SPACE] && !path.empty())
	{
		for (auto i : path) //for astar path visualization
		{
			g_Console.writeToBuffer(i, (char)176, 0x0F);
		}
	}

}

void renderMap()
{
	g_map.replaceAndRender(&g_Console); // render in map.cpp to prevent clutter here
}

void renderCharacter()
{
	// Draw the location of the players
	if (g_sChar1.m_bActive)
		g_Console.writeToBuffer(g_sChar1.m_cLocation, g_sChar1.symbol, g_sChar1.color);
	if (g_sChar2.m_bActive)
		g_Console.writeToBuffer(g_sChar2.m_cLocation, g_sChar2.symbol, g_sChar2.color);
}

void renderHealth()
{
	g_sChar1.playerUIPos = g_map.findChar('p');
	g_Console.writeToBuffer(g_sChar1.playerUIPos, g_sChar1.playerHPUI, g_sChar1.color);
	g_sChar2.playerUIPos = g_map.findChar('s');
	g_Console.writeToBuffer(g_sChar2.playerUIPos, g_sChar2.playerHPUI, g_sChar2.color);
}

void renderBullet()
{
	g_sChar1.gun->shoot(&g_sChar1);
	g_trigger.enemy = g_trigger.findEnemy(g_sChar1.gun->bulletPos);
	//check if bullet exceeds console or hits wall or out of range or hits enemy
	if (g_sChar1.gun->collision(&g_map, &g_Console))
	{
		if (g_trigger.enemy != NULL) //found enemy at bullet
			g_trigger.enemy->destroyEnemy(&g_map);
		delete g_sChar1.gun; //no more visual bullet
		g_abFlags[shooting] = false; //stops rendering
	}
	else
		g_Console.writeToBuffer(g_sChar1.gun->bulletPos, (char)254, 0x0E);
}



// Issue: after exiting boss gameplay or pacman:
// When player try to move boulder
// null ptr error



/****************************************BOSS GAMEPLAY****************************************/
// bgm added

void bossMode()
{
	moveCharacter();    // moves the character, collision detection, physics, etc
	processUserInput(); // for escaping the fight
	if (g_boss->dBounceTime > g_dElapsedTime)
		return;
	if (g_boss->numOfAttacks <= 0)
	{
		g_sChar1.color = 0x0C;
		g_sChar2.color = 0x0A;
		g_quiz.query();
		g_eGameState = S_QUIZ_B; //quiz
	}
	if (g_boss->active && (g_sChar1.m_bActive || g_sChar2.m_bActive))
	{
		//collison for each player
		if (g_sChar1.m_bActive && g_boss->collision(g_sChar1.m_cLocation))
		{
			g_sChar1.updateHealth(1, g_boss->getDmg(rand() % 15));
		}
		if (g_sChar2.m_bActive && g_boss->collision(g_sChar2.m_cLocation))
		{
			g_sChar2.updateHealth(2, g_boss->getDmg(rand() % 15));
		}

		//attacks
		if (g_dElapsedTime > g_boss->bossElapsedTime + g_boss->attackDura + g_boss->renderDelay)
		{
			//inits, called once every attack
			g_boss->attackIndex = rand() % 3;
			g_boss->initAttacks();
			g_boss->numOfAttacks--;
			g_boss->bossElapsedTime = g_dElapsedTime;
		}
		else if (g_dElapsedTime > g_boss->bossElapsedTime + g_boss->renderDelay + g_boss->attackDelay)
		{
			//attack, this is looped
			if (g_boss->attackIndex == 1)
			{
				g_boss->changePlayerColor(1, &g_sChar1.color);
				g_boss->changePlayerColor(2, &g_sChar2.color);
			}
			else
				g_boss->attack();
		}
		g_boss->dBounceTime = g_dElapsedTime + 0.07;
	}
	else if (!g_sChar1.m_bActive && !g_sChar2.m_bActive) // lose
	{
		//TEMPO, temporary, replace with loading last saved state function

		LOAD(temporary1);
		LOADMAP(temporarymap1);


		g_eGameState = S_GAME;
		g_trigger.initTrigger(&g_map, &g_Console);//reninit all triggers for new map
		PlaySound(TEXT("Sounds/bgm.wav"), NULL, SND_SYNC | SND_ASYNC);
	}
	else // win 
	{
		LOAD(temporary1);
		LOADMAP(temporarymap1);

		//TEMPO, temporary, replace with loading last saved state function

		g_eGameState = S_GAME;
		g_trigger.initTrigger(&g_map, &g_Console);//reninit all triggers for new map
		PlaySound(TEXT("Sounds/bgm.wav"), NULL, SND_SYNC | SND_ASYNC);
		g_abFlags[bossDone] = true;
	}
}

void renderBossMode()
{
	renderMap();
	renderCharacter();
	renderHealth();
	if (g_boss->active)
	{
		if (g_dElapsedTime > g_boss->bossElapsedTime + g_boss->renderDelay)
		{
			g_boss->renderBossAttack(&g_Console);
		}

	}
}









/***************************************RUBIKS CUBE***************************************/


void cubeControl()
{
	processUserInput(); //for escape

	bool eventHappened = false;
	if (g_dBounceTimeUI > g_dElapsedTime)
		return;
	//moves the cube
	if (g_abKeyPressed[K_W])
	{
		g_cube.moveR(1);
		eventHappened = true;
	}
	else if (g_abKeyPressed[K_S])
	{
		g_cube.moveR(-1);
		eventHappened = true;
	}
	else if (g_abKeyPressed[K_A])
	{
		g_cube.moveU(-1);
		eventHappened = true;
	}
	else if (g_abKeyPressed[K_D])
	{
		g_cube.moveU(1);
		eventHappened = true;
	}
	else if (g_abKeyPressed[K_UP])
	{
		g_cube.rotateY(1);
		eventHappened = true;
	}
	else if (g_abKeyPressed[K_DOWN])
	{
		g_cube.rotateY(-1);
		eventHappened = true;
	}
	else if (g_abKeyPressed[K_LEFT])
	{
		g_cube.rotateX(1);
		eventHappened = true;
	}
	else if (g_abKeyPressed[K_RIGHT])
	{
		g_cube.rotateX(-1);
		eventHappened = true;
	}
	if (eventHappened)
		g_dBounceTimeUI = g_dElapsedTime + 0.2; // avg
}

void renderCube()
{
	COORD c[6];
	c[0] = { 99, 24 };
	c[1] = { 105, 24 };
	c[2] = { 93, 24 };
	c[3] = { 99, 20 };
	c[4] = { 99, 28 };
	c[5] = { 99, 32 };
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			g_Console.writeToBuffer(c[i], 'O', g_cube.faces[i * 4 + j]);
			if (j == 0 || j == 2) c[i].X++;
			else
			{
				c[i].Y++;
				c[i].X--;
			}
		}
	}
	g_Console.writeToBuffer({ (SHORT)120, (SHORT)23 }, "2x2 RUBIKS CUBE", 0x0F);
	g_Console.writeToBuffer({ (SHORT)120, (SHORT)24 }, "WASD and Arrow Keys to manipulate", 0x0F);
	g_Console.writeToBuffer({ (SHORT)120, (SHORT)25 }, "Solve it if you can :)", 0x0F);
	g_Console.writeToBuffer({ (SHORT)120, (SHORT)26 }, "'Backspace' to exit", 0x0F);
}








/***************************************SNAKE GAME***************************************/
// sound added in, may add in bgm specific for this

void snakeminigame() //run mini game snake
{

	SnakeRenderMap();
	SnakerenderCharacter();
	Snakerenderapple();
	processUserInput();

	// sets the initial state for the game
}

void SnakeGameplay()
{
	Snakecollisiondetection();
	SnakemoveCharacter();
}

void SnakeRenderMap()
{

	COORD C = { 48,1 };
	std::string line;
	unsigned char box; //truncation error
	unsigned int rows;
	std::string map;
	std::ifstream snakegame("Levels/snakemap.txt");
	box = 219;
	rows = 48;
	if (!snakegame)
	{
		std::cerr << "File could not be opened" << std::endl;
		exit(1);
	}

	for (j = 0; j < rows; j++)
	{
		C.Y++;
		getline(snakegame, line);
		for (i = 0; i < line.length(); i++)
		{
			if (line[i] == 'z')
			{
				line[i] = box;
			}
			g_Console.writeToBuffer(C, line, 0x0F);
		}
	}
	snakegame.close();
	g_Console.writeToBuffer({ g_Console.getConsoleSize().X / 2,43 }, playerscore + std::to_string(score) + '/' + std::to_string(Snakewincondition), 0x0C);
}

SNAKELAD createSnakeBody(int X, int Y)
{
	SNAKELAD temp;
	temp.m_cLocation.X = X;
	temp.m_cLocation.Y = Y;
	temp.m_bActive = true;
	return temp;
}

void Snakerenderapple()
{
	int X = 0;
	int Y = 0;

	// Draw the location of the character
	WORD charColor = 0x0C;
	if (g_apple.m_bActive)
	{
		charColor = 0x0C;
	}
	g_Console.writeToBuffer(g_apple.m_cLocation, (char)235, charColor);

	if (((g_snake.m_cLocation.X) == (g_apple.m_cLocation.X)) && ((g_snake.m_cLocation.Y) == (g_apple.m_cLocation.Y)))
	{
		spawnapple = true;
		PlaySound(TEXT("Sounds/apple.wav"), NULL, SND_SYNC | SND_ASYNC);

		do
		{
			applelocation(spawnapple);
			for (i = 0; i < SnakeBody.size(); i++)
			{
				if (((g_apple.m_cLocation.X == SnakeBody[i].m_cLocation.X) && (g_apple.m_cLocation.Y == SnakeBody[i].m_cLocation.Y)) || ((g_apple.m_cLocation.X == g_snake.m_cLocation.X) && (g_apple.m_cLocation.Y == g_snake.m_cLocation.Y)))
				{
					spawnonsnake = true;
				}

				else
				{
					spawnonsnake = false;
				}


			}
		} while (((PrevLoc.X == g_apple.m_cLocation.X) && (PrevLoc.Y == g_apple.m_cLocation.Y)) && (spawnonsnake = true));// if the new location is same as old location, call the function again


		PrevLoc.X = g_apple.m_cLocation.X;
		PrevLoc.Y = g_apple.m_cLocation.Y;//updates the last position of the apple 



		spawnapple = false;
		score++;
		SnakeBody.push_back(createSnakeBody(X, Y));

	}
}

void SnakerenderCharacter()
{

	// Draw the location of the character
	WORD charColor = 0x0C;
	if (g_snake.m_bActive)
	{
		charColor = 0x0A;
	}
	g_Console.writeToBuffer(g_snake.m_cLocation, char(1), charColor);



	charColor = 0x0A;

	g_Console.writeToBuffer(g_snake.m_cLocation, char(1), charColor);


	for (j = 0; j < SnakeBody.size(); j++)
	{
		if (SnakeBody[j].m_bActive)
		{
			charColor = 0x0A;
			g_Console.writeToBuffer(SnakeBody[j].m_cLocation, char(1), charColor);
		}
	}

	//eat itself
	for (j = 0; j < SnakeBody.size(); j++)
	{
		if ((g_snake.m_cLocation.X == SnakeBody[j].m_cLocation.X) && (g_snake.m_cLocation.Y == SnakeBody[j].m_cLocation.Y))
		{
			g_eGameState = S_GAME;
			spawnapple = true;
			applelocation(spawnapple);
			g_snake.m_cLocation.X = g_Console.getConsoleSize().X / 2;
			g_snake.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
			g_snake.m_bActive = true;
			g_apple.m_cLocation.X;
			g_apple.m_cLocation.Y;
			g_apple.m_bActive = true;
			spawnapple = false;
			lastbutton = 0;
			SnakeBody.clear();
			score = 0;
			goup = false;
			goleft = false;
			goright = false;
			godown = false;
		}
	}

}

void applelocation(bool spawnapple)
{

	srand((unsigned int)time(NULL));

	unsigned int randomlocationX = rand() % 118 + 50;
	unsigned int randomlocationY = rand() % 37 + 3;
	COORD C = { (SHORT)randomlocationX, (SHORT)randomlocationY };


	if (spawnapple == true)//changes location of apple
	{
		g_apple.m_cLocation.X = C.X;
		g_apple.m_cLocation.Y = C.Y;
	}
}

void movebodypart() //makes the body parts follow the head
{
	if (SnakeBody.size() != 0)
	{
		for (i = (SnakeBody.size() - 1); i >= 0; i--)
		{
			if (i == 0)
			{
				SnakeBody[0].m_cLocation.X = g_snake.m_cLocation.X;
				SnakeBody[0].m_cLocation.Y = g_snake.m_cLocation.Y;
				break;
			}
			else
			{
				SnakeBody[i].m_cLocation.X = SnakeBody[i - 1].m_cLocation.X;
				SnakeBody[i].m_cLocation.Y = SnakeBody[i - 1].m_cLocation.Y;
			}
		}
	}
}

void Snakecollisiondetection()
{
	if (((g_snake.m_cLocation.Y == 2)

		|| (g_snake.m_cLocation.X == 49)

		|| (g_snake.m_cLocation.Y == 40)

		|| (g_snake.m_cLocation.X == 168))


		|| (score == Snakewincondition)// win condition
		)
	{
		g_eGameState = S_GAME;
		PlaySound(TEXT("Sounds/bgm.wav"), NULL, SND_SYNC | SND_ASYNC);
		if (score == Snakewincondition)
			g_abFlags[snakeDone] = true;

		spawnapple = true;
		applelocation(spawnapple);
		g_snake.m_cLocation.X = g_Console.getConsoleSize().X / 2;
		g_snake.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
		g_snake.m_bActive = true;
		g_apple.m_cLocation.X;
		g_apple.m_cLocation.Y;
		g_apple.m_bActive = true;
		spawnapple = false;
		lastbutton = 0;
		SnakeBody.clear();
		score = 0;
		goup = false;
		goleft = false;
		goright = false;
		godown = false;
	}

}

void SnakemoveCharacter()
{

	COORD C;
	C = { g_snake.m_cLocation.X ,g_snake.m_cLocation.Y };//coord c here is player location 
	bool bSomethingHappened = false;


	if (g_dBounceTimeMove[0] > g_dElapsedTime || !g_snake.m_bActive)
		return;
	movebodypart();
	if (g_abKeyPressed[K_UP] && (lastbutton != 4))
	{
		goup = true;
		goleft = false;
		goright = false;
		godown = false;
		lastbutton = 1;
	}

	if (g_abKeyPressed[K_LEFT] && (lastbutton != 3))
	{
		goup = false;
		goleft = true;
		goright = false;
		godown = false;
		lastbutton = 2;
	}

	if (g_abKeyPressed[K_RIGHT] && (lastbutton != 2))
	{
		goup = false;
		goleft = false;
		goright = true;
		godown = false;
		lastbutton = 3;
	}

	if (g_abKeyPressed[K_DOWN] && (lastbutton != 1))
	{
		goup = false;
		goleft = false;
		goright = false;
		godown = true;
		lastbutton = 4;
	}




	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (goup == true && g_snake.m_cLocation.Y > 2)
	{
		//Beep(1440, 30);
		bSomethingHappened = true;
		g_snake.m_cLocation.Y--;
	}



	if (goleft == true && g_snake.m_cLocation.X > 49)
	{
		//Beep(1440, 30);

		bSomethingHappened = true;
		g_snake.m_cLocation.X--;

	}

	if (godown == true && g_snake.m_cLocation.Y < 40)
	{
		//Beep(1440, 30);
		bSomethingHappened = true;
		g_snake.m_cLocation.Y++;

	}


	if (goright == true && g_snake.m_cLocation.X < 168)
	{
		//Beep(1440, 30);

		bSomethingHappened = true;
		g_snake.m_cLocation.X++;
	}


	if (g_abKeyPressed[K_SPACE])
	{
		g_snake.m_bActive = !g_snake.m_bActive;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers

		g_dBounceTimeMove[0] = g_dElapsedTime + 0.1;
	}
}



/***************************************PACMAN*****************************************/

void pacmanMode()
{
	moveCharacter();    // moves the character, collision detection, physics, etc
	checkForTiles();
	monsterLogic();

	// for collecting coins
	if (g_map.findCharExists(g_sChar1.m_cLocation, 'A'))
	{
		g_map.removeChar(g_sChar1.m_cLocation);
		PlaySound(TEXT("Sounds/coin.wav"), NULL, SND_SYNC | SND_ASYNC);
		countCoin--;
	}
	if (g_map.findCharExists(g_sChar2.m_cLocation, 'A'))
	{
		g_map.removeChar(g_sChar2.m_cLocation);
		PlaySound(TEXT("Sounds/coin.wav"), NULL, SND_SYNC | SND_ASYNC);
		countCoin--;
	}
	if (countCoin == 0) // when no more coin, switch gamestate
	{
		LOAD(temporary1);
		LOADMAP(temporarymap1);

		g_eGameState = S_GAME;
		g_trigger.initTrigger(&g_map, &g_Console);//reninit all triggers for new map		
		countCoin = 10;
		g_abFlags[pacmanDone] = true;

	}
	if (g_abKeyPressed[K_BACKSPACE])
	{
		LOAD(temporary1);
		LOADMAP(temporarymap1);
		g_eGameState = S_GAME;
		g_trigger.initTrigger(&g_map, &g_Console);//reninit all triggers for new map		
		countCoin = 10;
	}
}

void renderPacmanMode()
{
	renderMap();
	renderCharacter();
	renderMonster();
	g_Console.writeToBuffer({ 91,14 }, "Collect:", 0x0C);
	g_Console.writeToBuffer({ 100, 14 }, std::to_string(countCoin), 0x0C);
	g_Console.writeToBuffer({ 103, 14 }, "more coins", 0x0C);
}

void monsterLogic() // represented by 'M'
{
	int RNG1 = rand() % 4;
	int RNG2 = rand() % 2;
	int RNG3 = rand() % 2;

	if (g_dBounceTimeMonster < g_dElapsedTime)
	{
		//movement for monster 1
		if (RNG1 == 0 && g_monster1.m_cLocation.Y > 1) //up
		{
			moveMonster1(0, -1);
			moveMonster5(0, -1);
		}

		else if (RNG1 == 1 && g_monster1.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)//down
		{
			moveMonster1(0, 1);
			moveMonster5(0, 1);
		}

		else if (RNG1 == 2 && g_monster1.m_cLocation.X > 0)//left
		{
			moveMonster1(-1, 0);
			moveMonster5(-1, 0);
		}

		else if (RNG1 == 3 && g_monster1.m_cLocation.X < g_Console.getConsoleSize().X - 1)//right
		{
			moveMonster1(1, 0);
			moveMonster5(1, 0);
		}

		//movement for monster 2 
		if (RNG2 == 0)//left
		{
			moveMonster2(-1, 0);
		}

		else if (RNG2 == 1)//right
		{
			moveMonster2(1, 0);
		}

		//movement for monster 3
		if (RNG3 == 0 && g_monster3.m_cLocation.Y > 1) //up
		{
			moveMonster3(0, -1);
		}

		else if (RNG3 == 1 && g_monster3.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)//down
		{
			moveMonster3(0, 1);
		}

		//movement for monster 4
		if (RNG3 == 0 && g_monster3.m_cLocation.Y > 1) //up
		{
			moveMonster4(0, -1);
		}

		else if (RNG3 == 1 && g_monster3.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)//down
		{
			moveMonster4(0, 1);
		}

		// when player 1 or 2 touches monster, switch gamestate
		if (EQUCOORDS(g_sChar1.m_cLocation, g_monster1.m_cLocation) ||
			EQUCOORDS(g_sChar2.m_cLocation, g_monster1.m_cLocation) ||
			EQUCOORDS(g_sChar1.m_cLocation, g_monster2.m_cLocation) ||
			EQUCOORDS(g_sChar2.m_cLocation, g_monster2.m_cLocation) ||
			EQUCOORDS(g_sChar1.m_cLocation, g_monster3.m_cLocation) ||
			EQUCOORDS(g_sChar2.m_cLocation, g_monster3.m_cLocation) ||
			EQUCOORDS(g_sChar1.m_cLocation, g_monster4.m_cLocation) ||
			EQUCOORDS(g_sChar2.m_cLocation, g_monster4.m_cLocation) ||
			EQUCOORDS(g_sChar1.m_cLocation, g_monster5.m_cLocation) ||
			EQUCOORDS(g_sChar2.m_cLocation, g_monster5.m_cLocation))
		{
			LOAD(temporary1);
			LOADMAP(temporarymap1);
			g_eGameState = S_GAME;
			g_trigger.initTrigger(&g_map, &g_Console);//reninit all triggers for new map

			PlaySound(TEXT("Sounds/bgm.wav"), NULL, SND_SYNC | SND_ASYNC);


			// initialise the position of monsters, after pacman ends
			g_monster1.m_cLocation.X = 98;
			g_monster1.m_cLocation.Y = 28;

			g_monster2.m_cLocation.X = 98;
			g_monster2.m_cLocation.Y = 35;

			g_monster3.m_cLocation.X = 82;
			g_monster3.m_cLocation.Y = 33;

			g_monster4.m_cLocation.X = 115;
			g_monster4.m_cLocation.Y = 33;

			g_monster5.m_cLocation.X = 76;
			g_monster5.m_cLocation.Y = 43;
		}
	}
}

void renderMonster()
{
	g_Console.writeToBuffer(g_monster1.m_cLocation, (char)164, 0x03);
	g_Console.writeToBuffer(g_monster2.m_cLocation, (char)164, 0x03);
	g_Console.writeToBuffer(g_monster3.m_cLocation, (char)164, 0x03);
	g_Console.writeToBuffer(g_monster4.m_cLocation, (char)164, 0x03);
	g_Console.writeToBuffer(g_monster5.m_cLocation, (char)164, 0x03);
}

void moveMonster1(int dirx, int diry)
{
	//check for monster 1
	g_monster1.m_futureLocation.X = g_monster1.m_cLocation.X + dirx;
	g_monster1.m_futureLocation.Y = g_monster1.m_cLocation.Y + diry;


	if (!g_map.collideWithWall(g_monster1.m_futureLocation))
	{
		g_dBounceTimeMonster = g_dElapsedTime + 0.1;
		g_monster1.m_cLocation.X = g_monster1.m_cLocation.X + dirx;
		g_monster1.m_cLocation.Y = g_monster1.m_cLocation.Y + diry;
	}
}

void moveMonster2(int dirx, int diry)
{
	//check for monster 2
	g_monster2.m_futureLocation.X = g_monster2.m_cLocation.X + dirx;
	g_monster2.m_futureLocation.Y = g_monster2.m_cLocation.Y + diry;

	if (!g_map.collideWithWall(g_monster2.m_futureLocation))
	{
		g_dBounceTimeMonster = g_dElapsedTime + 0.1;
		g_monster2.m_cLocation.X = g_monster2.m_cLocation.X + dirx;
		g_monster2.m_cLocation.Y = g_monster2.m_cLocation.Y + diry;
	}
}

void moveMonster3(int dirx, int diry)
{
	//check for monster 2
	g_monster3.m_futureLocation.X = g_monster3.m_cLocation.X + dirx;
	g_monster3.m_futureLocation.Y = g_monster3.m_cLocation.Y + diry;

	if (!g_map.collideWithWall(g_monster3.m_futureLocation))
	{
		g_dBounceTimeMonster = g_dElapsedTime + 0.1;
		g_monster3.m_cLocation.X = g_monster3.m_cLocation.X + dirx;
		g_monster3.m_cLocation.Y = g_monster3.m_cLocation.Y + diry;
	}
}

void moveMonster4(int dirx, int diry)
{
	//check for monster 2
	g_monster4.m_futureLocation.X = g_monster4.m_cLocation.X + dirx;
	g_monster4.m_futureLocation.Y = g_monster4.m_cLocation.Y + diry;

	if (!g_map.collideWithWall(g_monster4.m_futureLocation))
	{
		g_dBounceTimeMonster = g_dElapsedTime + 0.1;
		g_monster4.m_cLocation.X = g_monster4.m_cLocation.X + dirx;
		g_monster4.m_cLocation.Y = g_monster4.m_cLocation.Y + diry;
	}
}

void moveMonster5(int dirx, int diry)
{
	//check for monster 2
	g_monster5.m_futureLocation.X = g_monster5.m_cLocation.X + dirx;
	g_monster5.m_futureLocation.Y = g_monster5.m_cLocation.Y + diry;

	if (!g_map.collideWithWall(g_monster5.m_futureLocation))
	{
		g_dBounceTimeMonster = g_dElapsedTime + 0.1;
		g_monster5.m_cLocation.X = g_monster5.m_cLocation.X + dirx;
		g_monster5.m_cLocation.Y = g_monster5.m_cLocation.Y + diry;
	}
}







/******************************************UI******************************************/


void mainMenu()
{
	//handling input
	bool bSomethingHappened = false;
	if (g_dBounceTimeUI > g_dElapsedTime)
		return;
	if (g_abKeyPressed[K_ENTER])
	{
		switch (g_menuSelection)
		{
		case 0:
			g_eGameState = S_GAME;
			break;
		case 1:
			g_eGameState = S_LOADSAVE;
			g_menuSelection = 0;
			break;
		case 2:
			g_bQuitGame = true;
			break;
		}
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_UP] || g_abKeyPressed[K_W])
	{
		g_menuSelection--;
		if (g_menuSelection == -1)
			g_menuSelection = 2;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_S])
	{
		g_menuSelection++;
		g_menuSelection %= 3;
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTimeUI = g_dElapsedTime + 0.2;
	}
}

void renderMainMenu()
{
	backgroundimage();
	WORD attri1 = 0x07, attri2 = 0x07, attri3 = 0x07;

	switch (g_menuSelection)
	{
	case 0:
		attri1 = 0x03;
		break;
	case 1:
		attri2 = 0x03;
		break;
	case 2:
		attri3 = 0x03;
		break;
	}

	COORD c = g_Console.getConsoleSize();
	c.Y = 33;
	c.X = (SHORT)(c.X * 0.5 + 3);
	g_Console.writeToBuffer(c, "PLAY", attri1);
	c.Y += 1;
	c.X = (SHORT)(g_Console.getConsoleSize().X * 0.5 + 3);
	g_Console.writeToBuffer(c, "LOAD", attri2);
	c.Y += 1;
	c.X = (SHORT)(g_Console.getConsoleSize().X * 0.5 + 3);
	g_Console.writeToBuffer(c, "EXIT", attri3);
}

void loadSave()
{
	//handling input
	bool bSomethingHappened = false;
	if (g_dBounceTimeUI > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER])
	{
		switch (g_menuSelection)
		{
		case 0:
			g_eGameState = S_GAME;
			LOAD(filename1);
			LOADMAP(mapname1);

			//load saved file 1
			break;
		case 1:
			g_eGameState = S_GAME;
			LOAD(filename2);
			LOADMAP(mapname2);
			//load saved file 2
			break;
		case 2:
			g_eGameState = S_GAME;
			LOAD(filename3);
			LOADMAP(mapname3);
			//load saved file 3
			break;
		case 3:
			g_eGameState = S_MENU;
			g_menuSelection = 1;
			break;
		}
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_UP] || g_abKeyPressed[K_W])
	{
		g_menuSelection--;
		if (g_menuSelection == -1)
			g_menuSelection = 3;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_S])
	{
		g_menuSelection++;
		g_menuSelection %= 4;
		bSomethingHappened = true;
	}


	if (g_abKeyPressed[K_BACKSPACE] || g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_MENU;
		g_menuSelection = 0;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTimeUI = g_dElapsedTime + 0.2;
	}
}

void renderLoadSave()
{
	backgroundimage();
	WORD attri1 = 0x07, attri2 = 0x07, attri3 = 0x07, attri4 = 0x07;

	switch (g_menuSelection)
	{
	case 0:
		attri1 = 0x03;
		break;
	case 1:
		attri2 = 0x03;
		break;
	case 2:
		attri3 = 0x03;
		break;
	case 3:
		attri4 = 0x03;
		break;
	}

	COORD c = g_Console.getConsoleSize();
	c.Y = 33;
	c.X = (SHORT)(g_Console.getConsoleSize().X * 0.5 + 2);

	g_Console.writeToBuffer(c, "SAVE 1", attri1);
	c.Y += 1;
	c.X = (SHORT)(g_Console.getConsoleSize().X * 0.5 + 2);
	g_Console.writeToBuffer(c, "SAVE 2", attri2);
	c.Y += 1;
	c.X = (SHORT)(g_Console.getConsoleSize().X * 0.5 + 2);
	g_Console.writeToBuffer(c, "SAVE 3", attri3);
	c.Y += 1;
	c.X = (SHORT)(g_Console.getConsoleSize().X * 0.5 + 3);
	g_Console.writeToBuffer(c, "BACK", attri4);
}

void quizMode()
{
	bool bSomethingHappened = false;
	if (g_dBounceTimeUI > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_A])
	{
		g_quiz.attempt += 'A';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_B])
	{
		g_quiz.attempt += 'B';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_C])
	{
		g_quiz.attempt += 'C';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_D])
	{
		g_quiz.attempt += 'D';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_E])
	{
		g_quiz.attempt += 'E';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_F])
	{
		g_quiz.attempt += 'F';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_G])
	{
		g_quiz.attempt += 'G';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_H])
	{
		g_quiz.attempt += 'H';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_I])
	{
		g_quiz.attempt += 'I';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_J])
	{
		g_quiz.attempt += 'J';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_K])
	{
		g_quiz.attempt += 'K';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_L])
	{
		g_quiz.attempt += 'L';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_M])
	{
		g_quiz.attempt += 'M';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_N])
	{
		g_quiz.attempt += 'N';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_O])
	{
		g_quiz.attempt += 'O';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_P])
	{
		g_quiz.attempt += 'P';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_Q])
	{
		g_quiz.attempt += 'Q';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_R])
	{
		g_quiz.attempt += 'R';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_S])
	{
		g_quiz.attempt += 'S';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_T])
	{
		g_quiz.attempt += 'T';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_U])
	{
		g_quiz.attempt += 'U';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_V])
	{
		g_quiz.attempt += 'V';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_W])
	{
		g_quiz.attempt += 'W';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_X])
	{
		g_quiz.attempt += 'X';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_Y])
	{
		g_quiz.attempt += 'Y';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_Z])
	{
		g_quiz.attempt += 'Z';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_0])
	{
		g_quiz.attempt += '0';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_1])
	{
		g_quiz.attempt += '1';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_2])
	{
		g_quiz.attempt += '2';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_3])
	{
		g_quiz.attempt += '3';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_4])
	{
		g_quiz.attempt += '4';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_5])
	{
		g_quiz.attempt += '5';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_6])
	{
		g_quiz.attempt += '6';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_7])
	{
		g_quiz.attempt += '7';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_8])
	{
		g_quiz.attempt += '8';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_9])
	{
		g_quiz.attempt += '9';
		bSomethingHappened = true;
	}


	if (g_abKeyPressed[K_SPACE])
	{
		g_quiz.attempt += ' ';
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_BACKSPACE])
	{
		g_quiz.attempt = g_quiz.attempt.substr(0, g_quiz.attempt.length() - 1); //removes a char
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_ENTER])
	{
		if (g_abFlags[quizzing])
		{
			g_abFlags[quizzing] = false;
			if (!g_quiz.checkAns() && g_eGameState == S_QUIZ_E)
			{
				g_sChar1.updateHealth(1, rand() % 5 + 1);
				g_sChar2.updateHealth(2, rand() % 5 + 1);
			}
			else if (g_quiz.checkAns() && g_eGameState == S_QUIZ_B)
			{
				g_boss->updateLives(1);
			}
			//TEMPOP, temporary, replace with loading last saved state function
			if (g_eGameState == S_QUIZ_E)
			{
				g_eGameState = S_GAME;
			}
			else if (g_eGameState == S_QUIZ_B)
			{
				g_boss->bossElapsedTime = g_dElapsedTime;
				g_boss->setNumOfAttacks(3);
				g_eGameState = S_BOSS;
			}
		}
		else g_abFlags[quizzing] = true;
		bSomethingHappened = true;
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTimeUI = g_dElapsedTime + 0.2;
	}
}

void renderQuiz()
{
	g_Console.writeToBuffer({ 10, 25 }, g_quiz.currQn, 0x0F);
	g_Console.writeToBuffer({ 10, 27 }, g_quiz.attempt + "_", 0x0F);
	string result = "", answers = "";
	if (g_abFlags[quizzing])
	{
		g_quiz.checkAns() ?
			g_quiz.quizResult(WIN, &result, &answers) :

			g_quiz.quizResult(LOSE, &result, &answers);
	}

	else
		result = "";
	g_Console.writeToBuffer({ 10, 28 }, result, 0x0F);
	g_Console.writeToBuffer({ 10, 29 }, answers, 0x0F);
}

void renderItems()
{
	g_Console.writeToBuffer({ 185, 5 }, "PISTOL", 0x0E);

	if (g_abFlags[hasPickaxe])
	{
		g_Console.writeToBuffer({ 164, 5 }, "PICKAXE", 0x0E);
	}

	if (g_abFlags[hasKey])
	{
		g_Console.writeToBuffer({ 145, 5 }, "KEY", 0x0E);
	}
}

void SAVE(string filename)
{
	std::ofstream savefile(filename);

	if (savefile.is_open())
	{

		if (g_sChar1.m_bActive == true)
		{
			savefile << '1' << std::endl;//player1 is active
		}
		else
		{
			savefile << '0' << std::endl;
		}

		savefile << g_sChar1.m_cLocation.X << std::endl;

		savefile << g_sChar1.m_cLocation.Y << std::endl;



		if (g_sChar2.m_bActive == true)
		{

			savefile << "1" << std::endl;//player2 is active
		}
		else
		{
			savefile << '0' << std::endl;
		}
		savefile << g_sChar2.m_cLocation.X << std::endl;

		savefile << g_sChar2.m_cLocation.Y << std::endl;



		for (int i = 0; i < flagCount; i++)
		{
			savefile << g_abFlags[i] ? '1' : '0';// if flag equals true save '1' else '0'
		}
		savefile << std::endl;

		//savefile << "END" << std::endl;
		savefile.close();
	}

	else
	{
		std::cerr << "UNABLE TO OPEN FILE" << std::endl;
	}

}

void LOAD(string filename)
{

	string load;
	std::ifstream savefile(filename);

	getline(savefile, load);
	g_sChar1.m_bActive = load == "1" ? true : false;

	if (g_sChar1.m_bActive)
	{
		getline(savefile, load);
		g_sChar1.m_cLocation.X = stoi(load);
		getline(savefile, load);
		g_sChar1.m_cLocation.Y = stoi(load);
	}

	else
	{
		getline(savefile, load);
		getline(savefile, load);
	}

	getline(savefile, load);
	g_sChar2.m_bActive = load == "1" ? true : false;
	if (g_sChar2.m_bActive)
	{
		getline(savefile, load);
		g_sChar2.m_cLocation.X = stoi(load);
		getline(savefile, load);
		g_sChar2.m_cLocation.Y = stoi(load);
	}

	else
	{
		getline(savefile, load);
		getline(savefile, load);
	}

	getline(savefile, load);
	//flags
	for (i = 0; i < flagCount; i++)
	{
		switch ((load[i]))
		{

		case 48:g_abFlags[i] = 0;
			break;
		case 49:g_abFlags[i] = 1;
			break;
		}
	}
}

void SAVEMAP(string mapname)
{
	string line;
	std::ofstream savefile(mapname);



	for (auto i : g_map.mapArray)
	{
		line += i;

	}
	savefile << line;
}

void LOADMAP(string mapname)
{

	string line;
	std::ifstream savefile(mapname);

	g_map.mapArray.clear();
	while (getline(savefile, line))
	{
		for (i = 0; i < line.length(); i++)
		{
			g_map.mapArray.push_back(line[i]); //adding to array
		}
	}

	vector<COORD> c;
	g_map.findChars('E', &c);
	if (!c.empty())
	{
		for (auto i : c)
		{
			g_map.removeChar(i);
		}
	}


}



void SAVEUI()
{
	processUserInput();

	bool bSomethingHappened = false;
	if (g_dBounceTimeUI > g_dElapsedTime)
		return;
	if (g_abKeyPressed[K_ENTER])
	{
		switch (g_menuSelection)
		{
		case 0:
			//savefile1

			SAVE(filename1);
			SAVEMAP(mapname1);

			break;
		case 1:
			//savefile2

			SAVE(filename2);
			SAVEMAP(mapname2);

			break;
		case 2:
			//savefile3

			SAVE(filename3);
			SAVEMAP(mapname3);

			break;
		case 3:
			g_menuSelection = 0;
			g_eGameState = S_GAME;
			break;

		case 4:
			g_menuSelection = 0;
			g_eGameState = S_MENU;
			break;
		}
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_UP] || g_abKeyPressed[K_W])
	{
		g_menuSelection--;
		if (g_menuSelection == -1)
			g_menuSelection = 4;
		bSomethingHappened = true;
	}
	else if (g_abKeyPressed[K_DOWN] || g_abKeyPressed[K_S])
	{
		g_menuSelection++;
		g_menuSelection %= 5;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTimeUI = g_dElapsedTime + 0.2;
	}
}

void RenderSAVEUI()
{
	WORD attri1 = 0x07, attri2 = 0x07, attri3 = 0x07, attri4 = 0x07, attri5 = 0x07;

	switch (g_menuSelection)
	{
	case 0:
		attri1 = 0x03;
		break;
	case 1:
		attri2 = 0x03;
		break;
	case 2:
		attri3 = 0x03;
		break;
	case 3:
		attri4 = 0x03;
		break;
	case 4:
		attri5 = 0x03;
		break;
	}


	COORD c = g_Console.getConsoleSize();
	c.Y = (SHORT)(g_Console.getConsoleSize().Y * 0.5);
	c.X = (SHORT)(g_Console.getConsoleSize().X * 0.5 + 2);
	g_Console.writeToBuffer(c, "SAVE 1", attri1);
	c.Y += 1;
	g_Console.writeToBuffer(c, "SAVE 2", attri2);
	c.Y += 1;
	g_Console.writeToBuffer(c, "SAVE 3", attri3);
	c.Y += 1;
	c.X++;
	g_Console.writeToBuffer(c, "BACK", attri4);
	c.Y++;
	g_Console.writeToBuffer(c, "EXIT", attri5);
}

void backgroundimage()
{
	COORD c = { 0,1 };
	std::string line;
	std::ifstream menubg("menuscreen.txt");
	unsigned int rows = 50;
	unsigned int cols = 200;
	char box = (char)219;

	for (i = 0;i < rows;i++)
	{

		getline(menubg, line);
		for (j = 0;j < line.length();j++)
		{
			if (line[j] == 'Z')
			{
				line[j] = box;
			}
		}
		g_Console.writeToBuffer(c, line, 0x0C);
		c.Y++;
	}
	menubg.close();
}




















/***************************************PONG GAME***************************************/

void pongMode()
{
	processUserInput();
	puckMove();
	moveSliders();
	if ((g_sPuck1.m_futureLocation.X == 135 || g_sPuck1.m_futureLocation.X == 34 || g_sPuck2.m_futureLocation.X == 135 || g_sPuck2.m_futureLocation.X == 34) || pongScore == pongWinCondition)
	{
		LOAD(temporary1);
		LOADMAP(temporarymap1);
		g_eGameState = S_GAME;

		g_trigger.initTrigger(&g_map, &g_Console);
		g_sPuck1.m_cLocation = { 84, 22 };
		g_sPuck2.m_cLocation = { 50, 22 };
		g_sPuck1.direction = { 1, 1 };
		g_sPuck2.direction = { -1, 1 };
		g_sSlider1.m_cLocation = { 35, 20 };
		g_sSlider2.m_cLocation = { 133, 20 };

		if (pongScore == pongWinCondition)
			g_abFlags[pongDone] = true;
		pongScore = 0;
	}

}

void renderPong()
{
	renderMap();
	renderSliders();
	g_Console.writeToBuffer(g_sPuck1.m_cLocation, g_sPuck1.symbol, g_sPuck1.color); // rendering the pucks
	g_Console.writeToBuffer(g_sPuck2.m_cLocation, g_sPuck2.symbol, g_sPuck2.color);
	g_Console.writeToBuffer({ g_Console.getConsoleSize().X / 2,43 }, playerscore + std::to_string(pongScore) + '/' + std::to_string(pongWinCondition), 0x0C);

}

void puckMove()
{
	bool bEventHappen = false;
	if (g_dBounceTimePuck > g_dElapsedTime)
		return;
	int puckSpeed = 1; // speed of the puck
	puckCollisionCheck();
	bEventHappen = true;
	g_sPuck1.m_cLocation.X += (puckSpeed * g_sPuck1.direction.X);
	g_sPuck1.m_cLocation.Y += (puckSpeed * g_sPuck1.direction.Y);
	g_sPuck2.m_cLocation.X += (puckSpeed * g_sPuck2.direction.X);
	g_sPuck2.m_cLocation.Y += (puckSpeed * g_sPuck2.direction.Y);
	if (bEventHappen = true)
	{
		g_dBounceTimePuck = g_dElapsedTime + 0.04;
	}
}

void renderSliders()
{
	COORD extend1 = g_sSlider1.m_cLocation;
	COORD extend2 = g_sSlider2.m_cLocation;
	for (int i = 0; i < 5; i++)
	{
		extend1.Y += 1;
		extend2.Y += 1;
		g_Console.writeToBuffer(extend1, (char)219, g_sSlider1.color);
		g_Console.writeToBuffer(extend2, (char)219, g_sSlider2.color);
	}
}

void puckCollisionCheck()
{
	int puckSpeed = 1;
	g_sPuck1.m_futureLocation = ADDCOORDS(g_sPuck1.m_cLocation, g_sPuck1.direction);
	g_sPuck2.m_futureLocation = ADDCOORDS(g_sPuck2.m_cLocation, g_sPuck2.direction);
	if (g_sPuck1.collisionCheckSlider(g_sPuck1.m_futureLocation, g_sSlider1.m_cLocation)) // to check if the puck collides with the player's slider
	{
		g_sPuck1.direction.X *= (-1);
	}
	if (g_sPuck1.collisionCheckSlider(g_sPuck1.m_futureLocation, g_sSlider2.m_cLocation))
	{
		g_sPuck1.direction.X *= (-1);
	}
	if (g_map.collideWithWall(g_sPuck1.m_futureLocation))
	{
		g_sPuck1.direction.Y *= (-1);
	}
	if (g_map.findCharExists(g_sPuck1.m_futureLocation, '5'))
	{
		g_map.removeChar(g_sPuck1.m_futureLocation);
		pongScore += 1;
		g_sPuck1.direction.X *= (-1);
	}

	if (g_sPuck2.collisionCheckSlider(g_sPuck2.m_futureLocation, g_sSlider1.m_cLocation)) // to check if the puck collides with the player's slider
	{
		g_sPuck2.direction.X *= (-1);
	}
	if (g_sPuck2.collisionCheckSlider(g_sPuck2.m_futureLocation, g_sSlider2.m_cLocation))
	{
		g_sPuck2.direction.X *= (-1);
	}
	if (g_map.collideWithWall(g_sPuck2.m_futureLocation))
	{
		g_sPuck2.direction.Y *= (-1);
	}
	if (g_map.findCharExists(g_sPuck2.m_futureLocation, '5'))
	{
		g_map.removeChar(g_sPuck2.m_futureLocation);
		pongScore += 1;
		g_sPuck2.direction.X *= (-1);
	}

}

void moveSliders()
{
	g_abFlags[moving1] = false;
	g_abFlags[moving2] = false;
	if (g_dBounceTimeMove[0] < g_dElapsedTime && g_sSlider1.m_bActive)
	{
		//player 1
		if (g_abKeyPressed[K_W] && g_sSlider1.m_cLocation.Y > 1)
		{
			//Beep(1440, 30);
			g_sSlider1.direction = { 0,-1 };
			g_abFlags[moving1] = true;
		}
		else if (g_abKeyPressed[K_S] && g_sSlider1.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
		{
			//Beep(1440, 30);
			g_sSlider1.direction = { 0, 1 };
			g_abFlags[moving1] = true;
		}
	}
	if (g_dBounceTimeMove[0] < g_dElapsedTime && g_sSlider1.m_bActive)
	{
		//player 2
		if (g_abKeyPressed[K_UP] && g_sSlider2.m_cLocation.Y > 1)
		{
			//Beep(1440, 30);
			g_sSlider2.direction = { 0,-1 };
			g_abFlags[moving2] = true;
		}
		else if (g_abKeyPressed[K_DOWN] && g_sSlider2.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
		{
			//Beep(1440, 30);
			g_sSlider2.direction = { 0, 1 };
			g_abFlags[moving2] = true;
		}
	}

	if (g_abFlags[moving1])
	{
		//calculating future location
		g_sSlider1.m_futureLocation = ADDCOORDS(g_sSlider1.m_cLocation, g_sSlider1.direction);
		g_sSlider1.m_futureLocation.Y += 1;
		if (!g_map.collideWithWall(g_sSlider1.m_futureLocation))
		{
			g_sSlider1.m_futureLocation.Y += 5;
			if (!g_map.collideWithWall(g_sSlider1.m_futureLocation))
				g_sSlider1.m_cLocation = ADDCOORDS(g_sSlider1.m_cLocation, g_sSlider1.direction);
		}
		//check bounce time
		g_dBounceTimeMove[0] = g_dElapsedTime + 0.03; // fazt
	}
	if (g_abFlags[moving2])
	{
		//calculating future location
		g_sSlider2.m_futureLocation = ADDCOORDS(g_sSlider2.m_cLocation, g_sSlider2.direction);
		if (!g_map.collideWithWall(g_sSlider2.m_futureLocation))
		{
			g_sSlider2.m_futureLocation.Y += 5;
			if (!g_map.collideWithWall(g_sSlider2.m_futureLocation))
				g_sSlider2.m_cLocation = ADDCOORDS(g_sSlider2.m_cLocation, g_sSlider2.direction);
		}
		//check bounce time
		g_dBounceTimeMove[0] = g_dElapsedTime + 0.03; // fazt
	}
}