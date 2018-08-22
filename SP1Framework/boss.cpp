#include "boss.h"

Boss::Boss(Map* map, Console* console, COORD* playerPos1, COORD* playerPos2, double elapsedTime)
{
	this->bossInit(map, console, playerPos1, playerPos2, elapsedTime);
}

//inits
void Boss::bossInit(Map* map, Console* console, COORD* playerPos1, COORD* playerPos2, double elapsedTime)
{
	//storing original player pos
	this->originalPlayerPos1 = *playerPos1;
	this->originalPlayerPos2 = *playerPos2;
	//storing current elapsed time
	this->bossElapsedTime = elapsedTime;
	//intialising position of player
	playerPos1->X = (SHORT)(console->getConsoleSize().X * 0.5 - 1);
	playerPos1->Y = (SHORT)(console->getConsoleSize().Y * 0.75 - 1);
	playerPos2->X = (SHORT)(console->getConsoleSize().X * 0.5 - 1);
	playerPos2->Y = (SHORT)(console->getConsoleSize().Y * 0.75 + 1);
	map->loadMap("Levels/BOSS1.txt");

	setNumOfAttacks(3);
    initAttacks();

	//setting seed
	srand(time(NULL));
}

void Boss::initAttacks()
{
	switch (this->attackIndex)
	{
	case 0:
		this->initBullets();
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

void Boss::initBullets()
{
	vector<COORD> pos;
	vector <COORD> dir;
	COORD cp, cd;
	switch (rand() % 2)
	{
	case 0:
		for (int i = 0; i < boxWidth; i++)
		{
			if (i % 2)
			{
				cp.X = boxLeftTop.X + i;
				cp.Y = boxLeftTop.Y - 2;
				pos.push_back(cp);
				cd = { 0 , 1 };
				dir.push_back(cd);
			}
		}
		break;
	case 1:
		for (int i = 1; i < boxWidth; i++)
		{
			if (!(i % 2))
			{
				cp.X = boxLeftTop.X + i;
				cp.Y = boxLeftTop.Y + boxHeight + 1;
				pos.push_back(cp);
				cd = { 0 , -1 };
				dir.push_back(cd);
			}
		}
		break;
	case 2:
		break;
	}
	this->bulletAttack.bulletPosts = pos;
	this->bulletAttack.bulletDirs = dir;
}

void Boss::setNumOfAttacks(int index)
{
	this->numOfAttacks = index;
}


//updates
void Boss::attack()
{	
	switch (this->attackIndex)
	{
	default:
	case 0:
		for (int i = 0; i < this->bulletAttack.bulletPosts.size(); i++)
		{
			this->bulletAttack.bulletPosts[i] = ADDCOORDS(this->bulletAttack.bulletPosts[i], this->bulletAttack.bulletDirs[i]);
		}
		break;
	case 1: //change player color in game.cpp
		break;
	case 2:
		break;
	}
}

bool Boss::collision(COORD playerPos)
{
	for (int i = 0; i < this->bulletAttack.bulletPosts.size(); i++)
	{
		if (EQUCOORDS(playerPos, this->bulletAttack.bulletPosts[i]))
		{
			this->bulletAttack.bulletPosts[i] = { NULL, NULL };
			return true;
		}
	}
	return false;
}

void Boss::updateLives(int loss)
{
	if (this->lives != 0)
		this->lives -= loss;
	if (this->lives <= 0)
	{
		this->active = false;
	}
}



//rendering
void Boss::renderBossAttack(Console* console)
{
	switch (this->attackIndex)
	{
	default:
	case 0:
	case 2:
		this->renderBulletAtk(console);
		break;
	case 1:
		console->writeToBuffer({(SHORT)this->boxLeftTop.X, (SHORT)(this->boxLeftTop.Y - 2)}, "YOU'RE BLUE NOW...THAT'S MY ATTACK", 0x0F);
		break;
	}
}



void Boss::renderBulletAtk(Console* console)
{
	for (int i = 0; i < this->bulletAttack.bulletPosts.size(); i++)
	{
		if (console->isInsideConsole(this->bulletAttack.bulletPosts[i])
			&& this->bulletAttack.bulletPosts[i].Y > this->boxLeftTop.Y - 5
			&& this->bulletAttack.bulletPosts[i].Y < this->boxLeftTop.Y + this->boxHeight + 2)
			console->writeToBuffer(this->bulletAttack.bulletPosts[i], this->bulletAttack.bullet, 0x0E);
	}	
}

//attack types

void Boss::changePlayerColor(int player, WORD* color)
{
	player--;
	if (player)
		*color = 0x09;
	else 
		*color = 0x03;
}
