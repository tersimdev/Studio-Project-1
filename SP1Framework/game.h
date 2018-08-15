#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Framework\console.h"
#include "organism.h"
#include "player.h"
#include "map.h"
#include <string>
using std::string;

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

//enum for flags
enum FLAGS
{
	moving = 0,
	shooting,
	flagCount
};

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP = 0,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_LSHIFT,
	K_W,
	K_A,
	K_S,
	K_D,
	K_RCTRL,
	K_RMB,
	K_LMB,
	K_ESCAPE,
	K_ENTER,
	K_BACKSPACE,
	K_1,
	K_2,
	K_3,
	K_4,
	K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_LOADSAVE,
    S_SPLASHSCREEN,
	S_MENU,
    S_GAME,
    S_COUNT
};


void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

void renderEnemy();			// renders the enemy into buffer
void renderBullet();		//renders bullets from players
void mainmenu();			//main menu
void loadsave();			//place for players to load their save
#endif // _GAME_H