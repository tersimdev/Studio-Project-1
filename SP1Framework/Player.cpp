#include "player.h"

/*CONSTRUCTORS*/

SGameChar::SGameChar(char symb, int hp, WORD col, COORD location)
{
	this->symbol = symb;
	this->health = hp;
	this->color = col;
	this->m_cLocation = location;
};


Gun::Gun(COORD loc)
{
	this->bulletPos = loc;
}

/*FUNCTIONS*/

void Gun::shoot(COORD playerPos, SHORT dirX, SHORT dirY)
{
	int range = this->range;
	if ( ((dirX == 1 && bulletPos.X < playerPos.X + range) 
		|| (dirX == -1 && bulletPos.X > playerPos.X - range) )
		|| ( (dirY == 1 && bulletPos.Y < playerPos.Y + (range >> 1)) 
		|| (dirY == -1 && bulletPos.Y > playerPos.Y - (range >> 1))) )
	{
		this->bulletPos.X += dirX;
		this->bulletPos.Y += dirY;
		outOfRange = true;
	}
	else outOfRange = false;
		
}