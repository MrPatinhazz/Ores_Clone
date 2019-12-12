#include "Timer.hpp"

Timer::Timer()
{
	m_start_ticks = 0;
	m_paused_ticks = 0;

	m_paused = false;
	m_started = false;
}

Timer::~Timer()
{
}

// Start function
void Timer::start()
{
	//Start
	m_started = true;

	//Unpause
	m_paused = false;

	// Get current clock time
	m_start_ticks = SDL_GetTicks();
	m_paused_ticks = 0;
}

// Stop function
void Timer::stop()
{
	// Stop
	m_started = false;

	// Unpause
	m_paused = false;

	// Clear tick variables
	m_start_ticks = 0;
	m_paused_ticks = 0;
}

// Pause/Unpause function
void Timer::pause()
{
	// Timer started but isn't paused -> Pause
	if (m_started && !m_paused)
	{
		// Pause
		m_paused = true;

		// Paused ticks
		m_paused_ticks = SDL_GetTicks() - m_start_ticks;
		m_start_ticks = 0;
	}
}

void Timer::unpause()
{
	// Timer started and is paused -> Unpause
	if (m_started && m_paused)
	{
		// Unpause
		m_paused = false;

		// Resets the starting ticks
		m_start_ticks = SDL_GetTicks() - m_paused_ticks;
		m_paused_ticks = 0;
	}
}

Uint32 Timer::getTicks()
{
	// Timer time
	Uint32 _time = 0;

	//Return either the paused ticks or the "until now" ticks
	if (m_started)
	{
		if (m_paused)
		{
			_time = m_paused_ticks;
		}
		else
		{
			_time = SDL_GetTicks() - m_start_ticks;
		}
	}

	return _time;
}
