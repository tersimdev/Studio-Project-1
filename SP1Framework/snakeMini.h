#ifndef _SNAKEMINI_H
#define _SNAKEMINI_H

#include "Framework\timer.h"

#include <string>




struct SNAKELAD
{
	COORD m_cLocation;
	bool  m_bActive;
};



void Snakecollisiondetection();
void applelocation(bool spawnapple);

void movebodypart();

SNAKELAD createSnakeBody(int X, int Y);
void snakeminigame();
void SnakeRenderMap();
void SnakerenderCharacter();
void Snakerenderapple();
void applelocation(bool spawnapple);
void movebodypart();
void SnakemoveCharacter();
void SnakeGameplay();

#endif