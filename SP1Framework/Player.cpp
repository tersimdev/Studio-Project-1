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


Gun::Gun(COORD loc)
{
	this->bulletPos = loc;
}

/*FUNCTIONS*/

void Gun::shoot(SGameChar* player)
{
	//change direction if none initialized
	if (this->direction.X == 0 && this->direction.Y == 0)
		this->direction = player->direction;
	
	int range = this->range;
	//if bullet within range, add to bullet position
	if ( ((player->direction.X == 1 && bulletPos.X < player->m_cLocation.X + range) 
		|| (player->direction.X == -1 && bulletPos.X > player->m_cLocation.X - range) )
		|| ( (player->direction.Y == 1 && bulletPos.Y < player->m_cLocation.Y + (range >> 1))
		|| (player->direction.Y == -1 && bulletPos.Y > player->m_cLocation.Y - (range >> 1))) )
	{
		this->bulletPos.X += player->direction.X;
		this->bulletPos.Y += player->direction.Y;
		outOfRange = false;
	}
	else outOfRange = true;
		
}