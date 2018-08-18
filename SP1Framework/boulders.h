#ifndef _BOULDER_H
#define _BOULDER_H
#include "Framework\console.h"
#include "trigger.h"
#include <vector>
using std::vector;

class Boulders 
{
public:
	Boulders(vector<COORD>* c);
};


class Boulder : public Trigger
{
public:
	Boulder(COORD location);

	//void moveBoulder(Map* map, Console* console, SGameChar* player);

	//void destroyBoulder();
};

#endif