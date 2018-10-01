#ifndef GMAINMENU_H
#define GMAINMENU_H
#include <SDL.h>
#include "GGameState.h"
#include "GAudioHandler.h"
#include "ETexture.h"

class GMainMenu : public GGameState
{
public: 
	GMainMenu(SDL_Window* window, SDL_Renderer* renderer);
	~GMainMenu();
	//Stage Functions
	void Events(bool& QUIT_FLAG);
	void Collisions();
	void Update(float updateStep);
	void Render(SDL_Renderer* renderer);

private:
	//Intro Surface
	SDL_Texture * background;
	GAudioHandler audioHandler;
};
#endif
