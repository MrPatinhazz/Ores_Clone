#include "MusicManager.hpp"

MusicMng::MusicMng()
{
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_mixer could not initialize!" << Mix_GetError() << endl;
	}
	else
	{
		//Load music
		m_menu_music = Mix_LoadMUS("assets/Miami Nights - Extended Theme.wav");
		if (m_menu_music == NULL)
		{
			cout << "Failed to load menu music" << Mix_GetError() << endl;
		}
	}
}

MusicMng::~MusicMng()
{
	Mix_FreeMusic(m_menu_music);
	m_menu_music = NULL;
}

void MusicMng::start()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(m_menu_music, -1);
	}
}
