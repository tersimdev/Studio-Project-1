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

	bool enemyAttack = false;

	COORD m_cLocation;

	char prevChar = ' ';
	
	void locationGen(Map* map, Console* console);
	
	COORD directionGen(float seed);

	COORD playerHoming(COORD playerPos1, COORD playerPos2);

	void pathFind(COORD &currDir);

	void moveEnemy(Map* map, Console* console);

	void destroyEnemy(Map* map);

private:
	COORD spawnNonce = { 20, 10 };

	int aggroRange = 15;
};

#endif