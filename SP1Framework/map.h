#ifndef _MAP_H
#define _MAP_H
#include "game.h"
#include <vector>
#include <fstream>
#include <string>
using std::vector;
using std::string;

class Map
{
public:

	Map(int index);

	const static int numOfLevels = 6;

	vector<char> mapArray;

	vector<string> mapNames;
	void Map::mapNamesInit();
	
	int rows, cols, mapLevel = 0;
	
	void updateMap(int level);
	void updateMap();

	void loadMap(string fileName); //loads map into array
	
	bool collideWithWall(COORD c); //check if there is wall at c

	bool findChar(COORD c, char target); //check for a char in the map
};


#endif
