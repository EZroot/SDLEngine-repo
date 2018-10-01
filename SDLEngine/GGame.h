#ifndef GGAME_H
#define GGAME_H
#include <SDL.h>
#include "GGameState.h"
#include "GCamera.h"

//Deals with GameState and forwards all functions to EEngine
class GGame
{
public:

	//Load media
	GGame(SDL_Window* window, SDL_Renderer* renderer);
	//Free media
	~GGame();

	void Events(bool& QUIT_FLAG);
	void Update(SDL_Window* window, SDL_Renderer* renderer, float updateStep);
	void Render(SDL_Renderer* renderer);

	//Getter
	GCamera* GetCamera();

private:
	//GameState status
	GGameState * currentState = nullptr;

	//Rendering surface
	SDL_Texture* renderTexture = nullptr;

	//Main Game Camera
	GCamera mainCamera;
};

#endif