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
	srand((unsigned int)time(NULL));
}

void Boss::initAttacks()
{
	switch (this->attackIndex)
	{
	case 0:
	case 2:
		this->initBullets();
		//some dialogue for fun
		switch (rand() % 5)
		{
		case 0:
			this->message = "TAKE THIS!";
			break;
		case 1:
			this->message = "...";
			break;
		case 2:
			this->message = "I MUST CAPTURE YOU!";
			break;
		case 3:
			this->message = "UNPARALLED SPHAGETTORE";
			break;
		case 4:
			this->message = "DON'T MAKE ME...";
			break;
		}
		break;
	case 1:
		this->message = "YOU'RE BLUE NOW...THAT'S MY ATTACK";
		break;
	}
}

void Boss::initBullets()
{
	vector<COORD> pos;
	vector <COORD> dir;
	COORD cp, cd;
	switch (rand() % 9)
	{
	case 2: //up and down
			//same as case 1
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
		//fallthrough
	case 0: //down
	
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
		this->bulletAttack.bullet = (char)233;
		break;
	case 1: //up
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
		this->bulletAttack.bullet = (char)233;
		break;
	case 5: //right and left
		for (int i = 0; i < boxHeight; i++)
		{
			if (!(i % 2))
				cp.X = boxLeftTop.X + boxWidth + 2;
			else
				cp.X = boxLeftTop.X - 2;

			cp.Y = boxLeftTop.Y + i;
			pos.push_back(cp);
			cd = { 1 , 0 };
			dir.push_back(cd);
		}
		break;
	case 3: //right
		for (int i = 0; i < boxHeight; i++)
		{
			cp.X = boxLeftTop.X - 2;
			cp.Y = boxLeftTop.Y + i;
			pos.push_back(cp);
			cd = { 1 , 0 };
			dir.push_back(cd);
		}
		this->bulletAttack.bullet = (char)222;
		break;
	case 4: //left
		for (int i = 0; i < boxHeight; i++)
		{
			cp.X = boxLeftTop.X - 2;
			cp.Y = boxLeftTop.Y + i;
			pos.push_back(cp);
			cd = { 1 , 0 };
			dir.push_back(cd);
		}
		this->bulletAttack.bullet = (char)222;
		break;
	case 8: //middle
		//same as case 7
		for (int i = 0; i < boxHeight; i++)
		{
			if (!(i % 2))
			{
				cp.X = boxLeftTop.X + (boxWidth >> 1) + 2;
				cp.Y = boxLeftTop.Y + i;
				pos.push_back(cp);
				cd = { -1 , 0 };
				dir.push_back(cd);
			}
		}
		//fallthrough
	case 6: //middle right
		for (int i = 1; i < boxHeight; i++)
		{
			if (i % 2)
			{
				cp.X = boxLeftTop.X + (boxWidth >> 1) - 2;
				cp.Y = boxLeftTop.Y + i;
				pos.push_back(cp);
				cd = { 1 , 0 };
				dir.push_back(cd);
			}
		}
		this->bulletAttack.bullet = (char)221;
		break;
	case 7: //middle left
		for (int i = 0; i < boxHeight; i++)
		{
			if (!(i % 2))
			{
				cp.X = boxLeftTop.X + (boxWidth >> 1) + 2;
				cp.Y = boxLeftTop.Y + i;
				pos.push_back(cp);
				cd = { -1 , 0 };
				dir.push_back(cd);
			}
		}
		this->bulletAttack.bullet = (char)221;
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
	case 2:
		for (unsigned int i = 0; i < this->bulletAttack.bulletPosts.size(); i++)
		{
			this->bulletAttack.bulletPosts[i] = ADDCOORDS(this->bulletAttack.bulletPosts[i], this->bulletAttack.bulletDirs[i]);
		}
		break;
	case 1: //change player color in game.cpp
		break;
	}
}

bool Boss::collision(COORD playerPos)
{
	for (unsigned int i = 0; i < this->bulletAttack.bulletPosts.size(); i++)
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
		break;
	}
	console->writeToBuffer(this->dialoguePos, message, 0x0F);
}



void Boss::renderBulletAtk(Console* console)
{
	for (unsigned int i = 0; i < this->bulletAttack.bulletPosts.size(); i++)
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
