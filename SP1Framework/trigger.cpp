#include "trigger.h"

Trigger::Trigger(Map* map)
{
	initTrigger(map);	
}

void Trigger::initTrigger(Map* map)
{
	boulderInit(map);
}

void Trigger::boulderInit(Map* map)
{
	//deletes all previous boulder
	for (int i = 0; i < allBoulders.size(); i++)
	{
		delete allBoulders[i];		
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
		if (allBoulders[i]->m_cLocation.X == c.X && allBoulders[i]->m_cLocation.Y == c.Y)
		{
			return allBoulders[i];
		}
	}
	return NULL;
}

 