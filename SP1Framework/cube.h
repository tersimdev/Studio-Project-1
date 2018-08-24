#ifndef _CUBE_H
#define _CUBE_H
#include "Framework\console.h"
#include <vector>
using std::vector;

enum STARTCOLOR
{
	WHITE	= 0,	//0 * 4,
	BLUE	= 4,	//1 * 4,
	GREEN	= 8,	//2 * 4,
	ORANGE	= 12,	//3 * 4,
	RED		= 16,	//4 * 4,
	YELLOW	= 20	//5 * 4
};

class Cube
{
public:
	Cube();

	void moveR(int dir);

	void moveU(int dir);

	void rotateY(int dir);

	void rotateX(int dir);

	vector<WORD> faces = vector<WORD>(24);

	vector<short> rotationPattern = vector<short>(4);

	static const WORD _white = 0xFF;
	static const WORD _blue = 0x99;
	static const WORD _green = 0xAA;
	static const WORD _orange = 0x55;
	static const WORD _red = 0xCC;
	static const WORD _yellow = 0x66;
};




#endif