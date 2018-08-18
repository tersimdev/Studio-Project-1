#ifndef _MAP_H
#define _MAP_H
#include "Framework\console.h"
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

	vector<char> colllidables = { 'Z' , 'U' , 'B' }; //add to this when needed

	vector<string> mapNames;
	
	int rows, cols, mapLevel = 0;

	void updateMap();
	void updateMap(int level);	

	void loadMap(string fileName); //loads map into array
	
	bool collideWithWall(COORD c); //check if there is wall at c

	bool findChar(COORD c, char target); //check for a char in the map

	void moveChar(char target, COORD c, COORD dir);

	char addChar(COORD c, char add); //returns replaced char

	void removeChar(COORD c); //removes char at c with ' '
	
	void replaceAndRender(Console* console);

private:

	void mapNamesInit();
};


#endif
