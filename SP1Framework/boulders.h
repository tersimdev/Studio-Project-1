#ifndef _BOULDER_H
#define _BOULDER_H
#include "Framework\console.h"
#include "trigger.h"
#include "map.h"
#include <vector>
using std::vector;

void bouldersInit(Map* map);

class Boulder : public Trigger
{
public:
	Boulder();
	Boulder(COORD location);

	//void moveBoulder(Map* map, Console* console, SGameChar* player);

	//void destroyBoulder();
};

class Boulders 
{
public:
	Boulders(vector<COORD>* c);

	vector<Boulder> allBoulders;

	Boulder* findBoulder(COORD thisPos);
};
#endif