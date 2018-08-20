#include "enemies.h"

Enemy::Enemy(COORD loc, Map* map, Console* console)
{
	this->m_cLocation = loc;
	srand(time(NULL));
	locationGen(map, console);
}

void Enemy::locationGen(Map* map, Console* console)
{
	COORD nonce;
	COORD originalPos = this->m_cLocation;
	do {
		originalPos = this->m_cLocation;
		nonce.X = rand() % this->spawnNonce.X;
		nonce.Y = rand() % this->spawnNonce.Y;
		originalPos = ADDCOORDS(originalPos, nonce);
	} while (!console->isInsideConsole(originalPos) || map->collideWithWall(originalPos));
	this->m_cLocation = originalPos;
	moveEnemy(map, console, { 0,0 }); // move to new location
}

void Enemy::moveEnemy(Map* map, Console* console, COORD dir)
{
	if (!EQUCOORDS(dir, {0,0}))
		map->removeChar(this->m_cLocation, this->prevChar); //remove the E and replace with prevchar
	this->m_cLocation = ADDCOORDS(this->m_cLocation, dir);
	this->prevChar = map->addChar(this->m_cLocation, 'E'); //places the new E and store as prevchar
}

void Enemy::destroyEnemy(Map* map)
{
	map->removeChar(this->m_cLocation, this->prevChar);
	//deletion handled when re-initializing
}