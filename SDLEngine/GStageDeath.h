#ifndef GSTAGEDEATH_H
#define GSTAGEDEATH_H
#include <SDL.h>
#include "GGameState.h"
#include "GAudioHandler.h"
#include "ETexture.h"

class GStageDeath : public GGameState
{
public:
	GStageDeath(SDL_Window* window, SDL_Renderer* renderer);
	~GStageDeath();

	//Stage Functions
	void Events(bool& QUIT_FLAG);
	void Collisions();
	void Update(float updateStep);
	void Render(SDL_Renderer* renderer);

private:
	SDL_Texture * background;
	GAudioHandler audioHandler;
};

#endif
