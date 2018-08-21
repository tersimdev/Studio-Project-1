#include "boss.h"

Boss::Boss(Map* map, Console* console, COORD* playerPos1, COORD* playerPos2)
{
	this->bossInit(map, console, playerPos1, playerPos2);
}

void Boss::bossInit(Map* map, Console* console, COORD* playerPos1, COORD* playerPos2)
{
	//storing original player pos
	this->originalPlayerPos1 = *playerPos1;
	this->originalPlayerPos2 = *playerPos2;
	//intialising position of player
	playerPos1->X = (SHORT)(console->getConsoleSize().X * 0.5 - 1);
	playerPos1->Y = (SHORT)(console->getConsoleSize().Y * 0.75 - 1);
	playerPos2->X = (SHORT)(console->getConsoleSize().X * 0.5 - 1);
	playerPos2->Y = (SHORT)(console->getConsoleSize().Y * 0.75 + 1);
	map->loadMap("Levels/BOSS1.txt");

	vector<COORD> c;
	vector<COORD> dir;
	c.push_back({ 100, 0 });
	dir.push_back({ 0, 1 });
	this->initBullets(c, dir);
}

//call respective inits first
void Boss::renderBossAttack(int index, Console* console)
{
	switch (index)
	{
	default:
	case 1:
		this->renderBulletAtk(console);
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void Boss::initBullets(vector<COORD> &postitions, vector<COORD> &directions)
{
	this->bulletAttack.bulletPosts = postitions;
	this->bulletAttack.bulletDirs = directions;
}

void Boss::renderBulletAtk(Console* console)
{
	for (int i = 0; i < this->bulletAttack.bulletPosts.size(); i++)
	{
		console->writeToBuffer(this->bulletAttack.bulletPosts[i], 'H', 0x0E);
		this->bulletAttack.bulletPosts[i] = ADDCOORDS(this->bulletAttack.bulletPosts[i], this->bulletAttack.bulletDirs[i]);
	}	
}



BulletAttack::BulletAttack() {}