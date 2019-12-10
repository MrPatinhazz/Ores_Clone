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

// Wall start and end x & y coordinate
#define W_X0 (SCREEN_WIDTH - W_WIDTH)
#define W_X1 (W_WIDTH + W_X0)
#define W_Y0 ((SCREEN_HEIGHT - W_HEIGHT)/2)
#define W_Y1 (W_HEIGHT + W_Y0)

// Score text X & Y
#define SC_TX_X 0
#define SC_TX_Y 0

// Timer text
#define TM_TX_X (SCREEN_WIDTH/2)
#define TM_TX_Y 0
// Push wall interval in ms
#define PSH_INTV 3000

// Current stage text
#define STG_TX_X (SCREEN_WIDTH - (SCREEN_WIDTH/5))
#define STG_TX_Y 0
// Stage points
#define STG_PTS 200

// Next stage button
#define NSB_BT_X (W_X1 - (B_WIDTH*1.5))
#define NSB_BT_Y (W_Y1 + (B_HEIGHT/2))

class RenderMng
{
public:
	RenderMng(const char* title, int xpos, int ypos);
	~RenderMng();

	SDL_Renderer* getRenderer() { return renderer; };
	SDL_Window* getWindow() { return window; };

	void renderGame(wallstrct* wall);
	void renderTimer(Uint32 currTime);
	void renderScore(int score);
	void renderStage(int stage);

private:
	SDL_Rect srcRect, dstRect;
	SDL_Window* window;
	SDL_Renderer* renderer;

	WTexture blockTex[BTYPES], timerTex, scoreTex, stageTex, nsBtTex;
	TTF_Font* timerFont;

	void initTextures();

	void render_wall(wallstrct* wall);
	void render_block(int bType, int row, int col);
	void render_grid();
};