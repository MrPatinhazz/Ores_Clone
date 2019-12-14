#pragma once

#include "WTexture.hpp"
#include "Wall.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

using namespace std;

constexpr unsigned int SCREEN_WIDTH = 800;
constexpr unsigned int SCREEN_HEIGHT = 600;
constexpr bool FULLSCREEN = false;

// Wall start and end x & y coordinate
constexpr unsigned int WALL_X1 = (SCREEN_WIDTH - W_WIDTH);
constexpr unsigned int WALL_X2 = (W_WIDTH + WALL_X1);
constexpr unsigned int WALL_Y1 = ((SCREEN_HEIGHT - W_HEIGHT) / 2);
constexpr unsigned int WALL_Y2 = (W_HEIGHT + WALL_Y1);

// Score text X & Y
constexpr unsigned int SCR_TXT_X = 0;
constexpr unsigned int SCR_TXT_Y = 0;

// Timer text
constexpr unsigned int TM_TXT_X = (SCREEN_WIDTH / 2);
constexpr unsigned int TM_TXT_Y = 0;

// Current stage text
constexpr unsigned int STG_TXT_X = (SCREEN_WIDTH - (SCREEN_WIDTH / 5));
constexpr unsigned int STG_TXT_Y = 0;

// Next stage button
constexpr unsigned int NSB_BT_X = (WALL_X2 - (B_WIDTH * 1.5));
constexpr unsigned int NSB_BT_Y = (WALL_Y2 + (B_HEIGHT / 2));

// Multi bomb info text 
constexpr unsigned int MBOMB_TXT_X = (SCREEN_WIDTH / 3);
constexpr unsigned int MBOMB_TXT_Y = 50;

// Aim bomb info text 
constexpr unsigned int ABOMB_TXT_X = (SCREEN_WIDTH / 3);
constexpr unsigned int ABOMB_TXT_Y = 50;

class RenderMng
{
public:
	RenderMng(const char* title, int xpos, int ypos);
	~RenderMng();

	SDL_Renderer* getRenderer() { return m_renderer; };
	SDL_Window* getWindow() { return m_window; };

	void renderGame(wallstrct* m_wall);
	void renderTimer(Uint32 currTime);
	void renderScore(int score);
	void renderStage(int stage);
	void renderMultiBomb();
	void renderAimBomb(int _clicks);

private:
	SDL_Rect m_src_rect, m_dst_rect;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	WTexture m_block_tex[BTYPES],
		m_bomb_tex[BTYPES],
		m_timer_tex,
		m_score_tex,
		m_stage_tex,
		m_nst_bttex,
		m_multiB_tex,
		m_aimB_tex;
	TTF_Font* m_timer_font;

	void initTextures();

	void renderWall(wallstrct* m_wall);
	void renderBlock(int bType, int row, int col);
	void renderGrid();
};