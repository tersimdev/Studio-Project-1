#ifndef _PLAYER_H
#define _PLAYER_H
#include "Framework\console.h"
#include "organism.h"
#include "map.h"

// struct for the game character
class SGameChar : public Organism
{
public:
	SGameChar::SGameChar();
	SGameChar(char symb, WORD col, Map* map, int player = 1);

	COORD playerUIPos = {10, 0};
	string playerHPUI = "";
	string playerHPText = "";
	string playerLivesText = "";

	struct Gun *gun = NULL;

	string updateHealth(int playerNum, int dmg);
	string updateLives(int playerNum, int loss);
	string updateHealthUI(int playerNum);

private:
	int maxHealth = 30;
	int health = maxHealth;
	int lives = 3;
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

	bool collision(Map* map, Console* console); //checks if bullet hits wall or out of range

private:
	int range = 25; //range of gun
};

#endif