#ifndef _MAP_H
#define _MAP_H
#include "Framework\console.h"
#include <vector>
#include <fstream>
#include <string>
using std::vector;
using std::string;


//defining some chars
#define _Z (char)219
#define _B (char)81
#define _E (char)2
#define _N (char)159
#define _U (char)164
#define _I (char)89
#define _K (char)184
#define _0 (char)176

class Map
{
public:
	Map(int index);

	const static int numOfLevels = 6;

	vector<char> mapArray;

	vector<char> colllidables = { 'Z' , 'U' , 'B' , 'E' , 'N' }; //add to this when needed

	vector<string> mapNames;
	
	int rows, cols, mapLevel = 0;

	void updateMap(); //loads new level
	void updateMap(int level); //loads new level

	void loadMap(string fileName); //loads map into array
	
	bool collideWithWall(COORD c); //check if there is wall at c

	bool findCharExists(COORD c, char target); //check for a char in the map

	COORD findChar(char target); //finds the position of a specific char

	void findChars(char target, vector<COORD>* c); //finds and returns coords of target chars in map

	char addChar(COORD c, char add); //returns replaced char

	void removeChar(COORD c, char replace = ' '); //removes char at c with ' '
	
	void replaceAndRender(Console* console); //render to console, replacing the chars

private:

	void mapNamesInit(); //inits map names into mapNames array
};


#endif
