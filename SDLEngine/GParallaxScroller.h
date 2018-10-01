#ifndef GPARALLAXSCROLLER_H
#define GPARALLAXSCROLLER_H
#include <SDL.h>
#include <SDL_image.h>
#include "GBackground.h"

class GParallaxScroller
{
public:
	GParallaxScroller(SDL_Window* window, SDL_Renderer* renderer);
	~GParallaxScroller();

	void Update(float updateStep);
	void Render(SDL_Renderer* renderer);

	//List
	GBackground* base = nullptr;
	GBackground* para1 = nullptr;
	GBackground* para2 = nullptr;
	GBackground* para3 = nullptr;
	GBackground* para4 = nullptr;
	GBackground* wideScreen = nullptr;
};

#endif