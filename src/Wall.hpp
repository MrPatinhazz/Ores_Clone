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

#define BTYPES 5
#define NROW 10
#define NCOL 17
#define INITCOL (NCOL/2)
#define B_WIDTH 32
#define B_HEIGHT 32
#define W_WIDTH (B_WIDTH * NCOL)
#define W_HEIGHT (B_HEIGHT * NROW)
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
	void initWall();
	int deleteBlocks(int row, int col);
	void pushWallLeft();

private:
	wallstrct wall;
	void printWall();
	void blockFall(int col);
	bool colCheck(int col);
	void fixWall();
	void fillEmptyCol(int col);
	int DFS(int row, int col, set<pair<int, int>> dSet);
};