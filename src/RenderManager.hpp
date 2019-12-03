#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "TextureManager.hpp"
#include "Wall.hpp"

using namespace std;

class RenderMng
{
public:
	RenderMng(const char* title, int xpos, int ypos, int w, int h, bool fullscreen);
	~RenderMng();

	SDL_Renderer* getRenderer() { return renderer; };
	SDL_Window* getWindow() { return window; };

	void renderGame(wallstrct* wall);

private:
	SDL_Rect srcRect, dstRect;
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* block_tex[5];
	void initTextures();

	void render_wall(wallstrct* wall);
	void render_block(int bType, int row, int col);
	void render_grid();
};