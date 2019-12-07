#include "Timer.hpp"

Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

Timer::~Timer()
{
}

// Start function
void Timer::start()
{
	//Start
	started = true;

	//Unpause
	paused = false;

	// Get current clock time
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

// Stop function
void Timer::stop()
{
	// Stop
	started = false;

	// Unpause
	paused = false;

	// Clear tick variables
	startTicks = 0;
	pausedTicks = 0;
}

// Pause/Unpause function
void Timer::pause()
{
	// Timer started but isn't paused -> Pause
	if (started && !paused)
	{
		// Pause
		paused = true;

		// Paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
	// Timer started and is paused -> Unpause
	if (started && paused)
	{
		// Unpause
		paused = false;

		// Resets the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	// Timer time
	Uint32 time = 0;

	//Return either the paused ticks or the "until now" ticks
	if (started)
	{
		if (paused)
		{
			time = pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}
