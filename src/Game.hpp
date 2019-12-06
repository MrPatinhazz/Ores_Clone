#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int w, int h, bool fulls);
	void handleEvent();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; };
	
private:
	bool isRunning;
};