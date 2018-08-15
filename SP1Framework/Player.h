#ifndef _PLAYER_H
#define _PLAYER_H

#include "game.h"

// struct for the game character
class SGameChar : public Organism
{
public:
	SGameChar(char symb, int hp, WORD col, COORD location = { 3, 3 });
	struct Gun *gun = NULL;

private:
	int health;
};


struct Gun
{
public:
	Gun(COORD loc);

	COORD bulletPos;
	COORD direction = { 0,0 };

	bool outOfRange= false;

	void shoot(COORD playerPos, SHORT dirX, SHORT dirY); //updates position of bullet to be rendered

	int getRange() { return range; }
	double getFirerate() { return firerate; }
private:
	double firerate = 1.0;
	int range = 25;
};

#endif