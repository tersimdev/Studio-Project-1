#include "cube.h"

Cube::Cube()
{
	for (int j = 0; j < 4; j++)
	{
		this->faces[WHITE + j]		= _white;	//white
		this->faces[BLUE + j]		= _blue;	//blue
		this->faces[GREEN + j]		= _green;	//green
		this->faces[ORANGE + j]		= _orange;	//purple
		this->faces[RED + j]		= _red;		//red
		this->faces[YELLOW + j]		= _yellow;	//yellow
	}
}

void Cube::moveR(int dir)
{
	WORD temp[4];
	switch (dir)
	{
	case 1:
		//turning
		for (int i = 0; i < 4; i++)
		{
			if (i % 2)
			{
				temp[i - 1] = this->faces[RED + i];
				this->faces[RED + i] = this->faces[YELLOW + i];
				this->faces[YELLOW + i] = this->faces[ORANGE + i];
				this->faces[ORANGE + i] = this->faces[WHITE + i];
				this->faces[WHITE + i] = temp[i - 1];
			}
		}

		//rotation
		this->rotationPattern = { 2, 0, 3, 1 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[BLUE + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[BLUE + k] = temp[rotationPattern[k]];
		}
		break;
	case -1:
		//turning
		for (int i = 0; i < 4; i++)
		{
			if (i % 2)
			{
				temp[i - 1] = this->faces[WHITE + i];
				this->faces[WHITE + i] = this->faces[ORANGE + i];
				this->faces[ORANGE + i] = this->faces[YELLOW + i];
				this->faces[YELLOW + i] = this->faces[RED + i];
				this->faces[RED + i] = temp[i - 1];
			}
		}

		//rotation
		this->rotationPattern = { 1, 3, 0, 2 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[BLUE + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[BLUE + k] = temp[rotationPattern[k]];
		}
		break;
	}
}

void Cube::moveU(int dir)
{
	WORD temp[4];
	switch (dir)
	{
	case -1:
		//turning
		this->rotationPattern = { 2, 0, 3, 1 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[WHITE + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[WHITE + k] = temp[rotationPattern[k]];
		}
		//rotating
		temp[0] = this->faces[RED];
		temp[1] = this->faces[RED + 1];
		this->faces[RED] = this->faces[BLUE + 2];
		this->faces[RED + 1] = this->faces[BLUE];
		this->faces[BLUE + 2] = this->faces[ORANGE + 3];
		this->faces[BLUE] = this->faces[ORANGE + 2];
		this->faces[ORANGE + 3] = this->faces[GREEN + 1];
		this->faces[ORANGE + 2] = this->faces[GREEN + 3];
		this->faces[GREEN + 1] = temp[0];
		this->faces[GREEN + 3] = temp[1];
		break;
	case 1:
		//turning
		this->rotationPattern = { 1, 3, 0, 2 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[WHITE + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[WHITE + k] = temp[rotationPattern[k]];
		}

		//rotating
		temp[0] = this->faces[GREEN + 1];
		temp[1] = this->faces[GREEN + 3];
		this->faces[GREEN + 1] = this->faces[ORANGE + 3];
		this->faces[GREEN + 3] = this->faces[ORANGE + 2];
		this->faces[ORANGE + 2] = this->faces[BLUE];
		this->faces[ORANGE + 3] = this->faces[BLUE + 2];
		this->faces[BLUE] = this->faces[RED + 1];
		this->faces[BLUE + 2] = this->faces[RED];
		this->faces[RED] = temp[0];
		this->faces[RED + 1] = temp[1];
		break;
	}
}

void Cube::rotateY(int dir)
{
	WORD temp[4];
	switch (dir)
	{
	case -1:
		for (int i = 0; i < 4; i++)
		{
			temp[i] = this->faces[WHITE + i];
			this->faces[WHITE + i] = this->faces[ORANGE + i];
			this->faces[ORANGE + i] = this->faces[YELLOW + i];
			this->faces[YELLOW + i] = this->faces[RED + i];
			this->faces[RED + i] = temp[i];
		}

		this->rotationPattern = { 2, 0, 3, 1 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[GREEN + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[GREEN + k] = temp[rotationPattern[k]];
		}
		
		this->rotationPattern = { 1, 3, 0, 2 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[BLUE + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[BLUE + k] = temp[rotationPattern[k]];
		}
		break;
	case 1:
		for (int i = 0; i < 4; i++)
		{
			temp[i] = this->faces[RED + i];
			this->faces[RED + i] = this->faces[YELLOW + i];
			this->faces[YELLOW + i] = this->faces[ORANGE + i];
			this->faces[ORANGE + i] = this->faces[WHITE + i];
			this->faces[WHITE + i] = temp[i];
		}
		this->rotationPattern = { 1, 3, 0, 2 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[GREEN + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[GREEN + k] = temp[rotationPattern[k]];
		}

		this->rotationPattern = { 2, 0, 3, 1 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[BLUE + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[BLUE + k] = temp[rotationPattern[k]];
		}
		break;
	}
}

void Cube::rotateX(int dir)
{
	WORD temp[4];
	switch (dir)
	{
	case -1:
		this->rotationPattern = { 1, 3, 0, 2 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[WHITE + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[WHITE + k] = temp[rotationPattern[k]];
		}
		
		this->rotationPattern = { 2, 0, 3, 1 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[YELLOW + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[YELLOW + k] = temp[rotationPattern[k]];
		}

		this->rotationPattern = { 1, 3, 0, 2 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[RED + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[RED + k] = this->faces[GREEN + rotationPattern[k]];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[GREEN + k] = this->faces[ORANGE + rotationPattern[k]];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[ORANGE + k] = this->faces[BLUE + rotationPattern[k]];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[BLUE + k] = temp[rotationPattern[k]];
		}
		break;
	case 1:
		this->rotationPattern = { 2, 0, 3, 1 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[WHITE + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[WHITE + k] = temp[rotationPattern[k]];
		}
		
		this->rotationPattern = { 1, 3, 0, 2 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[YELLOW + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[YELLOW + k] = temp[rotationPattern[k]];
		}

		this->rotationPattern = { 2, 0, 3, 1 };
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[ORANGE + j];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[ORANGE + k] = this->faces[GREEN + rotationPattern[k]];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[GREEN + k] = this->faces[RED + rotationPattern[k]];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[RED + k] = this->faces[BLUE + rotationPattern[k]];
		}
		for (int k = 0; k < 4; k++)
		{
			this->faces[BLUE + k] = temp[rotationPattern[k]];
		}
		break;
	}

}