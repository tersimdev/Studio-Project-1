#ifndef _TRIGGER_H
#define _TRIGGER_H
#include "Framework\console.h"
#include "map.h"

class Trigger
{
public:
	COORD m_cLocation; //position
	bool  m_bActive = false; //whether if activated
};

#endif