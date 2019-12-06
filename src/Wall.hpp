/**
	Wall Class:
	Holds wall graphical and matrix dimensions
	Methods do delete blocks, move blocks vertically and horizontally
*/

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

#define BTYPES 2
#define NROW 50
#define NCOL 50
#define WALL_WIDTH 1000
#define WALL_HEIGHT 500
#define WALL_X 0
#define WALL_Y 0
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