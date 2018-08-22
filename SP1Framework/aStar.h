#ifndef _ASTAR_H
#define _ASTAR_H
#include "Framework/console.h"
#include <vector>
#include <algorithm>
using std::vector;

struct Node : public COORD
{
	COORD parent;
	double gCost, hCost, fCost;
};

class aStar
{
public:
	aStar(int x, int y, Console* console);

	Console* console;

	COORD mapSize;

	bool isValid(COORD c);

	bool isDest(COORD c, Node dest);

	double calcH(COORD c, Node dest);

	vector<Node> makePath(vector<Node> &map, Node dest);
	
	vector<Node> aStarSearch(Node player, Node dest);
};

#endif
