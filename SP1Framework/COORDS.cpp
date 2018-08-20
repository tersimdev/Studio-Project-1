#include "COORDS.h"

COORDS COORDS::operator+ (COORDS &obj)
{
	COORDS res;
	res.X = this->X + obj.X;
	res.Y = this->Y + obj.Y;
	return res;
}

void COORDS::operator+= (COORDS &obj)
{
	this->X += obj.X;
	this->Y += obj.Y;
}

bool COORDS::operator== (COORDS &obj)
{
	if (this->X == obj.X && this->Y == obj.Y)
		return true;
	else return false;
}

bool COORDS::operator!= (COORDS &obj)
{
	if (this->X == obj.X && this->Y == obj.Y)
		return false;
	else return true;
}