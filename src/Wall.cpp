#include "Wall.hpp"

Wall::Wall()
{
	initWall();
	blockFall();
	//printWall();
}

Wall::~Wall()
{
}

void Wall::initWall()
{
	srand(time(NULL));

	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			wall.wallMx[i][j] = rand() % 6;
		}
	}
}

void Wall::printWall()
{
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			cout << wall.wallMx[i][j] << " \n"[j == NCOL - 1];
		}
	}
}

void Wall::blockFall()
{
	for (int j = 0; j < NCOL; j++)
	{
		while(!colCheck(j))
		{
			fixCol(j);
		}
	}
}

bool Wall::colCheck(int col)
{
	bool isOk = true;
	bool foundN = false;
	
	for (int i = 0; i < NROW; i++)
	{
		if (wall.wallMx[i][col] != 0)
		{
			foundN = true;
		}
		else
		{
			if (foundN)
			{
				isOk = false;
			}
		}
	}
	
	return isOk;
}

void Wall::fixCol(int col)
{
	for (int i = NROW-1; i > 0; i--)
	{
		if (wall.wallMx[i][col] == 0)
		{
			int x = i;
			while(x > 0)
			{
				if (wall.wallMx[x - 1][col] == 0)
				{
					x--;
				}
				else
				{
					wall.wallMx[x][col] = wall.wallMx[x - 1][col];
					wall.wallMx[x - 1][col] = 0;
					break;
				}
			}
		}
	}
}

void Wall::deleteBlocks(int row, int col)
{
	wall.wallMx[row][col] = 0;
	cout << "Tried to delete block in L " << row << " C " << col << endl;
	blockFall();
}

