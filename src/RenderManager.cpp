#include "RenderManager.hpp"

RenderMng::RenderMng(const char* title, int xpos, int ypos, int w, int h, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	window = SDL_CreateWindow(title, xpos, ypos, w, h, flags);
	if (window)
	{
		cout << "Window created" << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		cout << "Renderer created" << endl;
	}

	initTextures();
}

RenderMng::~RenderMng()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void RenderMng::renderGame(wallstrct* wall)
{
	render_grid();
	render_wall(wall);
}

void RenderMng::initTextures()
{
	block_tex[0] = TextureManager::LoadTexture("assets/ore_1.png", renderer);
	block_tex[1] = TextureManager::LoadTexture("assets/ore_2.png", renderer);
	block_tex[2] = TextureManager::LoadTexture("assets/ore_3.png", renderer);
	block_tex[3] = TextureManager::LoadTexture("assets/ore_4.png", renderer);
	block_tex[4] = TextureManager::LoadTexture("assets/ore_5.png", renderer);
}

void RenderMng::render_wall(wallstrct* wall)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int i = 0; i < NROW; i++)
	{
		for (int j = 0; j < NCOL; j++)
		{
			int bType = wall->wallMx[i][j];
			if (bType != 0)
			{
				render_block(bType, i, j);
			}

		}
	}
}

void RenderMng::render_block(int blockType, int row, int col)
{
	dstRect.h = BLOCK_HEIGHT;
	dstRect.w = BLOCK_WIDTH;

	dstRect.x = col * BLOCK_WIDTH;
	dstRect.y = row * BLOCK_HEIGHT;

	SDL_RenderCopy(renderer, block_tex[blockType - 1], NULL, &dstRect);
}

void RenderMng::render_grid()
{
	SDL_SetRenderDrawColor(renderer, 155, 155, 155, 255);
	for (int i = 0; i < NCOL + 1; i++)
	{
		SDL_RenderDrawLine(renderer, i * BLOCK_WIDTH, 0, i * BLOCK_WIDTH, WALL_HEIGHT);

		for (int j = 0; j < NROW + 1; j++)
		{
			SDL_RenderDrawLine(renderer, 0, i * BLOCK_HEIGHT, WALL_WIDTH, i * BLOCK_HEIGHT);

		}
	}
}