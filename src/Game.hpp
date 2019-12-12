#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Wall.hpp"
#include "RenderManager.hpp"
#include "Timer.hpp"

using namespace std;

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
	bool clickedPushW(Sint32 mouseX, Sint32 mouseY);
	
private:
	unsigned int m_currScore;
	unsigned int m_currStage;

	bool m_isRunning;
	Timer* m_timer;
	Wall* m_wall;
	RenderMng* m_rend;
};