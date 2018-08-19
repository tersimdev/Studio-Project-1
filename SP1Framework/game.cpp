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
// Game specific variables here
Map			g_map(0); //map
SGameChar	g_sChar1((char)3, 0x0C, &g_map, 1); //player1
SGameChar	g_sChar2((char)3, 0x0A, &g_map, 2); //player2
Trigger		g_trigger(&g_map);
Quiz		g_quiz(0); //quiz
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
// these are to prevent key bouncing, so we won't trigger keypresses more than once
double	g_dBounceTimeNorm;
double  g_dBounceTimeUI; 
double  g_dBounceTimeMove[NumOfPlayers];
double  g_dBounceTimeAction[NumOfPlayers];
// Console object
Console g_Console(199, 51, "RISE OF THE TOMB EXPLORING N00BS");

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
	

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

	// setting seed for srand
	srand(time(NULL));

	//prevent selection of text- disable quick edit mode
	g_Console.setConsoleMode(ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

	//init variables
	g_menuSelection = 0;
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
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
void getInput( void )
{    
	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: //none
		break;
	case S_MENU: //ui
	case S_LOADSAVE: //ui
	case S_GAME: //game
	case S_BOSS: //boss
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
		}
		break;
	case S_QUIZ:
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
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
		case S_MENU: mainMenu();
			break;
		case S_LOADSAVE: loadSave();
			break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
		case S_BOSS: bossMode();
			break;
		case S_QUIZ: quizMode();
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
	case S_QUIZ: renderQuiz();
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
						// sound can be played here too.
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
		if (!g_map.collideWithWall(g_sChar1.m_futureLocation) && (
			g_sChar1.m_futureLocation.X != g_sChar2.m_cLocation.X || g_sChar1.m_futureLocation.Y != g_sChar2.m_cLocation.Y))
				g_sChar1.m_cLocation = ADDCOORDS(g_sChar1.m_cLocation, g_sChar1.direction);
		//check bounce time
		g_dBounceTimeMove[0] = g_dElapsedTime + 0.05; // fazt
	}
	if (g_abFlags[moving2])
	{
		//calculating future location
		g_sChar2.m_futureLocation = ADDCOORDS(g_sChar2.m_cLocation, g_sChar2.direction);
		//check if colliding with collidables in map, or if moving towards player 2
		if (!g_map.collideWithWall(g_sChar2.m_futureLocation) && (
			g_sChar2.m_futureLocation.X != g_sChar1.m_cLocation.X || g_sChar2.m_futureLocation.Y != g_sChar1.m_cLocation.Y))
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
		}
	}
	if (g_dBounceTimeAction[1] < g_dElapsedTime)
	{
		if (g_abKeyPressed[K_SPACE])
		{
			g_abFlags[hasPickaxe] = !g_abFlags[hasPickaxe];
			g_sChar1.updateHealth(1, 10);
			g_sChar2.updateHealth(1, -1);
			//g_quiz.query();
			//g_eGameState = S_QUIZ;
			eventHappened[1] = true;
		}
	}
	if (eventHappened[0])
		g_dBounceTimeAction[0] = g_dElapsedTime + 0.8; // slow
	if (eventHappened[1])
		g_dBounceTimeAction[1] = g_dElapsedTime + 0.5; // slow
}

void processUserInput()
{
	bool eventHappened = false;
	if (g_dBounceTimeNorm > g_dElapsedTime)
		return;
		// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
		eventHappened = true;
	}

	if (eventHappened)
		g_dBounceTimeNorm = g_dElapsedTime + 0.125; // avg
}

void checkForTiles()
{
	if (g_abFlags[moving1] || g_abFlags[moving2])
	{
		SGameChar* player = &g_sChar1;
		if (g_abFlags[moving2])
			player = &g_sChar2;

		if (g_map.findCharExists(player->m_futureLocation, 'D'))
		{
			g_map.updateMap(); //loads next map, wraping around
			g_trigger.initTrigger(&g_map); //reinits all triggers for new map
			if (player->m_cLocation.X > g_Console.getConsoleSize().X * 0.9)
			{
				player->m_cLocation.X = 2;
			}
			else if (player->m_cLocation.X < g_Console.getConsoleSize().X * 0.1)
			{
				player->m_cLocation.X = g_Console.getConsoleSize().X - 3;
			}
			else if (player->m_cLocation.Y > g_Console.getConsoleSize().Y * 0.9)
			{
				player->m_cLocation.Y = 2;
			}
			else if (player->m_cLocation.Y < g_Console.getConsoleSize().Y * 0.1)
				player->m_cLocation.Y = g_Console.getConsoleSize().Y - 3;
		}
		
		if (g_map.findCharExists(player->m_futureLocation, 'U'))
		{
			//intialising position of player
			g_sChar1.m_cLocation.X = g_Console.getConsoleSize().X * 0.5 - 1;
			g_sChar1.m_cLocation.Y = g_Console.getConsoleSize().Y * 0.5 - 1;
			g_sChar2.m_cLocation.X = g_Console.getConsoleSize().X * 0.5 - 1;
			g_sChar2.m_cLocation.Y = g_Console.getConsoleSize().Y * 0.5 + 1;
			g_map.loadMap("Levels/BOSS1.txt");
			g_eGameState = S_BOSS;
		}
		if (g_map.findCharExists(g_sChar1.m_futureLocation, 'B'))
		{
			g_trigger.boulder = g_trigger.findBoulder(g_sChar1.m_futureLocation);
			g_trigger.boulder->moveBoulder(&g_map, &g_sChar1, &g_Console);
		}
		else if (g_map.findCharExists(g_sChar2.m_futureLocation, 'B'))
		{
			if (g_abFlags[hasPickaxe] && g_abKeyPressed[K_RCTRL])
			{
				g_trigger.boulder = g_trigger.findBoulder(g_sChar2.m_futureLocation);
				g_trigger.boulder->destroyBoulder(&g_map);
			}
		}
	}

	
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X * 0.5 - 7;
	g_Console.writeToBuffer(c, "Starting in 3s", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X * 0.5 - 21;
	g_Console.writeToBuffer(c, "Change console font-size to suit your needs", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X * 0.5 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer

	if (g_abFlags[shooting]) // renders bullet if shooting
		renderBullet();
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
	renderHealth();
}

void renderHealth()
{
	g_Console.writeToBuffer(g_sChar1.playerUIPos, g_sChar1.playerHPUI, g_sChar1.color);
	g_Console.writeToBuffer(g_sChar2.playerUIPos, g_sChar2.playerHPUI, g_sChar2.color);
}

void renderBullet()
{	
	g_sChar1.gun->shoot(&g_sChar1);
	//check if bullet exceeds console or hits wall or out of range
	if (g_sChar1.gun->outOfRange || g_sChar1.gun->bulletPos.X < 0 || g_sChar1.gun->bulletPos.Y < 1 ||
		g_sChar1.gun->bulletPos.X > g_Console.getConsoleSize().X - 1 || g_sChar1.gun->bulletPos.Y > g_Console.getConsoleSize().Y - 1 || 
		g_map.collideWithWall(g_sChar1.gun->bulletPos))
	{
		delete g_sChar1.gun; //no more visual bullet
		g_abFlags[shooting] = false; //stops rendering
	}
	else
		g_Console.writeToBuffer(g_sChar1.gun->bulletPos, (char)254, 0x0E);
}







/****************************************BOSS GAMEPLAY****************************************/


void bossMode()
{
	moveCharacter();    // moves the character, collision detection, physics, etc
}

void renderBossMode()
{
	renderMap();
	renderCharacter();
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
			g_menuSelection = 1;
			//currentgamestate = 2;
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

	if (g_abKeyPressed[K_1])
	{
		g_eGameState = S_GAME;
	}
	else if (g_abKeyPressed[K_2])
	{
		g_eGameState = S_LOADSAVE;
		g_menuSelection = 0;
	}
	else if (g_abKeyPressed[K_3])
	{
		g_bQuitGame = true;
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
	c.Y /= 3;
	c.X = c.X * 0.5 - 3;

	g_Console.writeToBuffer(c, "1. PLAY", attri1);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X * 0.5 - 3;
	g_Console.writeToBuffer(c, "2. LOAD", attri2);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X * 0.5 - 3;
	g_Console.writeToBuffer(c, "3. EXIT", attri3);
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
			//load saved file 1
			break;
		case 1:
			//load saved file 2
			break;
		case 2:
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

	if (g_abKeyPressed[K_1])
	{
		//load saved file 1
	}
	else if (g_abKeyPressed[K_2])
	{
		//load saved file 2
	}
	else if (g_abKeyPressed[K_3])
	{
		//load saved file 3
	}
	else if (g_abKeyPressed[K_4])
	{
		g_eGameState = S_MENU;
		g_menuSelection = 0;
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
	c.Y /= 3;
	c.X = c.X * 0.5 - 4;

	g_Console.writeToBuffer(c, "1. EMPTY", attri1);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X * 0.5 - 4;
	g_Console.writeToBuffer(c, "2. EMPTY", attri2);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X * 0.5 - 4;
	g_Console.writeToBuffer(c, "3. EMPTY", attri3);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X * 0.5 - 4;
	g_Console.writeToBuffer(c, "4. BACK", attri4);
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
			g_eGameState = S_GAME;
			g_abFlags[quizzing] = false;
		}
		else g_abFlags[quizzing] = true;
		g_quiz.checkAns();
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
		g_quiz.checkAns() ? 
			g_quiz.quizResult(WIN_ENEMY, &result, &answers) : 
			g_quiz.quizResult(LOSE_ENEMY, &result, &answers);
	else
		result = "";
	g_Console.writeToBuffer({ 10, 28 }, result, 0x0F);
	g_Console.writeToBuffer({ 10, 29 }, answers, 0x0F);
}