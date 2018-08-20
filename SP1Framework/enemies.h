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

	void locationGen(Map* map, Console* console);

	void moveEnemy(Map* map, Console* console, COORD dir);

	void destroyEnemy(Map* map);

	COORD m_cLocation;

	char prevChar = ' ';

private:
	COORD spawnNonce = { 20, 10 };
};

#endif