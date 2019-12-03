#include "Game.hpp"
#include "TextureManager.hpp"
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
		cout << "Click" << endl;
		if (wall != nullptr)
		{
			clickOnBlock(e.button.y / BLOCK_HEIGHT, e.button.x / BLOCK_WIDTH);	
		}
		break;
	default:
		break;
	}
}

void Game::update()
{
	//Logica do timer
	//Niveis
}

void Game::render()
{
	SDL_RenderClear(rendMng->getRenderer());
	
	rendMng->renderGame(&wall->getWall());
	
	SDL_RenderPresent(rendMng->getRenderer());
}

void Game::clean()
{
	rendMng->~RenderMng();
	SDL_Quit();
	cout << "Game closed" << endl;
}

void Game::clickOnBlock(int row, int col)
{
	wall->deleteBlocks(row, col);
}