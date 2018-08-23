/*#include "aStar.h"

aStar::aStar(Console* console)
{
	this->consoleSize = console->getConsoleSize();
	this->console = console;
}

bool aStar::isValid(COORD c)
{
	return (console->isInsideConsole(c));
}

bool aStar::isDest(COORD c, Node dest)
{
	return (EQUCOORDS(c, dest.c));
}

double aStar::calcH(COORD c, Node dest)
{
	return (sqrt((c.X - dest.c.X)*(c.X - dest.c.X)
		+ (c.Y - dest.c.Y)*(c.Y - dest.c.Y)));
}

vector<Node> aStar::makePath(Node* map, Node dest)
{
	COORD c = dest.c;
	vector<Node> path;
	vector<Node> usablePath;

	while (!(map[c.X * consoleSize.X + c.Y].parent.X == c.X && map[c.X * consoleSize.X + c.Y].parent.Y == c.Y)
		&& map[c.X * consoleSize.X + c.Y].c.X != -1 && map[c.X * consoleSize.X + c.Y].c.Y != -1)
	{
		path.push_back(map[c.X * consoleSize.X + c.Y]);
		int tempX = map[c.X * consoleSize.X + c.Y].parent.X;
		int tempY = map[c.X * consoleSize.X + c.Y].parent.Y;
		c.X = tempX;
		c.Y = tempY;

	}
	path.push_back(map[c.X * consoleSize.X + c.Y]);

	while (!path.empty()) {
		Node top = path.back();
		path.pop_back();
		usablePath.emplace_back(top);
	}
	return usablePath;
}

//main alg
vector<Node> aStar::aStarSearch(Node player, Node dest)
{
	vector<Node> empty;
	if (!isValid(dest.c))
		return empty;
	if (isDest(player.c, dest))
		return empty;

	bool* closedList = new bool [consoleSize.X * consoleSize.Y + 1];
	Node* map = new Node[consoleSize.X * consoleSize.Y + 1];
	for (int x = 0; x < consoleSize.X; x++)
	{
		for (int y = 0; y < consoleSize.Y; y++)
		{
			map[x * consoleSize.X + y].fCost = FLT_MAX;
			map[x * consoleSize.X + y].gCost = FLT_MAX;
			map[x * consoleSize.X + y].hCost = FLT_MAX;
			map[x * consoleSize.X + y].parent = { -1, -1 };
			map[x * consoleSize.X + y].c = { (SHORT)x, (SHORT)y };

			closedList[x * consoleSize.X + y] = false;
		}
	}

	COORD c = player.c;
	map[c.X * consoleSize.X + c.Y].fCost = 0.0;
	map[c.X * consoleSize.X + c.Y].gCost = 0.0;
	map[c.X * consoleSize.X + c.Y].hCost = 0.0;
	map[c.X * consoleSize.X + c.Y].parent = c;

	vector<Node> openList;
	openList.emplace_back(map[c.X * consoleSize.X + c.Y]);
	bool destFound = false;

	while (!openList.empty() && openList.size() < consoleSize.X * consoleSize.Y + 1)
	{
		Node node;
		do {
			float temp = FLT_MAX;
			vector<Node>::iterator itNode;
			for (vector<Node>::iterator it = openList.begin();
				it != openList.end(); it = next(it)) 
			{
				Node n = *it;
				if (n.fCost < temp) 
				{
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!isValid(node.c));

		c = node.c;
		closedList[c.X * consoleSize.X + c.Y] = true;

		for (int newX = -1; newX <= 1; newX++) 
		{
			for (int newY = -1; newY <= 1; newY++) 
			{
				double gNew, hNew, fNew;
				if (isValid({ (SHORT)(c.X + newX), (SHORT)(c.Y + newY) }))
				{
					if (isDest({ (SHORT)(c.X + newX), (SHORT)(c.Y + newY) }, dest))
					{
						//Destination found - make path
						map[c.X * consoleSize.X + c.Y].parent.X = c.X;
						map[c.X * consoleSize.X + c.Y].parent.Y = c.Y;
						destFound = true;
						return makePath(map, dest);
					}
					else if (!closedList[c.X * consoleSize.X + c.Y])
					{
						gNew = node.gCost + 1.0;
						hNew = calcH({ (SHORT)(c.X + newX), (SHORT)(c.Y + newY) }, dest);
						fNew = gNew + hNew;
						// Check if this path is better than the one already present
						if (map[c.X * consoleSize.X + c.Y].fCost == FLT_MAX ||
							map[c.X * consoleSize.X + c.Y].fCost > fNew)
						{
							// Update the details of this neighbour node
							map[c.X * consoleSize.X + c.Y].fCost = fNew;
							map[c.X * consoleSize.X + c.Y].gCost = gNew;
							map[c.X * consoleSize.X + c.Y].hCost = hNew;
							map[c.X * consoleSize.X + c.Y].parent.X = c.X;
							map[c.X * consoleSize.X + c.Y].parent.Y = c.Y;
							openList.emplace_back(map[c.X * consoleSize.X + c.Y]);
						}
					}
				}
			}
		}
	}
	if (!destFound) 
		return empty;

}*/