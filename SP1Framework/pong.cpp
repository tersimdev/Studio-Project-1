#include "pong.h"
#include "game.h"
#include <fstream>

Pong::Pong(char symb, WORD col, COORD location, COORD direction)
{
	this->symbol = symb;
	this->color = col;
	this->m_cLocation = location;
	this->direction = direction;
};

bool Pong::collisionCheckSlider(COORD puckLoc, COORD sliderLoc)
{
	if (puckLoc.X == sliderLoc.X)
	{
		if (puckLoc.Y == sliderLoc.Y || puckLoc.Y == (sliderLoc.Y + 5) || puckLoc.Y == (sliderLoc.Y + 4) || puckLoc.Y == (sliderLoc.Y + 3) || puckLoc.Y == (sliderLoc.Y + 2) || puckLoc.Y == (sliderLoc.Y + 1))
		{
			return true;
		}
		else return false;
	}
	else return false;
}


Slider::Slider(WORD col, COORD location)
{
	this->color = col;
	this->m_cLocation = location;
}