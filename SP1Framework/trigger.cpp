#include "trigger.h"

Trigger::Trigger(Map* map, Console* console)
{
	initTrigger(map, console);	
}

void Trigger::initTrigger(Map* map, Console* console)
{
	boulderInit(map);
	enemyInit(map, console);
}

/*Boulders*/
void Trigger::boulderInit(Map* map)
{
	//deletes all previous boulder
	for (Boulder* ptr : allBoulders)
	{
		delete ptr;
	}
	allBoulders.clear();
	//finds all boulder sand places into vector
	vector<COORD> c;
	map->findChars('B', &c);
	for (int i = 0; i < c.size(); i++)
	{
		allBoulders.emplace_back(new Boulder(c[i]));
	}
}

Boulder* Trigger::findBoulder(COORD c)
{
	for (int i = 0; i < allBoulders.size(); i++)
	{
		if (EQUCOORDS(allBoulders[i]->m_cLocation, c))
		{
			return allBoulders[i];
		}
	}
	return NULL;
}


/*Enemies*/
void Trigger::enemyInit(Map* map, Console* console)
{
	//deletes all previous boulder
	for (Enemy* ptr : allEnemies)
	{
		delete ptr;
	}
	allEnemies.clear();
	//finds all boulder sand places into vector
	vector<COORD> c;
	map->findChars('e', &c);
	for (int i = 0; i < c.size(); i++)
	{
		allEnemies.emplace_back(new Enemy(c[i], map, console));
	}
}

Enemy* Trigger::findEnemy(COORD c)
{
	for (int i = 0; i < allEnemies.size(); i++)
	{
		if (EQUCOORDS(allEnemies[i]->m_cLocation, c))
		{
			return allEnemies[i];
		}
	}
	return NULL;
}

 