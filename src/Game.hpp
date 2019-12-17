#pragma once

#include "Wall.hpp"
#include "RenderManager.hpp"
#include "Timer.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

// Stage points needed to pass to the next level
constexpr unsigned int STG_PTS = 400;

// Max clicks allowed when aim bomb is on
constexpr unsigned int AIM_CLICKS = 9;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos);
	void handleEvent();
	void update();
	void render();
	void clean();
	bool running() { return m_isRunning; };
	
private:
	unsigned int m_currScore, m_currStage, m_MBombType, m_ABomb_clicks;
	bool m_isRunning, m_isMultiBomb, m_isAimBomb;
	Timer* m_timer;
	Wall* m_wall;
	RenderMng* m_rend;
	
	bool clickedPushW(Sint32 mouseX, Sint32 mouseY);
	void deleteOres(int _row, int _col, int _btype);
	void deleteBomb(int _row, int _col, int _btype);
};