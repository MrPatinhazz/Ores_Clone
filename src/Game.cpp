#include "Game.hpp"

Game::Game()
{
	gWall = nullptr;
	gTimer = nullptr;
	gRend = nullptr;
	isRunning = true;
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int w, int h, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Init sucessfull" << endl;
		
		gWall = new Wall();

		gRend = new RenderMng(title, xpos, ypos, w, h, fullscreen);
	
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
			gWall->deleteBlocks((e.button.y - WALL_Y) / BLOCK_HEIGHT, (e.button.x - WALL_X) / BLOCK_WIDTH);
			gTimer->pause();
		}
		break;
	default:
		break;
	}
}

// Updates game logic
void Game::update()
{
	
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