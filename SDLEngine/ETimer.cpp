#include "ETimer.h"



ETimer::ETimer()
{
	//Default our timer
	startTime = 0;
	pausedTime = 0;

	started = false;
	paused = false;
}


ETimer::~ETimer()
{
}

void ETimer::Start()
{
	started = true;
	paused = false;

	startTime = SDL_GetTicks();
	pausedTime = 0;
}

void ETimer::Stop()
{
	//Reset the timer and save our time
	started = false;
	paused = true;
	pausedTime = SDL_GetTicks() - startTime;
	startTime = 0;

}

void ETimer::Pause()
{
	if (started && !paused)
	{
		paused = true;
		
		pausedTime = SDL_GetTicks() - startTime;
		startTime = 0;
	}
}

void ETimer::Unpause()
{
	if (started && paused)
	{
		paused = false;

		startTime = SDL_GetTicks() - pausedTime;
		pausedTime = 0;
	}
}

Uint32 ETimer::GetTicks()
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
		{
			time = pausedTime;
		}
		else
		{
			time = SDL_GetTicks() - startTime;
		}
	}
	return time;
}

bool ETimer::isStarted()
{
	return started;
}

bool ETimer::isPaused()
{
	return paused && started;
}
