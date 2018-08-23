#ifndef _CUBE_H
#define _CUBE_H
#include "Framework\console.h"
#include <vector>
using std::vector;

enum STARTCOLOR
{
	WHITE = 0,
	BLUE,
	GREEN,
	ORANGE,
	RED,
	YELLOW
};

struct Face
{
	vector<WORD> colors = vector<WORD>(4);
};


class Cube
{
public:
	Cube();

	void moveR(int dir);

	void moveU(int dir);

	void rotateY(int dir);

	void rotateX(int dir);

	struct Face faces[6]; //create 6 faces

	static const WORD _white = 0xFF;
	static const WORD _blue = 0x99;
	static const WORD _green = 0xAA;
	static const WORD _orange = 0x55;
	static const WORD _red = 0xCC;
	static const WORD _yellow = 0x66;
};




#endif