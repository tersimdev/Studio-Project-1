#ifndef _PLAYER_H
#define _PLAYER_H

#include "game.h"

// struct for the game character
class SGameChar
{
public:
	SGameChar(char symb, int hp, WORD color, COORD location = { 3, 3 });

	char symbol; //ascii character
	WORD color; //color of char
	COORD m_cLocation; //position of player
	COORD direction = { 1, 0 }; //direction of movement
	COORD m_futureLocation; //future position of player
	bool  m_bActive = true; //whether player is active

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
	double firerate = 3.0;
	int range = 35;
};

#endif