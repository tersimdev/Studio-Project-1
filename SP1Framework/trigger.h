#ifndef _TRIGGER_H
#define _TRIGGER_H
#include "Framework\console.h"
#include "map.h"
#include "player.h"
#include "boulders.h"
#include <vector>
using std::vector;

class Trigger
{
public:
	Trigger(Map* map);
	
	void initTrigger(Map* map);

	/*Boulders*/
	Boulder* boulder = NULL;
	
	vector<Boulder*> allBoulders;

	void boulderInit(Map* map);

	Boulder* findBoulder(COORD c);
};

#endif