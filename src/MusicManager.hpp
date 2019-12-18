#pragma once

#include "SDL.h"
#include <SDL_mixer.h>
#include <iostream>
#include <string>

using namespace std;

class MusicMng
{
public:
	MusicMng();
	~MusicMng();

	void start();
	void stop();
	void pause();
	void resume();

private:
	Mix_Music *m_menu_music = nullptr;
};
