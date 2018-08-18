#include "player.h"

/*CONSTRUCTORS*/

SGameChar::SGameChar(char symb, int hp, WORD col, Map* map, int player)
{
	this->symbol = symb;
	this->health = hp;
	this->color = col;
	this->direction = { 1 , 0 };
	this->m_futureLocation = ADDCOORDS(m_cLocation, direction);

	//setting position, based on map
	for (int i = 0; i < map->rows; i++)
	{
		for (int j = 0; j < map->cols; j++)
		{
			if (player == 1 && map->mapArray[i * map->cols + j] == 'P')
			{
				COORD c = { j, i + 1 };
				this->m_cLocation = c;
			}	
		}
	}
};


Gun::Gun(COORD loc, COORD dir)
{
	this->bulletPos = loc;
	this->playerPos = loc;
	this->direction = dir;
}

/*FUNCTIONS*/

void Gun::shoot(SGameChar* player)
{	
	int range = this->range;
	//if bullet within range, add to bullet position
	if ( ((direction.X == 1 && bulletPos.X < playerPos.X + range) 
		|| (direction.X == -1 && bulletPos.X > playerPos.X - range) )
		|| ( (direction.Y == 1 && bulletPos.Y < playerPos.Y + (range >> 1))
		|| (direction.Y == -1 && bulletPos.Y > playerPos.Y - (range >> 1))) )
	{
		this->bulletPos.X += this->direction.X;
		this->bulletPos.Y += this->direction.Y;
		outOfRange = false;
	}
	else outOfRange = true;
		
}