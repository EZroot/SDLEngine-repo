#ifndef GGAMESTATE_H
#define GGAMESTATE_H

#include <SDL.h>
#include "EEvent.h"
#include "GCamera.h"

class GGameState
{
public:
	//Game states
	enum GameStates
	{
		STATE_NULL,
		STATE_INTRO,
		STATE_STAGE01,
		STATE_STAGE01END,
		STATE_STAGEDEATH,
		STATE_EXIT,
	};

	virtual ~GGameState();
	virtual void Events(bool& QUIT_FLAG) = 0;
	virtual void Collisions() = 0;
	virtual void Update(float updateStep) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

	//Sets the stages camera to the game camera for stage control (camera shake, etc)
	void SetCamera(GCamera* mainCamera);

	//Queue next state and change it
	void SetStateQueue(int gameState);
	void ChangeState(GGameState*& currentState, SDL_Window* window, SDL_Renderer* renderer, GCamera* gameCamera);

	//State vars
	int id = STATE_NULL;
	int queuedState = STATE_NULL;

	//Camera
	GCamera* gameCamera = nullptr;
};

#endif