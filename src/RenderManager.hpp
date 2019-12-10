#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "WTexture.hpp"
#include "Wall.hpp"
#include <string>

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FULLSCREEN false

#define W_X0 (SCREEN_WIDTH - W_WIDTH)
#define W_X1 (W_WIDTH + W_X0)
#define W_Y0 ((SCREEN_HEIGHT - W_HEIGHT)/2)
#define W_Y1 (W_HEIGHT + W_Y0)

class RenderMng
{
public:
	RenderMng(const char* title, int xpos, int ypos);
	~RenderMng();

	SDL_Renderer* getRenderer() { return renderer; };
	SDL_Window* getWindow() { return window; };

	void renderGame(wallstrct* wall);
	void renderTimer(Uint32 currTime);

private:
	SDL_Rect srcRect, dstRect;
	SDL_Window* window;
	SDL_Renderer* renderer;

	WTexture blockTex[BTYPES];
	WTexture timerTex;
	TTF_Font* timerFont;

	void initTextures();

	void render_wall(wallstrct* wall);
	void render_block(int bType, int row, int col);
	void render_grid();
};