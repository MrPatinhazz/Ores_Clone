#include "Game.hpp"
#include "Wall.hpp"
#include "RenderManager.hpp"

static Wall* wall = nullptr;
RenderMng* rendMng = nullptr;

Game::Game()
{
	wall = new Wall();
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int w, int h, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Init sucessfull" << endl;
		
		rendMng = new RenderMng(title, xpos, ypos, w, h, fullscreen);
	
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
		if (wall != nullptr)
		{
			wall->deleteBlocks((e.button.y - WALL_Y) / BLOCK_HEIGHT, (e.button.x - WALL_X) / BLOCK_WIDTH);
		}
		break;
	default:
		break;
	}
}

// Updates game logic
void Game::update()
{
	//Logica do timer
	//Niveis
}

// Updates game graphics
void Game::render()
{
	SDL_RenderClear(rendMng->getRenderer());
	
	rendMng->renderGame(&wall->getWall());
	
	SDL_RenderPresent(rendMng->getRenderer());
}

void Game::clean()
{
	rendMng->~RenderMng();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	cout << "Game closed" << endl;
}