/**
	Wall Class:
	Defines wall matrix dimensions, block dimension and wall position 
	Methods do delete blocks, move blocks vertically and horizontally
**/

#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL.h"
#include <stack>
#include <vector>
#include <utility>
#include <set>
#include <iterator>

#define NROW 20
#define NCOL 20
#define WALL_WIDTH 500
#define WALL_HEIGHT 500
#define WALL_X 500
#define WALL_Y 100
#define BLOCK_WIDTH (WALL_WIDTH / NCOL)
#define BLOCK_HEIGHT (WALL_HEIGHT / NROW)
#define WMX wall.wallMx

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
	void blockFall(int col);
	bool colCheck(int col);
	void fixWall();
	void moveCols(int col);
	bool DFS(int row, int col, set<pair<int, int>> dSet);
};