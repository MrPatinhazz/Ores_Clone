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

		//Load level up
		m_level_up = Mix_LoadWAV("assets/433701__dersuperanton__level-up-voice.wav");
		if (m_level_up == NULL)
		{
			cout << "Failed to load sound effect" << Mix_GetError() << endl;
		}
	}
}

MusicMng::~MusicMng()
{
	Mix_FreeMusic(m_menu_music);
	m_menu_music = NULL;
	Mix_FreeChunk(m_level_up);
	m_level_up = NULL;
}

void MusicMng::start()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(m_menu_music, -1);
	}
}

void MusicMng::stop()
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}
}

void MusicMng::pause()
{
	if (Mix_PlayingMusic())
	{
		//Pause the music
		Mix_PauseMusic();
	}
}

void MusicMng::resume()
{
	if (Mix_PausedMusic() == 1)
	{
		//Resume the music
		Mix_ResumeMusic();
	}
}

void MusicMng::levelUp()
{
	Mix_PlayChannel(-1, m_level_up, 0);
}
