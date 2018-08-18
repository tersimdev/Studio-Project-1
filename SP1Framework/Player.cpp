#include "player.h"

#define spaceUI "          "

/*CONSTRUCTORS*/

SGameChar::SGameChar(char symb, WORD col, Map* map, int player)
{
	this->symbol = symb;
	this->color = col;
	this->direction = { 1 , 0 };
	this->m_futureLocation = ADDCOORDS(m_cLocation, direction);
	this->playerHPUI = updateHealth(player, 0);

	//setting positions, based on map
	COORD c;
	for (int i = 0; i < map->rows; i++)
	{
		for (int j = 0; j < map->cols; j++)
		{
			
			if (player == 1 && map->mapArray[i * map->cols + j] == 'P')
			{
				c = { (SHORT) j,(SHORT)(i + 1) };
				this->m_cLocation = c;
			}	
			else if (player == 1 && map->mapArray[i * map->cols + j] == 'p')
			{
				c = { (SHORT)j,(SHORT)(i + 1) };
				this->playerUIPos = c;
			}
			if (player == 2 && map->mapArray[i * map->cols + j] == 'S')
			{
				c = { (SHORT)j,(SHORT)(i + 1) };
				this->m_cLocation = c;
			}
			else if (player == 2 && map->mapArray[i * map->cols + j] == 's')
			{
				c = { (SHORT)j,(SHORT)(i + 1) };
				this->playerUIPos = c;
			}
		}
	}
};

string SGameChar::updateHealth(int playerNum, int dmg)
{
	if (this->health != 0 && this->health <= this->maxHealth)
		this->health -= dmg;
	return updateHealthUI(playerNum);
}

string SGameChar::updateLives(int playerNum, int loss)
{
	if (this->lives != 0)
		this->lives -= loss;
	return updateHealthUI(playerNum);
}

string SGameChar::updateHealthUI(int playerNum)
{
	//updating health
	this->playerHPText = "PLAYER " + std::to_string(playerNum) + " HP : ";
	this->playerLivesText = "LIVES: ";
	for (int i = 0; i < this->health; i++)
	{
		playerHPText += '/';
	}
	for (int i = 0; i < this->maxHealth - this->health; i++)
	{
		playerHPText += '-';
 	}
	
	string spaces = "     ";
	if (this->health < 10)
		spaces += ' ';
	playerHPText += spaces + std::to_string(this->health) + " / " + std::to_string(this->maxHealth);
	
	//updating lives
	for (int i = 0; i < lives; i++)
	{
		playerLivesText += "  O  ";
	}
	playerHPUI = playerHPText + spaceUI + playerLivesText;
	return playerHPUI;
}




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