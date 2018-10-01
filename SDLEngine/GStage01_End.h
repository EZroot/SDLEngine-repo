#ifndef GSTAGE01_END_H
#define GSTAGE01_END_H
#include <SDL.h>
#include "GGameState.h"
#include "ETexture.h"
#include "GAudioHandler.h"

class GStage01_End : public GGameState
{
public:
	GStage01_End(SDL_Window* window, SDL_Renderer* renderer);
	~GStage01_End();

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