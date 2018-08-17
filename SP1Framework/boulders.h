#ifndef _BOULDER_H
#define _BOULDER_H
#include "Framework\console.h"
#include "trigger.h"
#include "player.h"

class Boulder : public Trigger
{
public:
	Boulder(COORD location);

	void moveBoulder(Map* map, Console* console, SGameChar* player);
};

#endif