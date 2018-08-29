#ifndef _PONG_H
#define _PONG_H
#include "game.h"
#include "trigger.h"

class Pong : public Organism
{
public:
	Pong(char symb, WORD col, COORD location, COORD direction);
	bool collisionCheckSlider(COORD puckloc, COORD slideloc);
};

class Slider : public Organism
{
public:
	Slider(WORD col, COORD location);
};


#endif 