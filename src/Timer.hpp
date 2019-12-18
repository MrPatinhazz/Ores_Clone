/**
	Timer class
	Holds game ticks , and timer methods
**/
#pragma once

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>

class Timer
{
public:
	// Inits timer
	Timer();
	~Timer();

	// Timer Functions
	void start();
	void stop();
	void pause();
	void unpause();

	// Get timer time
	Uint32 getTicks();

	// Get timer status. A timer that did not start will always be paused
	bool isPaused() { return m_paused && m_started; };
	bool hasStarted() { return m_started; };

private:
	// Game ticks when timer starts and was paused
	Uint32 m_start_ticks, m_paused_ticks;

	//Timer status
	bool m_paused, m_started;
};