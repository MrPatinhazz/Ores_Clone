#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL.h"

#define NROW 50
#define NCOL 50
#define WALL_WIDTH 1000
#define WALL_HEIGHT 800
#define BLOCK_WIDTH (WALL_WIDTH / NCOL)
#define BLOCK_HEIGHT (WALL_HEIGHT / NROW)

using namespace std;

struct wallstrct
{
	int wallMx[NROW][NCOL];
};

class Wall
{
public:
	Wall();
	~Wall();
	wallstrct getWall() { return wall; };
	void deleteBlocks(int row, int col);

private:
	wallstrct wall;

	void initWall();
	void printWall();
	void fixCol(int col);
	bool colCheck(int col);
	void blockFall();
};