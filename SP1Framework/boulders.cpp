#include "boulders.h"

Boulder::Boulder(COORD location)
{
	this->m_cLocation = location;
}

void Boulder::moveBoulder(Map* map, Console* console, SGameChar* player)
{
	if (m_cLocation.Y > 1 && m_cLocation.X > 0
		&& m_cLocation.Y < console->getConsoleSize().Y - 1
		&& m_cLocation.X < console->getConsoleSize().X - 1) //if at console edge
	{
		if (!map->collideWithWall(ADDCOORDS(this->m_cLocation, { player->direction.X << 1,  player->direction.Y << 1 }))) //if boulder not colliding with walls
		{
			map->moveChar('B', this->m_cLocation, player->direction);
			player->m_cLocation = ADDCOORDS(player->m_cLocation, player->direction);
		}
	}
}