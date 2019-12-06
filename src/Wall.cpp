#include "Wall.hpp"

// Adjacent directions to look for - Up, down, left, right
vector<pair<int, int>> dirs = { { -1, 0},{1, 0},{ 0, -1},{0, 1} };

Wall::Wall()
{
	initWall();
	fixWall();
}

Wall::~Wall()
{
}

// Inits wall matrix with random values from 0 (empty) to 6, with 5 types of blocks
void Wall::initWall()
{
	srand(time(NULL));

	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			WMX[i][j] = rand() % 6;
		}
	}
}

// Prints the wall matrix to console in matrix form
void Wall::printWall()
{
	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			cout << WMX[i][j] << " \n"[j == NCOL - 1];
		}
	}
}

// Checks for spaces between rows and empty columns, and if found, calls the fixing fuctions
void Wall::fixWall()
{
	for (int j = 0; j < NCOL; j++)
	{
		while (!colCheck(j))								// While spaces are found between blocks, the column will be fixed
		{
			blockFall(j);								// Moves
		}

		if (j != 0 && WMX[NROW - 1][j] == 0)		// If a column is empty, push the left columns to fix it
		{
			cout << j << " col is empty" << endl;
			moveCols(j);
		}
	}
}

// Moves the columns when an empty is found
void Wall::moveCols(int col)
{
	for (int j = col; j > 0; j--)							// Starting from the empty column, all the left columns will be moved
	{
		for (int i = 0; i < NROW; i++)						/// Every block will be swapped with the adjacent left block
		{
			WMX[i][j] = WMX[i][j - 1];
			WMX[i][j - 1] = 0;
		}
	}
}

// Checks if a column needs fixing (has "holes")
bool Wall::colCheck(int col)
{
	bool isOk = true;						// Is the column ok? (No inbetween spaces)
	bool foundN = false;					// Has a number (block) been found

	for (int i = 0; i < NROW; i++)			// Check top to bottom
	{
		if (WMX[i][col] != 0)		// Found a block
		{
			foundN = true;
		}
		else								// Found a space
		{
			if (foundN)						// If a space has been found after a number, column needs a fix
			{
				isOk = false;
				return isOk;
			}
		}
	}

	return isOk;
}

// Makes the blocks above the column holes "fall", filling those spaces
void Wall::blockFall(int col)
{
	for (int i = NROW - 1; i > 0; i--)								// Checks line bottom to top
	{
		if (WMX[i][col] == 0)								// Checks for spaces (0's)
		{
			int x = i;												// Starts fixing here
			while (x > 0)											// Cycles while it hasn't reach the top
			{
				if (WMX[x - 1][col] == 0)					// If the current space is empty, continues checking
				{
					x--;
				}
				else												// If the current space is a block, it swaps with the bottom one and breaks the process
				{
					WMX[x][col] = WMX[x - 1][col];
					WMX[x - 1][col] = 0;
					break;
				}
			}
		}
	}
}

// Checks if the block clicked is not empty, starts a DFS and fixes the wall if needed
void Wall::deleteBlocks(int row, int col)
{
	if (wall.wallMx[row][col] != 0)
	{
		set<pair<int, int>> deleteSet = {};
		if (DFS(row, col, deleteSet))
		{
			fixWall();
		}
	}
}

// Depth First search
// Founds number groups (adjacent numbers with the same value) and sets them to 0
bool Wall::DFS(int row, int col, set<pair<int, int>> dSet)
{
	int bv = WMX[row][col];						// Clicked blocked value
	stack<pair<int, int>> search = {};			// DFS search stack
	bool foundEqu = false;						// Has an equal number been found?
	bool fixWall = false;						// Does the wall need a fix (yes if a block got deleted)

	pair<int, int> start(row, col);				// Clicked coordinate and tree start
	search.push(start);							// Push the start to the DFS search stack

	while (search.size() > 0)					// While it has elements to do an adjancency search
	{
		foundEqu = false;						// Restarts the found equal value

		pair<int, int> currCoord(search.top().first, search.top().second);		// The current coordinate is the top of the search stack

		for (auto dir : dirs)													// For each direction (Up, down, left, right)
		{
			int searchedRow = currCoord.first + dir.first;						// Row and column currently being searched
			int searchedCol = currCoord.second + dir.second;

			if (searchedRow > NROW - 1 || searchedRow < 0 || searchedCol > NCOL - 1 || searchedCol < 0)	// If any of these values are out of bounds, skip this check
			{
				continue;
			}

			pair <int, int> searchedCoord(searchedRow, searchedCol);	// This coord is validated and saved to a pair

			if (!dSet.count(searchedCoord) && WMX[searchedRow][searchedCol] == bv)	// If this coord hasnt been searched yet (doesnt exist in the deleted set) and is equal to value, proceed
			{
				foundEqu = true;						// An equal as been found (the cycle will be repeated)
				fixWall = true;							// The wall will need a fix
				search.push(searchedCoord);				// One more block to search													
				dSet.emplace(searchedCoord);			// One more block to delete
			}
		}

		if (!foundEqu)		// If there are no adj. equals, end of branch, pop from search stack.
		{
			search.pop();
		}
	}

	for (auto x : dSet)		// For every element in the deleteSet, set the matrix value to 0
	{
		WMX[x.first][x.second] = 0;
	}

	return fixWall;
}