#ifndef ETIMER_H
#define ETIMER_H

#include <SDL.h>

class ETimer
{
public:
	ETimer();
	~ETimer();

	void Start();
	void Stop();
	void Pause();
	void Unpause();

	Uint32 GetTicks();

	bool isStarted();
	bool isPaused();
private:
	Uint32 startTime;
	Uint32 pausedTime;

	bool started;
	bool paused;
};

#endif