#pragma once
#include "game.h"

// struct for the game character
class SGameChar
{
	public:
		SGameChar(char symb, int hp, WORD color, COORD location = {3, 3}); // init hp and dmg

		char symbol; //ascii character
		WORD color; //color of char
		COORD m_cLocation; //position of player
		COORD m_futureLocation = m_cLocation; //future location of player
		bool  m_bActive = true; //whether player is active

		int health;
};


struct Bullet
{
	Bullet();
	Bullet(COORD loc);
	COORD location;
	COORD direction = { 0,0 };
	bool outOfRange;
	int range = 15;
	void shoot(COORD playerPos, SHORT dirX, SHORT dirY);
};