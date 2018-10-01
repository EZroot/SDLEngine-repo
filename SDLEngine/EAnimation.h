#ifndef EAnimation_H_
	#define EAnimation_H_

#include <SDL.h>

class EAnimation
{
public:
	EAnimation();
	~EAnimation();

	static SDL_Texture* OnLoad(SDL_Window* window, SDL_Renderer* renderer, char* file,
		SDL_Rect*& clips, int amountOfFrames, int frameWidth, int frameHeight);
	static bool OnDraw(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y,
		SDL_Rect*& clips, int amountOfFrames, int frameCounter, int frameSpeed);
	static bool OnFree(SDL_Texture* texture, SDL_Rect*& clips);
};

#endif

