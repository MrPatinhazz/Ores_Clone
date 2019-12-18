#pragma once

// Music manager - controls game music and sound effects

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
	void levelUp();

private:
	Mix_Music *m_menu_music = nullptr;
	Mix_Chunk* m_level_up = nullptr;
};
