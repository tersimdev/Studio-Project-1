#ifndef _COORDS_H
#define _COORDS_H
#include "Framework\console.h"

class COORDS : public COORD
{
public:
	
	COORDS operator+ (COORDS &obj);

	void operator+= (COORDS &obj);
	
	bool operator== (COORDS &obj);
	
	bool operator!= (COORDS &obj);
};

#endif