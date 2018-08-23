#ifndef _TRIGGER_H
#define _TRIGGER_H
#include "Framework\console.h"
#include "map.h"
#include "player.h"
#include "boulders.h"
#include "enemies.h"
#include <vector>
using std::vector;

class Trigger
{
public:
	Trigger(Map * map, Console* console);
	
	void initTrigger(Map* map, Console* console);

	/*Boulders*/
	Boulder* boulder = NULL;
	
	vector<Boulder*> allBoulders;

	void boulderInit(Map* map);

	Boulder* findBoulder(COORD c);

	/*Enemies*/
	Enemy* enemy = NULL;

	vector<Enemy*> allEnemies;

	void enemyInit(Map* map, Console* console);

	Enemy* findEnemy(COORD c);
};

#endif