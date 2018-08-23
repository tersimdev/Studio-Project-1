#include "cube.h"

Cube::Cube()
{
	for (int j = 0; j < 4; j++)
	{
		this->faces[WHITE].colors[j] = _white; //white
		this->faces[BLUE].colors[j] = _blue; //blue
		this->faces[GREEN].colors[j] = _green; //green
		this->faces[ORANGE].colors[j] = _orange; //purple
		this->faces[RED].colors[j] = _red; //red
		this->faces[YELLOW].colors[j] = _yellow; //yellow
	}
}

void Cube::moveR(int dir)
{
	WORD temp[4];
	switch (dir)
	{
	case 1:
		for (int i = 0; i < 4; i++)
		{
			if (i % 2)
			{
				temp[i - 1] = this->faces[RED].colors[i];
				this->faces[RED].colors[i] = this->faces[YELLOW].colors[i];
				this->faces[YELLOW].colors[i] = this->faces[ORANGE].colors[i];
				this->faces[ORANGE].colors[i] = this->faces[WHITE].colors[i];
				this->faces[WHITE].colors[i] = temp[i - 1];
			}
		}
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[BLUE].colors[j];
		}
		this->faces[BLUE].colors[0] = temp[2];
		this->faces[BLUE].colors[1] = temp[0];
		this->faces[BLUE].colors[2] = temp[3];
		this->faces[BLUE].colors[3] = temp[1];
		break;
	case -1:
		for (int i = 0; i < 4; i++)
		{
			if (i % 2)
			{
				temp[i - 1] = this->faces[WHITE].colors[i];
				this->faces[WHITE].colors[i] = this->faces[ORANGE].colors[i];
				this->faces[ORANGE].colors[i] = this->faces[YELLOW].colors[i];
				this->faces[YELLOW].colors[i] = this->faces[RED].colors[i];
				this->faces[RED].colors[i] = temp[i - 1];
			}
		}
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[BLUE].colors[j];
		}
		this->faces[BLUE].colors[0] = temp[1];
		this->faces[BLUE].colors[1] = temp[3];
		this->faces[BLUE].colors[2] = temp[0];
		this->faces[BLUE].colors[3] = temp[2];
		break;
	}
}

void Cube::moveU(int dir)
{
	WORD temp[4];
	switch (dir)
	{
	case -1:
		temp[0] = this->faces[RED].colors[0];
		temp[1] = this->faces[RED].colors[1];
		this->faces[RED].colors[0] = this->faces[BLUE].colors[2];
		this->faces[RED].colors[1] = this->faces[BLUE].colors[0];
		this->faces[BLUE].colors[2] = this->faces[ORANGE].colors[3];
		this->faces[BLUE].colors[0] = this->faces[ORANGE].colors[2];
		this->faces[ORANGE].colors[3] = this->faces[GREEN].colors[1];
		this->faces[ORANGE].colors[2] = this->faces[GREEN].colors[3];
		this->faces[GREEN].colors[1] = temp[0];
		this->faces[GREEN].colors[3] = temp[1];
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[WHITE].colors[j];
		}
		this->faces[WHITE].colors[0] = temp[2];
		this->faces[WHITE].colors[1] = temp[0];
		this->faces[WHITE].colors[2] = temp[3];
		this->faces[WHITE].colors[3] = temp[1];
		break;
	case 1:
		temp[0] = this->faces[GREEN].colors[1];
		temp[1] = this->faces[GREEN].colors[3];
		this->faces[GREEN].colors[1] = this->faces[ORANGE].colors[3];
		this->faces[GREEN].colors[3] = this->faces[ORANGE].colors[2];
		this->faces[ORANGE].colors[2] = this->faces[BLUE].colors[0];
		this->faces[ORANGE].colors[3] = this->faces[BLUE].colors[2];
		this->faces[BLUE].colors[0] = this->faces[RED].colors[1];
		this->faces[BLUE].colors[2] = this->faces[RED].colors[0];
		this->faces[RED].colors[0] = temp[0];
		this->faces[RED].colors[1] = temp[1];
		for (int j = 0; j < 4; j++)
		{
			temp[j] = this->faces[WHITE].colors[j];
		}
		this->faces[WHITE].colors[0] = temp[1];
		this->faces[WHITE].colors[1] = temp[3];
		this->faces[WHITE].colors[2] = temp[0];
		this->faces[WHITE].colors[3] = temp[2];
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
			temp[i] = this->faces[WHITE].colors[i];
			this->faces[WHITE].colors[i] = this->faces[ORANGE].colors[i];
			this->faces[ORANGE].colors[i] = this->faces[YELLOW].colors[i];
			this->faces[YELLOW].colors[i] = this->faces[RED].colors[i];
			this->faces[RED].colors[i] = temp[i];
		}
		for (int i = 0; i < 4; i++)
			temp[i] = this->faces[GREEN].colors[i];
		this->faces[GREEN].colors[0] = temp[2];
		this->faces[GREEN].colors[1] = temp[0];
		this->faces[GREEN].colors[2] = temp[3];
		this->faces[GREEN].colors[3] = temp[1];
		for (int i = 0; i < 4; i++)
			temp[i] = this->faces[BLUE].colors[i];
		this->faces[BLUE].colors[0] = temp[1];
		this->faces[BLUE].colors[1] = temp[3];
		this->faces[BLUE].colors[2] = temp[0];
		this->faces[BLUE].colors[3] = temp[2];
		break;
	case 1:
		for (int i = 0; i < 4; i++)
		{
			temp[i] = this->faces[RED].colors[i];
			this->faces[RED].colors[i] = this->faces[YELLOW].colors[i];
			this->faces[YELLOW].colors[i] = this->faces[ORANGE].colors[i];
			this->faces[ORANGE].colors[i] = this->faces[WHITE].colors[i];
			this->faces[WHITE].colors[i] = temp[i];
		}
		for (int i = 0; i < 4; i++)
			temp[i] = this->faces[GREEN].colors[i];
		this->faces[GREEN].colors[0] = temp[1];
		this->faces[GREEN].colors[1] = temp[3];
		this->faces[GREEN].colors[2] = temp[0];
		this->faces[GREEN].colors[3] = temp[2];
		for (int i = 0; i < 4; i++)
			temp[i] = this->faces[BLUE].colors[i];
		this->faces[BLUE].colors[0] = temp[2];
		this->faces[BLUE].colors[1] = temp[0];
		this->faces[BLUE].colors[2] = temp[3];
		this->faces[BLUE].colors[3] = temp[1];
		break;
	}
}

void Cube::rotateX(int dir)
{
	WORD temp[4];
	switch (dir)
	{
	case -1:
		//rotate faces
		for (int i = 0; i < 4; i++)
			temp[i] = this->faces[WHITE].colors[i];
		this->faces[WHITE].colors[0] = temp[1];
		this->faces[WHITE].colors[1] = temp[3];
		this->faces[WHITE].colors[2] = temp[0];
		this->faces[WHITE].colors[3] = temp[2];
		for (int i = 0; i < 4; i++)
			temp[i] = this->faces[YELLOW].colors[i];
		this->faces[YELLOW].colors[0] = temp[2];
		this->faces[YELLOW].colors[1] = temp[0];
		this->faces[YELLOW].colors[2] = temp[3];
		this->faces[YELLOW].colors[3] = temp[1];

		for (int i = 0; i < 4; i++)
			temp[i] = this->faces[RED].colors[i];
		this->faces[RED].colors[0] = this->faces[GREEN].colors[1];
		this->faces[RED].colors[1] = this->faces[GREEN].colors[3];
		this->faces[RED].colors[2] = this->faces[GREEN].colors[0];
		this->faces[RED].colors[3] = this->faces[GREEN].colors[2];
		this->faces[GREEN].colors[0] = this->faces[ORANGE].colors[1];
		this->faces[GREEN].colors[1] = this->faces[ORANGE].colors[3];
		this->faces[GREEN].colors[2] = this->faces[ORANGE].colors[0];
		this->faces[GREEN].colors[3] = this->faces[ORANGE].colors[2];
		this->faces[ORANGE].colors[0] = this->faces[BLUE].colors[1];
		this->faces[ORANGE].colors[1] = this->faces[BLUE].colors[3];
		this->faces[ORANGE].colors[2] = this->faces[BLUE].colors[0];
		this->faces[ORANGE].colors[3] = this->faces[BLUE].colors[2];
		this->faces[BLUE].colors[0] = temp[1];
		this->faces[BLUE].colors[1] = temp[3];
		this->faces[BLUE].colors[2] = temp[0];
		this->faces[BLUE].colors[3] = temp[2];
		break;
	case 1:
		//rotate faces
		for (int i = 0; i < 4; i++)
			temp[i] = this->faces[WHITE].colors[i];
		this->faces[WHITE].colors[0] = temp[2];
		this->faces[WHITE].colors[1] = temp[0];
		this->faces[WHITE].colors[2] = temp[3];
		this->faces[WHITE].colors[3] = temp[1];
		for (int i = 0; i < 4; i++)
			temp[i] = this->faces[YELLOW].colors[i];
		this->faces[YELLOW].colors[0] = temp[1];
		this->faces[YELLOW].colors[1] = temp[3];
		this->faces[YELLOW].colors[2] = temp[0];
		this->faces[YELLOW].colors[3] = temp[2];

		for (int i = 0; i < 4; i++)
			temp[i] = this->faces[ORANGE].colors[i];
		this->faces[ORANGE].colors[0] = this->faces[GREEN].colors[2];
		this->faces[ORANGE].colors[1] = this->faces[GREEN].colors[0];
		this->faces[ORANGE].colors[2] = this->faces[GREEN].colors[3];
		this->faces[ORANGE].colors[3] = this->faces[GREEN].colors[1];
		this->faces[GREEN].colors[0] = this->faces[RED].colors[2];
		this->faces[GREEN].colors[1] = this->faces[RED].colors[0];
		this->faces[GREEN].colors[2] = this->faces[RED].colors[3];
		this->faces[GREEN].colors[3] = this->faces[RED].colors[1];
		this->faces[RED].colors[0] = this->faces[BLUE].colors[2];
		this->faces[RED].colors[1] = this->faces[BLUE].colors[0];
		this->faces[RED].colors[2] = this->faces[BLUE].colors[3];
		this->faces[RED].colors[3] = this->faces[BLUE].colors[1];
		this->faces[BLUE].colors[0] = temp[2];
		this->faces[BLUE].colors[1] = temp[0];
		this->faces[BLUE].colors[2] = temp[3];
		this->faces[BLUE].colors[3] = temp[1];
		break;
	}

}