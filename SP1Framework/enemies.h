#ifndef _ENEMY_H
#define _ENEMY_H
#include "Framework\console.h"
#include "organism.h"
#include "map.h"
#include <random>
#include <time.h>

class Enemy : public Organism
{
public:
	Enemy(COORD loc, Map* map, Console* console);

	char prevChar = ' ';

	COORD dirToPLayer = { 0 , 0 };
	
	void locationGen(Map* map, Console* console);
	
	COORD directionGen(float seed);

	bool isAggro(COORD playerPos);

	void generalDir(COORD playerPos);

	void pathFind(COORD playerPos);

	void moveEnemy(Map* map, Console* console);

	void destroyEnemy(Map* map);
	
	bool enemyAttack(COORD playerPos);

private:
	COORD spawnNonce = { 20, 10 };

	int aggroRange = 50;
};

#endif