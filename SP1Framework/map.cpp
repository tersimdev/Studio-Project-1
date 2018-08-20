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
		if (this->findCharExists(c, this->colllidables[i]))
			return true;
	}
	return false;
}

bool Map::findCharExists(COORD c, char target)
{
	if (this->mapArray[(c.Y - 1) * this->cols + c.X] == target)
	{
		return true;
	}
	else return false;
}

COORD Map::findChar(char target)
{
	COORD c;
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			if (this->mapArray[i * this->cols + j] == target)
			{
				c.X = j;
				c.Y = i + 1;
				return c;
			}
		}
	}
}

void Map::findChars(char target, vector<COORD>* c)
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			if (this->mapArray[i * this->cols + j] == target)
			{
				c->push_back({ (SHORT)j, (SHORT)(i + 1) });
			}
		}
	}
}

char Map::addChar(COORD c, char add)
{
	char replacedChar = this->mapArray[(c.Y - 1) * this->cols + c.X];
	this->mapArray[(c.Y - 1) * this->cols + c.X] = add;
	return replacedChar;
}

void Map::removeChar(COORD c, char replace)
{
	this->mapArray[(c.Y - 1) * this->cols + c.X] = replace;
}

void Map::replaceAndRender(Console* console)
{
	COORD c = { 0, 1 };
	string line = "";
	char currChar;
	WORD color;
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			//add characters to line, replacing depending on char
			currChar = this->mapArray[i * this->cols + j];
			switch (currChar)
			{
			case 'Z': //walls
				currChar = _Z;
				color = 0x08;
				break;
			case 'B': //boulder
				currChar = _B;
				color = 0x07;
				break;
			case 'E':
				currChar = _E;
				color = 0x0D;
				break;
			case 'N': //transitions
				currChar = _N;
				color = 0x0F;
				break;
			case 'P': //player1
			case 'p': //player1 hp
			case 'S': //player2
			case 's': //player2 hp
			case 'e': //enemy spawn reference
				currChar = ' ';
				break;
			case 'U':
				currChar = _U;
				color = 0x0B;
				break;
			case '0': //text
				currChar = _0;
				color = 0x03;
				break;
			default:
				color = 0x0F;
			}
			c.X = j; //next char
					 //write to buffer, one char
			console->writeToBuffer(c, currChar, color);

		}
		c.Y++; //next line
		line = ""; //clear line for next line
	}
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