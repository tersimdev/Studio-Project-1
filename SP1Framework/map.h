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
#define _B (char)234
#define _E (char)227
#define _N (char)178
#define _U (char)164
#define _I (char)209
#define _K (char)213
#define _M (char)156
#define _T (char)232
#define _A (char)4 
#define _R (char)237 
#define _0 (char)176
#define _5 (char)219
#define _D (char)176
#define _F (char)146

class Map
{
public:
	Map(int index);
	Map(string fileName);

	const static int numOfLevels = 6;

	vector<char> mapArray;

	const vector<char> colllidables = { 'Z' , 'U' , 'B' , 'E' , 'N' , 'R' , 'M' , 'T' , 'F' }; //add to this when needed

	vector<string> mapNames;
	
	//num of rows, num of columns, and current map level form ai ngame
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
