#ifndef _PLAYER_H
#define _PLAYER_H

#include "game.h"

// struct for the game character
class SGameChar
{
	public:
		SGameChar(char symb, int hp, WORD color, COORD location = {3, 3});

		char symbol; //ascii character
		WORD color; //color of char
		COORD m_cLocation; //position of player
		COORD m_futureLocation = { 1, 0 }; //future location of player
		bool  m_bActive = true; //whether player is active

		int health;

		struct Gun *gun = NULL;
};


struct Gun
{
	Gun(COORD loc);

	COORD bulletPos;
	COORD direction = { 0,0 };

	bool outOfRange;
	int range = 20;

	void shoot(COORD playerPos, SHORT dirX, SHORT dirY); //updates position of bullet to be rendered
};

#endif