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
	
	vector<char> mapArray;
	
	const static int numOfLevels = 6;
	int rows, cols, mapLevel = 0;
	
	void updateMap(int level);
	void updateMap();

	void loadMap(string fileName); //loads map into array
	
	bool collideWithWall(COORD c); //check if there is wall at c

	bool findChar(COORD c, char target); //check for a char in the map

	string mapNames[numOfLevels] = { "Levels/01.txt", "Levels/02.txt" , "Levels/03.txt", "Levels/04.txt", "Levels/05.txt", "Levels/06.txt" };
};


#endif
