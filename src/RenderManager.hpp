#pragma once

// Render Manager - Render all texts and objetcs in game.
// A future alternative could be each game object handle its own rendering but due to game complexity
// this approach seemed enough. May need a refactoring to implement animations

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

	void renderBg();																	// Background image
	void renderMenu();																	// Initial menu
	void renderPauseScreen();															// Pause screen
	void renderLostScreen();															// You lost screen
	void renderGame(wallstrct* m_wall);													// Wall and grid
	void renderHUD(Uint32 currTime, int max_time, int currScore, int stg_prog, int stage, int max_stg_pts);   // Score, timer and stage
	void renderMultiBomb();																// Multi bomb text
	void renderAimBomb(int _clicks);													// Aim bomb text
	void setFinalScore(int score){m_final_sc = score; };								// Saves final score
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	WTexture m_ore_tex[BTYPES],				// Ore textures
		m_bomb_tex[BTYPES],					// Bomb textures
		m_backg_tex,						// Background image
		m_timer_tex,						// Timer text
		m_score_tex,						// Score text
		m_stage_tex,						// Stage text
		m_pushw_bt,							// Push wall button
		m_endzone_tex,						// End zone text
		m_start_bt,							// Menu start button
		m_quit_bt,							// Menu quit button
		m_paused_tex,						// Paused text
		m_lost1_tex,						// You lost text
		m_lost2_tex,						// Final score text
		m_menuB_bt,							// Back to menu button
		m_multiB_bt,						// Multi bomb info text
		m_aimB_bt;							// Aim bomb clicks left tex

	TTF_Font *m_game_font, *m_paused_font, *m_lost_font;
	SDL_Rect m_timer_rect, m_stage_rect;

	void initTextures();
	int m_final_sc;
	void renderWall(wallstrct* m_wall);
	void renderBlock(int bType, int row, int col);
	void renderGrid();
};