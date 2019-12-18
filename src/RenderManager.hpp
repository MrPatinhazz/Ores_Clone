#pragma once

#include "WTexture.hpp"
#include "Wall.hpp"

using namespace std;

class RenderMng
{
public:
	RenderMng(const char* title, int xpos, int ypos);
	~RenderMng();

	SDL_Renderer* getRenderer() { return m_renderer; };
	SDL_Window* getWindow() { return m_window; };

	void renderBg();										// Background image
	void renderMenu();										// Initial menu
	void renderPauseScreen();								// Pause screen
	void renderGame(wallstrct* m_wall);						// Wall and grid
	void renderHUD(Uint32 currTime, int score, int stage);  // Score, timer and stage
	void renderMultiBomb();									// Multi bomb text
	void renderAimBomb(int _clicks);						// Aim bomb text

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	WTexture m_block_tex[BTYPES],
		m_bomb_tex[BTYPES],
		m_backg_tex,
		m_timer_tex,
		m_score_tex,
		m_stage_tex,
		m_nst_bttex,
		m_start_bt,
		m_quit_bt,
		m_paused_tex,
		m_multiB_tex,
		m_aimB_tex;

	TTF_Font *m_game_font, *m_paused_font;
	SDL_Rect m_timer_rect;

	void initTextures();

	void renderWall(wallstrct* m_wall);
	void renderBlock(int bType, int row, int col);
	void renderGrid();
};