#include "Game.hpp"

Game::Game()
{
	currScore = 0;
	gWall = nullptr;
	gTimer = nullptr;
	gRend = nullptr;
	isRunning = true;
}

Game::~Game()
{
}

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
			clickScore = gWall->deleteBlocks((e.button.y - W_Y0) / B_HEIGHT, (e.button.x - W_X0) / B_WIDTH);
			if (clickScore > 0)
			{
				currScore += pow(5, clickScore);
			}
			cout << currScore << endl;
		}
		break;
	default:
		break;
	}
}

// Updates game logic
void Game::update()
{
	// Push the wall each interval
	if (gTimer->getTicks() > (Uint32)3000)
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
}

// Updates game graphics
void Game::render()
{
	SDL_RenderClear(gRend->getRenderer());
	
	gRend->renderGame(&gWall->getWall());

	gRend->renderTimer(gTimer->getTicks());
	
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