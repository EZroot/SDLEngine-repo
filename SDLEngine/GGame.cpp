#include "GGame.h"
#include "EEvent.h"
#include "ELog.h"
#include "GIntro.h"
#include "GStage01.h"

//Setup initial State for our video game
GGame::GGame(SDL_Window* window, SDL_Renderer* renderer)
{
	ELog::Print("Game Starting..");

	//Initialize our Game State;
	//Starts our game;
	currentState = new GIntro(window, renderer);
	currentState->id = currentState->STATE_INTRO;
	currentState->SetCamera(GetCamera());

	//Initialize our camera rendering texture
	renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, mainCamera.GetRectData().w, mainCamera.GetRectData().h);

	ELog::Print("Game Started!");
}

//Deallocate our memory
GGame::~GGame()
{
	ELog::Print("Game freed!");
	delete currentState;
	currentState = nullptr;
}

//Setup events for current state
void GGame::Events(bool& QUIT_FLAG)
{
	//Call our level events
	currentState->Events(QUIT_FLAG);
}

//Game Logic
void GGame::Update(SDL_Window* window, SDL_Renderer* renderer, float updateStep)
{
	//Camera Logic
	mainCamera.Update(updateStep);

	//Current Level Collision Handling
	currentState->Collisions();

	//Current Level Logic
	currentState->Update(updateStep);

	//Change level if queued != null
	currentState->ChangeState(currentState, window, renderer, GetCamera());
}

//Game rendering
void GGame::Render(SDL_Renderer * renderer)
{
	SDL_SetRenderTarget(renderer, renderTexture);
	//Clear our renderer target
	SDL_RenderClear(renderer);
	//Render the current level to our MAIN texture
	currentState->Render(renderer);

	//Free the render target
	SDL_SetRenderTarget(renderer, NULL);
	//Clear our renderer target
	SDL_RenderClear(renderer);
	
	//Game renders based on mainCamera data!
	ETexture::OnDraw(renderTexture, renderer, mainCamera.GetRectData().x, mainCamera.GetRectData().y, 0, NULL, SDL_FLIP_NONE);

	//Update renderer
	SDL_RenderPresent(renderer);
}

GCamera* GGame::GetCamera()
{
	return &mainCamera;
}
