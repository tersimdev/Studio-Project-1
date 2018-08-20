/*#ifndef _ASTAR_H
#define _ASTAR_H
#include "Framework/console.h"
#include <vector>
using std::vector;

struct Node
{
	COORD c;
	COORD parent;
	float gCost, hCost, fCost;
};

class aStar
{
public:
	aStar(Console* console);

	Console* console;

	COORD consoleSize;

	bool isValid(COORD c);

	bool isDest(COORD c, Node dest);

	double calcH(COORD c, Node dest);

	vector<Node> makePath(Node* map, Node dest);
	
	vector<Node> aStarSearch(Node player, Node dest);
};

#endif*/
