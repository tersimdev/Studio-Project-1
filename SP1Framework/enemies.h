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

	COORD dirToPlayerX = { 0 , 0 };
	COORD dirToPlayerY = { 0 , 0 };
	COORD dirToPlayerInvX = { 0 , 0 }; 
	COORD dirToPlayerInvY = { 0 , 0 };;
	
	void locationGen(Map* map, Console* console);
	
	COORD directionGen(double seed);

	bool isAggro(COORD playerPos);

	void setGeneralDir(COORD playerPos);

	void setAltDir(Map* map, COORD playerPos);

	void moveEnemy(Map* map, Console* console);

	void destroyEnemy(Map* map);
	
	bool enemyAttack(COORD playerPos);

private:
	COORD spawnNonce = { 20, 10 };

	int aggroRange = 20;
};

#endif