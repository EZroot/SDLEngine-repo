#include "GGameState.h"
#include "GIntro.h"
#include "GStage01.h"
#include "GStage01_End.h"
#include "GStageDeath.h"

#include <iostream>

GGameState::~GGameState()
{
}

void GGameState::SetCamera(GCamera* mainCamera)
{
	gameCamera = mainCamera;
}

void GGameState::SetStateQueue(int gameState)
{
	//If the user doesn't want to exit
	if (queuedState != STATE_EXIT)
	{
		//Set the next state
		queuedState = gameState;
		std::cout << "QUEUE WAS SET!" << std::endl;
		//SDL_Delay(1000);
	}
}

//Level factory
void GGameState::ChangeState(GGameState*& currentState, SDL_Window* window, SDL_Renderer* renderer, GCamera* gameCamera)
{
	int queue = currentState->queuedState;

	//If the state needs to be changed
	if (queue != STATE_NULL)
	{
		//Delete the current state
		if (queue != STATE_EXIT)
		{
			delete currentState;
			currentState = nullptr;
		}

		//Change the state
		switch (queue)
		{
		case STATE_INTRO:
			currentState = new GIntro(window,renderer);
			break;
		case STATE_STAGE01:
			currentState = new GStage01(window, renderer);
			break;
		case STATE_STAGE01END:
			currentState = new GStage01_End(window, renderer);
			break;
		case STATE_STAGEDEATH:
			currentState = new GStageDeath(window, renderer);
			break;
		}

		//Set the stage camera
		currentState->SetCamera(gameCamera);

		//Change the current state ID
		currentState->id = queue;

		//NULL the next state ID
		currentState->queuedState = STATE_NULL;
	}
}
