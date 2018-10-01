#ifndef EEVENT_H
#define EEVENT_H

#include <SDL.h>

class EEvent
{
public:
	EEvent();
	~EEvent();

	static void WindowEventHandler(bool& QUIT_FLAG);
	static bool OnKeyDown(SDL_Scancode keyCode);
	static bool OnKey(SDL_Scancode keyCode);
};

#endif