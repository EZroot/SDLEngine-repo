#include "EEvent.h"



EEvent::EEvent()
{
}


EEvent::~EEvent()
{
}

void EEvent::WindowEventHandler(bool& QUIT_FLAG)
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			QUIT_FLAG = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//QUIT_FLAG = true;
			break;
		}
	}
}

bool EEvent::OnKeyDown(SDL_Scancode keyCode)
{
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[keyCode])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EEvent::OnKey(SDL_Scancode keyCode)
{
	//Single keystrokes logic
	return true;
}
