#pragma once

#include "Wall.hpp"
#include "RenderManager.hpp"
#include "Timer.hpp"
#include "MusicManager.hpp"

using namespace std;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos);
	void restart();
	void handleEvent();
	void update();
	void render();
	void clean();
	bool running() { return m_isRunning; };
	
private:
	unsigned int m_currScore, m_currStage, m_MBombType, m_ABomb_clicks, m_push_intv, m_stg_prog, m_max_stg_pts;
	bool m_gameStarted, m_isRunning, m_isPaused, m_isLost, m_isMultiBomb, m_isAimBomb;
	Timer* m_timer;
	Wall* m_wall;
	RenderMng* m_rend;
	MusicMng* m_music;
	
	bool clickedButton(Sint32 mouseX, Sint32 mouseY, int bt);
	void deleteOres(int _row, int _col, int _btype);
	void deleteBomb(int _row, int _col, int _btype);
};