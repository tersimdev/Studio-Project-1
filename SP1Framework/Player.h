#ifndef _PLAYER_H
#define _PLAYER_H
#include "Framework\console.h"
#include "organism.h"
#include "map.h"

// struct for the game character
class SGameChar : public Organism
{
public:
	SGameChar(char symb, int hp, WORD col, Map* map, int player = 1);
	struct Gun *gun = NULL;

private:
	int health;
};



struct Gun
{
public:
	Gun(COORD loc, COORD dir);

	COORD bulletPos;
	COORD playerPos;
	COORD direction = { 0,0 };

	bool outOfRange = false;

	void shoot(SGameChar* player); //updates position of bullet to be rendered

private:
	int range = 25; //range of gun
};

#endif