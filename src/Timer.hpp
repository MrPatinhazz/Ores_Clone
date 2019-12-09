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
	bool isPaused() { return paused && started; };
	bool hasStarted() { return started; };

private:
	// Game ticks when timer starts and was paused
	Uint32 startTicks, pausedTicks;

	//Timer status
	bool paused, started;
};