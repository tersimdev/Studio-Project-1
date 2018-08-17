#include "map.h"

/*CONSTRUCTOR*/
Map::Map(int index)
{
	mapNamesInit();
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

void Map::updateMap()
{
	this->mapLevel++;
	this->mapLevel %= this->numOfLevels;
	this->loadMap(this->mapNames[this->mapLevel]);
}

bool Map::collideWithWall(COORD c)
{
	for (int i = 0; i < colllidables.size(); i++)
	{ 
		if (this->findChar(c, this->colllidables[i]))
			return true;
	}
	return false;
}

bool Map::findChar(COORD c, char target)
{
	if (this->mapArray[(c.Y - 1) * this->cols + c.X] == target)
	{
		return true;
	}
	else return false;
}

void Map::moveChar(char target, COORD c, COORD dir)
{
	this->mapArray[(c.Y - 1) * this->cols + c.X] = prevChar;
	c = ADDCOORDS(c, dir);
	prevChar = this->mapArray[(c.Y - 1) * this->cols + c.X];
	this->mapArray[(c.Y - 1) * this->cols + c.X] = target;
}

void Map::mapNamesInit()
{
	for (int i = 0; i < this->numOfLevels; i++)
	{
		string name;
		name = "Levels/" + std::to_string(i);
		this->mapNames.push_back(name + ".txt");
	}
}