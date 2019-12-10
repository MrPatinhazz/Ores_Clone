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
	bool running() { return isRunning; };
	
private:
	int currScore;
	int currStage;

	bool isRunning;
	Timer* gTimer;
	Wall* gWall;
	RenderMng* gRend;
};