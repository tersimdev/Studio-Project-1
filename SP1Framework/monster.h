#ifndef _MONSTER_H
#define _MONSTER_H
#include "Framework\console.h"

class PacmanMonster
{
public:

	char symbol; //ascii character
	WORD color; //color of char
	COORD m_cLocation; //position
	COORD direction; //direction of movement
	COORD m_futureLocation = m_cLocation; //future position 
	bool  m_bActive = true; //whether is alive
};

#endif

