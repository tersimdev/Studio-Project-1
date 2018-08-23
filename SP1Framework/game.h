#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Framework\console.h"
#include "organism.h"
#include "player.h"
#include "map.h"
#include "quiz.h"
#include "trigger.h"
#include "boss.h"
#include "cube.h"
#include "aStar.h"
#include "snakeMini.h"
#include <string>
#include <vector>
#include "Windows.h"//for music
#include "MMsystem.h"

using std::string;

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

const static int NumOfPlayers = 2;

//enum for flags
enum FLAGS
{
	moving1 = 0,
	moving2,
	shooting,
	hasPickaxe,
	quizzing,
	hasKey,
	tutoDone,
	snakeDone,
	bossDone,
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
	K_SPACE,
	K_B,
	K_C,
	K_E,
	K_F,
	K_G,
	K_H,
	K_I,
	K_J,
	K_K,
	K_L,
	K_M,
	K_N,
	K_O,
	K_P,
	K_Q,
	K_R,
	K_T,
	K_U,
	K_V,
	K_X,
	K_Y,
	K_Z,
	K_1,
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_7,
	K_8,
	K_9,
	K_0,
	K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
	S_MENU,
	S_LOADSAVE,
    S_GAME,
	S_BOSS,
	S_QUIZ_E,
	S_QUIZ_B,
	S_SNAKEMINIGAME,
	S_RUBIKS,
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

/*new*/
void mainMenu();			//captures events for navigating UI
void loadSave();			//captures events for navigating UI
void actionsListener();		//listens to actions
void checkForTiles();		//checks for special tiles which player can interact with
void enemyMovement();		//moves the enemy and collision detection
void bossMode();			//new map and collision tiles and enemies
void quizMode();			//captures keyboard input
void cubeControl();			//captures input to move cube
void renderHealth();		//renders the health of players
void renderBullet();		//renders bullets from players
void renderMainMenu();      //renders main menu
void renderLoadSave();		//renders load saves menu
void renderBossMode();		//renders the boss' attacks etc
void renderQuiz();			//renders the quiz to console
void renderItems();			//renders currently owned items
void renderCube();			//renders the cube;
void SAVE();
void LOAD();


#endif // _GAME_H