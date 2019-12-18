/**
	Wall Class:
	Holds wall graphical and matrix dimensions
	Methods do delete blocks, move blocks vertically and horizontally
	Also holds bombs methods
*/

#pragma once

#include "Constants.hpp"
#include "SDL.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <vector>
#include <set>

#define WMX m_wall.wallMx

using namespace std;

struct wallstrct										// Matrix wrapper so I can return it easilly
{
	int wallMx[NROW][NCOL];
};

class Wall
{
public:
	Wall();

	wallstrct getWall() { return m_wall; };
	void printWall();									

	void initWall();									// Starts/resets the wall
	void clearWall();
	void setBlock(int row, int col, int type);			// Changes the block type
	int dfsDelete(int row, int col);					// Calls for DFS and returns score
	void pushWallLeft();								// Generates one random column and pushes wall left
	int explodeBomb(int row, int col, int bType);		// Explodes bomb and returns score or negative values for click bombs

private:
	wallstrct m_wall;
	void fixWall();										// Main wall verification - checks for "holes" and empty columns.
	void fixCol(int col);								// Column check and fix. Separate from fixWall() so it can be called
														// on a single column (eg. pushWLeft), saving useless checks
	bool colCheck(int col);								// Checks for holes in columns
	void blockFall(int col);							// Pushes block down when needed (holes found)
	void fillEmptyCol(int col);							// Pushes the wall right starting from col
	int DFS(int row, int col);							// Depth first search that starts from [r][c]. Finds groups and deletes them
};