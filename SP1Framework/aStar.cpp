#include "aStar.h"

aStar::aStar(int x, int y, Console* console)
{
	this->mapSize = {(SHORT)x, (SHORT)y};
	this->console = console;
}

bool aStar::isValid(COORD c)
{
	return (console->isInsideConsole(c));
}

bool aStar::isDest(COORD c, Node dest)
{
	return (c.X == dest.X && c.Y == dest.Y);
}

double aStar::calcH(COORD c, Node dest)
{
	//square rooting makes it more accurate, but is it worth it?
	return (c.X - dest.X) *(c.X - dest.X) + (c.Y - dest.Y) * (c.Y - dest.Y);
}

vector<Node> aStar::makePath(vector<Node> &map, Node dest)
{
	Node c = dest;
	vector<Node> path;
	

	while (!(map[c.Y * mapSize.X + c.X].parent.X == c.X && map[c.Y * mapSize.X + c.X].parent.Y == c.Y)
		&& map[c.Y * mapSize.X + c.X].X != -1 && map[c.Y * mapSize.X + c.X].Y != -1)
	{
		path.push_back(map[c.Y * mapSize.X + c.X]);
		int tempX = map[c.Y * mapSize.X + c.X].parent.X;
		int tempY = map[c.Y * mapSize.X + c.X].parent.Y;
		c.X = tempX;
		c.Y = tempY;
	}
	//reverse the path to become usable
	std::reverse(path.begin(), path.end());

	return path;
}

//main alg
vector<Node> aStar::aStarSearch(Node player, Node dest)
{
	//catch if nodes are within console or dest is reached
	vector<Node> empty;
	if (!isValid({dest.X, dest.Y}))
		return empty;
	if (isDest({ player.X, player.Y }, dest))
		return empty;

	//init closedlist and map
	vector<bool> closedList = vector<bool>(mapSize.X * mapSize.Y + 1);
	vector<Node> map = vector<Node> (mapSize.X * mapSize.Y + 1);
	for (int x = 0; x < mapSize.X; x++)
	{
		for (int y = 0; y < mapSize.Y; y++)
		{
			map[y * mapSize.X + x].fCost = FLT_MAX;
			map[y * mapSize.X + x].gCost = FLT_MAX;
			map[y * mapSize.X + x].hCost = FLT_MAX;
			map[y * mapSize.X + x].parent = { -1, -1 };
			map[y * mapSize.X + x].X = (SHORT)x;
			map[y * mapSize.X + x].Y = (SHORT)y;

			closedList[y * mapSize.X + x] = false;
		}
	}

	vector<Node> openList;

	//init player and add it, the root node, to open list
	Node c = player;
	map[c.Y * mapSize.X + c.X].fCost = 0.0;
	map[c.Y * mapSize.X + c.X].gCost = 0.0;
	map[c.Y * mapSize.X + c.X].hCost = 0.0;
	map[c.Y * mapSize.X + c.X].parent = c;

	openList.emplace_back(map[c.Y * mapSize.X + c.X]);
	bool destFound = false;

	//main alg loop
	while (!openList.empty() && openList.size() < (unsigned int)(mapSize.X * mapSize.Y + 1))
	{
		//find lowest fcost node and store it in node
		Node node;
		double temp = FLT_MAX;
		for (unsigned int i = 0; i < openList.size(); i++)
		{
			if (openList[i].fCost < temp)
			{
				temp = openList[i].fCost;
				node = openList[i];
			}
			openList.erase(openList.begin() + i);
		}

		//switch current node to node with lowest fcost
		c = node;
		//add to closedlist
		closedList[c.Y * mapSize.X + c.X] = true;

		//iterate through the 8 nodes around this node
		for (int newX = -1; newX <= 1; newX++) 
		{
			for (int newY = -1; newY <= 1; newY++) 
			{
				double gNew, hNew, fNew;
				if (isValid({ (SHORT)(c.X + newX), (SHORT)(c.Y + newY) }))
				{
					if (isDest({ (SHORT)(c.X + newX), (SHORT)(c.Y + newY) }, dest))
					{
						//set current node to be its own parent
						map[(c.Y + newY) * mapSize.X + (c.X + newX)].parent.X = c.X;
						map[(c.Y + newY) * mapSize.X + (c.X + newX)].parent.Y = c.Y;
						destFound = true;
						return makePath(map, dest);
					}
					else if (!closedList[(c.Y + newY) * mapSize.X + (c.X + newX)]) //if not in closed list
					{
						//calculate fcost
						gNew = node.gCost + 1.0;
						hNew = calcH({ (SHORT)(c.X + newX), (SHORT)(c.Y + newY) }, dest);
						fNew = gNew + hNew;
						//check if this neighbour is in openlist or if uninitialized ie check all neighbours not checked
						if (map[(c.Y + newY) * mapSize.X + (c.X + newX)].fCost == FLT_MAX ||
							map[(c.Y + newY) * mapSize.X + (c.X + newX)].fCost > fNew)
						{
							//updates the cost of this neighbour
							map[(c.Y + newY) * mapSize.X + (c.X + newX)].fCost = fNew;
							map[(c.Y + newY) * mapSize.X + (c.X + newX)].gCost = gNew;
							map[(c.Y + newY) * mapSize.X + (c.X + newX)].hCost = hNew;
							//make current node the parent of this neighbour node
							map[(c.Y + newY) * mapSize.X + (c.X + newX)].parent.X = c.X;
							map[(c.Y + newY) * mapSize.X + (c.X + newX)].parent.Y = c.Y;
							//add to openlist
							openList.emplace_back(map[(c.Y + newY) * mapSize.X + (c.X + newX)]);
						}
					}
				}
			}
		}
	}
	if (!destFound) 
		return empty;

}