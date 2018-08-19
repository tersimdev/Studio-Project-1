#ifndef _BOULDER_H
#define _BOULDER_H
#include "Framework\console.h"
#include "map.h"
#include "player.h"
#include <vector>
using std::vector;

class Boulder
{
public:
	Boulder();
	Boulder(COORD location);

	COORD m_cLocation; //position

	char prevChar = ' ';

	void moveBoulder(Map* map, SGameChar* player, Console* console);

	void destroyBoulder(Map* map);
};
#endif