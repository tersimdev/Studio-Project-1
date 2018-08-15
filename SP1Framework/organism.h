#ifndef _ORGANISM_H
#define _ORGANISM_H
#include "game.h"

class Organism
{
public:

	char symbol; //ascii character
	WORD color; //color of char
	COORD m_cLocation; //position
	COORD direction = { 1, 0 }; //direction of movement
	COORD m_futureLocation; //future position 
	bool  m_bActive = true; //whether is active
};

#endif
