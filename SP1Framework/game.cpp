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
int selection = 1;
int currentgamestate = 1;
// Game specific variables here
Map			g_map(0); //map
SGameChar   g_sChar1((char)3, 30, 0x0C, {3, 3}); //player1
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(200, 60, "RISE OF THE TOMB MARAUDER");

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
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

	// setting seed for srand
	srand(time(NULL));

	//prevent selection of text- disable quick edit mode
	g_Console.setConsoleMode(ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);
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
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_RCTRL] = isKeyPressed(VK_RCONTROL);
	g_abKeyPressed[K_W]		 = isKeyPressed(0x57); 
	g_abKeyPressed[K_A]      = isKeyPressed(0x41); 
	g_abKeyPressed[K_S]      = isKeyPressed(0x53); 
	g_abKeyPressed[K_D]      = isKeyPressed(0x44);
	g_abKeyPressed[K_LSHIFT] = isKeyPressed(VK_LSHIFT); 
	g_abKeyPressed[K_RMB]    = isKeyPressed(VK_RBUTTON);
	g_abKeyPressed[K_LMB]    = isKeyPressed(VK_LBUTTON);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	g_abKeyPressed[K_BACKSPACE] = isKeyPressed(VK_BACK);
	g_abKeyPressed[K_1] = isKeyPressed(0x31);
	g_abKeyPressed[K_2] = isKeyPressed(0x32);
	g_abKeyPressed[K_3] = isKeyPressed(0x33);
	g_abKeyPressed[K_4] = isKeyPressed(0x34);

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
		case S_MENU: mainmenu();
			break;
		case S_LOADSAVE:loadsave();
			break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
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
		case S_MENU:mainmenu();
			break;

		case S_LOADSAVE:loadsave();
			break;
        case S_GAME: renderGame();
            break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 1.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_MENU;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
	                 // sound can be played here too.
}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_W] && g_sChar1.m_cLocation.Y > 0)
    {
        //Beep(1440, 30);
		g_sChar1.direction = { 0,-1 };
		g_sChar1.m_futureLocation.X = g_sChar1.m_cLocation.X + g_sChar1.direction.X;
		g_sChar1.m_futureLocation.Y = g_sChar1.m_cLocation.Y + g_sChar1.direction.Y;
		if (!g_map.collideWithWall(g_sChar1.m_futureLocation))
			g_sChar1.m_cLocation.Y--;
        g_abFlags[moving] = true;
    }
    if (g_abKeyPressed[K_A] && g_sChar1.m_cLocation.X > 0)
    {
        //Beep(1440, 30)
		g_sChar1.direction = { -1, 0 };
		g_sChar1.m_futureLocation.X = g_sChar1.m_cLocation.X + g_sChar1.direction.X;
		g_sChar1.m_futureLocation.Y = g_sChar1.m_cLocation.Y + g_sChar1.direction.Y;
		if (!g_map.collideWithWall(g_sChar1.m_futureLocation))
			g_sChar1.m_cLocation.X--;
		g_abFlags[moving] = true;
    }
    if (g_abKeyPressed[K_S] && g_sChar1.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
		g_sChar1.direction = { 0, 1 };
		g_sChar1.m_futureLocation.X = g_sChar1.m_cLocation.X + g_sChar1.direction.X;
		g_sChar1.m_futureLocation.Y = g_sChar1.m_cLocation.Y + g_sChar1.direction.Y;
		if (!g_map.collideWithWall(g_sChar1.m_futureLocation))
			g_sChar1.m_cLocation.Y++;
		g_abFlags[moving] = true;
    }
    if (g_abKeyPressed[K_D] && g_sChar1.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
		g_sChar1.direction = { 1, 0 };
		g_sChar1.m_futureLocation.X = g_sChar1.m_cLocation.X + g_sChar1.direction.X;
		g_sChar1.m_futureLocation.Y = g_sChar1.m_cLocation.Y + g_sChar1.direction.Y;
		if (!g_map.collideWithWall(g_sChar1.m_futureLocation))
			g_sChar1.m_cLocation.X++;
		g_abFlags[moving] = true;
    }

    if (g_abKeyPressed[K_LSHIFT] && (g_sChar1.gun == NULL || !g_abFlags[shooting]))
    {
		g_abFlags[shooting] = true;
		g_sChar1.gun = new Gun(g_sChar1.m_cLocation);
		g_abFlags[moving] = true;
    }
	if (g_abKeyPressed[K_RCTRL])
	{
			g_map.updateMap(1);
	}

	if (g_abFlags[moving])
	{
		if (g_sChar1.direction.X == -1 || g_sChar1.direction.X == 1)
			g_dBounceTime = g_dElapsedTime + 0.03; // fazt
		else if (g_sChar1.direction.Y == -1 || g_sChar1.direction.Y == 1)
			g_dBounceTime = g_dElapsedTime + 0.06; // not as fazt
	}
    else if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + g_sChar1.gun->getFirerate(); // 125ms should be enough
    }
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    

	if (g_abKeyPressed[K_BACKSPACE])
	{	
			g_eGameState = S_MENU;
			selection = 1;
	}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x00);
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X * 0.5 - 9;
	g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
	/*c.Y += 1;
	c.X = g_Console.getConsoleSize().X * 0.5 - 20;
	g_Console.writeToBuffer(c, "Font Size 16 Consolas for best experience", 0x09);
	*/
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X * 0.5 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer

	if (g_abFlags[shooting]) //renders bullet if shooting
		renderBullet();
}

void renderMap()
{
	COORD c = { 0, 1 }; 
	string line = "";
	for (int i = 0; i < g_map.rows; i++)
	{
		for (int j = 0; j < g_map.cols; j++)
		{
			line += g_map.mapArray[i * g_map.cols + j]; //add characters to line
		}
		g_Console.writeToBuffer(c, line, 0x0F); //write to buffer, one line
		c.Y++; //next line
		line = ""; //clear line for next line
	}
}

void renderCharacter()
{
	// Draw the location of the character
	g_Console.writeToBuffer(g_sChar1.m_cLocation, g_sChar1.symbol, g_sChar1.color);
}

void renderEnemy()
{
	COORD c;
	g_Console.writeToBuffer(c, (char)1, 0x0B);
}

void renderBullet()
{	
	if (g_sChar1.gun->direction.X == 0 && g_sChar1.gun->direction.Y == 0)
		g_sChar1.gun->direction = g_sChar1.direction;

	g_sChar1.gun->shoot(g_sChar1.m_cLocation, g_sChar1.gun->direction.X, g_sChar1.gun->direction.Y);

	if (g_map.collideWithWall(g_sChar1.gun->bulletPos) || g_sChar1.gun->outOfRange ||
		g_sChar1.gun->bulletPos.X < 0 || g_sChar1.gun->bulletPos.Y < 0 ||
		g_sChar1.gun->bulletPos.X > g_Console.getConsoleSize().X - 1 || g_sChar1.gun->bulletPos.Y > g_Console.getConsoleSize().Y - 1)
	{
		delete g_sChar1.gun;
		g_abFlags[shooting] = false;
	}
	else
		g_Console.writeToBuffer(g_sChar1.gun->bulletPos, (char)254, 0x0E);
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

void mainmenu()					
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;

	switch (selection)
	{
	case 1:
	{
		g_Console.writeToBuffer(c, "1. Play", 0x0A);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "2. Load", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "3. Exit", 0x17);
		c.Y += 3;
		c.X = g_Console.getConsoleSize().X / 2 - 16;
		g_Console.writeToBuffer(c, "Press 'Backspace' to back", 0x17);
		break;
	}

	case 2:
	{
		g_Console.writeToBuffer(c, "1. Play", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "2. Load", 0x0A);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "3. Exit", 0x17);
		c.Y += 3;
		c.X = g_Console.getConsoleSize().X / 2 - 16;
		g_Console.writeToBuffer(c, "Press 'Backspace' to back", 0x17);
		break;
	}

	case 3:
	{
		g_Console.writeToBuffer(c, "1. Play", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "2. Load", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "3. Exit", 0x0A);
		c.Y += 3;
		c.X = g_Console.getConsoleSize().X / 2 - 16;
		g_Console.writeToBuffer(c, "Press 'Backspace' to back", 0x17);
		break;
	}
	}

	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	




	if (g_abKeyPressed[K_ENTER])
	{
		if (selection == 1)
		{
			g_eGameState = S_GAME;
		}

		if (selection == 2)
		{
			g_eGameState = S_LOADSAVE;
			selection = 1;
			currentgamestate = 2;
		}

		if (selection == 3)
		{
			g_bQuitGame = true;
		}
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_UP])
	{
		selection--;
		if (selection == 0)
		{
			selection = 3;
		}
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_DOWN])
	{
		selection++;
		if (selection == 4)
		{
			selection = 1;
		}
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_1])
	{
		g_eGameState = S_GAME;
	}

	if (g_abKeyPressed[K_2])
	{
		g_eGameState = S_LOADSAVE;
		selection = 1;
	}

	if (g_abKeyPressed[K_3])
	{
		g_bQuitGame = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.2; // 125ms should be enough
	}
}




void loadsave()
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;



	switch (selection)
	{
	case 1:
	{
		g_Console.writeToBuffer(c, "1. Empty", 0x0A);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "2. Empty", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "3. Empty", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "4. Back", 0x17);
		break;
	}

	case 2:
	{
		g_Console.writeToBuffer(c, "1. Empty", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "2. Empty", 0x0A);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "3. Empty", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "4. Back", 0x17);
		break;
	}

	case 3:
	{
		g_Console.writeToBuffer(c, "1. Empty", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "2. Empty", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "3. Empty", 0x0A);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "4. Back", 0x17);
		break;
	}

	case 4:
	{
		g_Console.writeToBuffer(c, "1. Empty", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "2. Empty", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "3. Empty", 0x17);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 9;
		g_Console.writeToBuffer(c, "4. Back", 0x0A);
		break;
	}
	}

	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (g_abKeyPressed[K_ENTER])
	{
		if (g_dBounceTime > g_dElapsedTime)
			return;
		if (selection == 1)
		{
			//load saved file 1
		}

		if (selection == 2)
		{
			//load saved file 2
		}

		if (selection == 3)
		{
			//load saved file 3
		}

		if (selection == 4)
		{
			g_eGameState = S_MENU;
			selection = 1;
			currentgamestate = 1;            //game state goes back to main menu
		}
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_UP])
	{
		selection--;
		if (selection == 0)
		{
			selection = 4;
		}
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_DOWN])
	{
		selection++;
		if (selection == 5)
		{
			selection = 1;
		}
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_BACKSPACE])
	{
		g_eGameState = S_MENU;
	}

	if (g_abKeyPressed[K_1])
	{
		//load saved file 1
	}

	if (g_abKeyPressed[K_2])
	{
		//load saved file 2
	}

	if (g_abKeyPressed[K_3])
	{
		//load saved file 3
	}

	if (g_abKeyPressed[K_4])
	{
		g_eGameState = S_MENU;
		selection = 1;
	}

	if (g_abKeyPressed[K_BACKSPACE])
	{
		g_eGameState = S_MENU;
		selection = 1;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.2; // 125ms should be enough
	}
}