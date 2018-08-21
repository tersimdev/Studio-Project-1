#ifndef _BOSS_H
#define _BOSS_H
#include "Framework/console.h"
#include "map.h"
#include <vector>
using std::vector;

struct BulletAttack
{
public:
	BulletAttack();
	vector<COORD> bulletPosts;
	vector<COORD> bulletDirs;

private:
	int dmg = 10;
};

class Boss
{
public:
	Boss(Map* map, Console* console, COORD* playerPos1, COORD* playerPos2);

	COORD originalPlayerPos1, originalPlayerPos2;
	
	double bossElapsedTime = 0.0;
	double dBounceTime = 0.0;
	
	void bossInit(Map* map, Console* console, COORD* playerPos1, COORD* playerPos2);

	void renderBossAttack(int index, Console* console);

	void initBullets(vector<COORD> &postitions, vector<COORD> &directions);

	void renderBulletAtk(Console* console);

	struct BulletAttack bulletAttack;
};

#endif