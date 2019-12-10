#include "Game.hpp"

Game::Game()
{
	currScore = 0;
	currStage = 1;
	gWall = nullptr;
	gTimer = nullptr;
	gRend = nullptr;
	isRunning = true;
}

Game::~Game()
{
}

// Inits SDL, the wall, the render manager and the timer
void Game::init(const char* title, int xpos, int ypos)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Init sucessfull" << endl;
		
		gWall = new Wall();

		gRend = new RenderMng(title, xpos, ypos);
	
		gTimer = new Timer();
		gTimer->start();

		isRunning = true;
	}
}

// Handles mouse clicks
void Game::handleEvent()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (gWall != nullptr)
		{
			int clickScore = 0;
			// Block clicks and added score if applied
			clickScore = gWall->deleteBlocks((e.button.y - W_Y0) / B_HEIGHT, (e.button.x - W_X0) / B_WIDTH);
			if (clickScore > 0)
			{
				currScore += (clickScore*clickScore);
			}

			// Push wall button click
			if (clickedPushW(e.button.x, e.button.y))
			{
				gWall->pushWallLeft();
			}
		}
		break;
	default:
		break;
	}
}

// Checks if the click coordinates are inside the push wall button
bool Game::clickedPushW(Sint32 mouseX, Sint32 mouseY)
{
	if (mouseX >= NSB_BT_X && mouseX <= NSB_BT_X + 32)
	{
		if (mouseY >= NSB_BT_Y && mouseY <= NSB_BT_Y + 32)
		{
			return true;
		}
		return false;
	}
	return false;
}

// Updates game logic
void Game::update()
{
	// Push the wall each interval
	if (gTimer->getTicks() > (Uint32)PSH_INTV)
	{
		gTimer->stop();
		gWall->pushWallLeft();
		gTimer->start();
	}
	// Loosing condition
	if (gWall->getWall().wallMx[NROW-1][0] != 0)
	{
		cout << "You lost!" << endl;
		gTimer->stop();
		isRunning = false;
	}
	// Different stage every x score
	if (currScore > (STG_PTS * currStage))
	{
		currStage++;
		gWall->initWall();
	}
}

// Updates game graphics
void Game::render()
{
	SDL_RenderClear(gRend->getRenderer());
	
	// Renders wall and grid, timer, score, and curr. stage
	gRend->renderGame(&gWall->getWall());
	gRend->renderTimer(gTimer->getTicks());
	gRend->renderScore(currScore);
	gRend->renderStage(currStage);

	SDL_RenderPresent(gRend->getRenderer());
}

void Game::clean()
{
	gRend->~RenderMng();
	gWall->~Wall();
	gTimer->~Timer();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	cout << "Game closed" << endl;
}


