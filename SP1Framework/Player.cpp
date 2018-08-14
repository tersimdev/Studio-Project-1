#include "player.h"

// Constructor

SGameChar::SGameChar(char symb, int hp, WORD col, COORD location)
{
	this->symbol = symb;
	this->health = hp;
	this->color = col;
	this->m_cLocation = location;
};


Bullet::Bullet() {}
Bullet::Bullet(COORD loc)
{
	this->location = loc;
}
/*FUNCTIONS*/

void Bullet::shoot(COORD playerPos, SHORT dirX, SHORT dirY)
{
	int range = this->range;
	if ((dirX == 1 && location.X < playerPos.X + range) || (dirX == -1 && location.X > playerPos.X - range))
	{
		this->location.X += dirX;
		this->location.Y += dirY;
		outOfRange = true;
	}
	else if ((dirY == 1 && location.Y < playerPos.Y + (range >> 1)) || (dirY == -1 && location.Y > playerPos.Y - (range >> 1)))
	{
		this->location.X += dirX;
		this->location.Y += dirY;
		outOfRange = true;
	}
	else outOfRange = false;
		
}