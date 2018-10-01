#ifndef GINTRO_H
#define GINTRO_H
#include <SDL.h>
#include "GGameState.h"
#include "GAudioHandler.h"
#include "ETexture.h"

class GIntro : public GGameState
{
public:
	//Loads resources
	GIntro(SDL_Window* window, SDL_Renderer* renderer);
	//Frees resources
	~GIntro();

	//Stage Functions
	void Events(bool& QUIT_FLAG);
	void Collisions();
	void Update(float updateStep);
	void Render(SDL_Renderer* renderer);

private:
	//Intro Surface
	SDL_Texture* background;
	SDL_Texture* background2;

	GAudioHandler audioHandler;

	float xPos = 0.0f;
};

#endif