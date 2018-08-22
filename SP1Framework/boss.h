#ifndef _BOSS_H
#define _BOSS_H
#include "Framework/console.h"
#include "map.h"
#include <vector>
#include <time.h>
using std::vector;

struct BulletAttack
{
public:
	char bullet = (char)233;
	vector<COORD> bulletPosts;
	vector<COORD> bulletDirs;
};

class Boss
{
public:
	Boss(Map* map, Console* console, COORD* playerPos1, COORD* playerPos2, double elapsedTime);

	COORD originalPlayerPos1, originalPlayerPos2;
	
	bool active = true; //alive or dead

	double bossElapsedTime = 0.0;
	
	double dBounceTime = 0.0;

	const double renderDelay = 1.0;

	const double attackDelay = 0.5;

	const double attackDura = 3.0;
	
	int attackIndex = 0;

	int numOfAttacks = 3;

	//init
	void bossInit(Map* map, Console* console, COORD* playerPos1, COORD* playerPos2, double elapsedTime);

	void initAttacks();
	
	void initBullets();
	
	void setNumOfAttacks(int index);
	
	//updates
	void attack();

	bool collision(COORD playerPos);

	void updateLives(int loss);
    
	//rendering
	void renderBossAttack(Console* console);
	
	void renderBulletAtk(Console* console);

	int getDmg(int modifier) { return this->dmg + modifier; };

	//types of attacks
	void changePlayerColor(int player, WORD* color);
	
	struct BulletAttack bulletAttack;

private:
	const int dmg = 5;
	int lives = 1;

	const int boxWidth = 80 - 2;
	const int boxHeight = 20 - 2;
	const COORD boxLeftTop = { 59, 29 };
};

#endif