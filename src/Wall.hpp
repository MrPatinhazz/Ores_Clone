/**
	Wall Class:
	Holds wall graphical and matrix dimensions
	Methods do delete blocks, move blocks vertically and horizontally
*/

#pragma once

#include "SDL.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <vector>
#include <set>

#define WMX m_wall.wallMx

constexpr unsigned int BTYPES = 5;						// Block types
constexpr unsigned int NROW = 10;						// Number of rows
constexpr unsigned int NCOL = 17;						// '' of columns
constexpr unsigned int INITCOL = (NCOL / 2);			// Starting column of a new wall (left to right)
constexpr unsigned int B_WIDTH = 32;					// Block width
constexpr unsigned int B_HEIGHT = 32;					// Block height
constexpr unsigned int W_WIDTH = (B_WIDTH * NCOL);		// Wall width
constexpr unsigned int W_HEIGHT = (B_HEIGHT * NROW);	// Wall height

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
	wallstrct getWall() { return m_wall; };
	void setBlock(int row, int col, int type);
	void initWall();
	int dfsDelete(int row, int col);
	void pushWallLeft();
	void printWall();
	int explodeBomb(int row, int col, int bType);

private:
	wallstrct m_wall;
	void blockFall(int col);
	bool colCheck(int col);
	void fixWall();
	void fillEmptyCol(int col);
	int DFS(int row, int col, set<pair<int, int>> dSet);
};