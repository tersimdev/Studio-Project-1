#ifndef _MAP_H
#define _MAP_H
#include "Framework\console.h"
#include "boulders.h"
#include <vector>
#include <fstream>
#include <string>
using std::vector;
using std::string;

class Map
{
public:

	Map(int index);

	Boulder boulder;
	Boulders* boulders = NULL;

	const static int numOfLevels = 6;

	vector<char> mapArray;

	vector<char> colllidables = { 'Z' , 'U' , 'B' }; //add to this when needed

	vector<string> mapNames;
	
	int rows, cols, mapLevel = 0;

	void updateMap(); //loads new level
	void updateMap(int level); //loads new level

	void loadMap(string fileName); //loads map into array

	void loadObjects(); //loads in game objects in map like boulders
	
	bool collideWithWall(COORD c); //check if there is wall at c

	bool findCharExists(COORD c, char target); //check for a char in the map

	COORD findChar(char target); //finds the position of a specific char

	void findChars(char target, vector<COORD>* c); //finds and returns coords of target chars in map

	char addChar(COORD c, char add); //returns replaced char

	void removeChar(COORD c); //removes char at c with ' '
	
	void replaceAndRender(Console* console); //render to console, replacing the chars

private:

	void mapNamesInit(); //inits map names into mapNames array
};


#endif
