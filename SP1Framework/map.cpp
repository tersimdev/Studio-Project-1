#include "map.h"

/*CONSTRUCTOR*/
Map::Map(int index)
{
	loadMap(mapNames[index]);
}

/*FUNCTIONS*/
void Map::loadMap(string fileName)
{
	//re-initialising all vars
	string line = "";
	cols = 0;
	rows = 0;
	this->mapArray.clear();
	//opening file
	std::ifstream file(fileName);
	//getting row and columns of map
	getline(file, line);
	cols = stoi(line);
	getline(file, line);
	rows = stoi(line);
	while (getline(file, line))
	{
		for (int i = 0; i < cols; i++)
		{
			this->mapArray.push_back(line[i]); //adding to array
		}
	}
	file.close();
}

void Map::updateMap(int level)
{
	this->mapLevel = level;
	this->loadMap(this->mapNames[this->mapLevel]);
}

bool Map::collideWithWall(COORD c)
{
	if (this->mapArray[(c.Y - 1) * this->cols + c.X] != ' ')
	{
		return true;
	}
	else return false;
}
