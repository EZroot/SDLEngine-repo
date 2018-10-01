#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "ETexture.h"
#include "EAnimation.h"
#include "EEvent.h"
#include "ETimer.h"
#include "ELog.h"

#include "GGame.h"
/*
this file is entirely for testing purposes.
Store this engine in a SDLEngine folder and then make a game framework based around it
*/
//The window we'll be rendering to
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

//Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//FPS Timer
ETimer fpsTimer;
ETimer capTimer;
int countedFrames;
//for fps calcs
int fps = 0;
float fpsTime = 0.f;

//Update Timer
ETimer updateTimer;

//Game
GGame* game;

//Engine initialization
bool OnInit()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return 0;
	}

	//Initialize SDL_Image (Optional, but quicker here.)
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		ELog::Print("SDL_Image Init Error");
		SDL_Quit();
		return 0;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return 0;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 0;
	}

	//Create window
	if ((gWindow = SDL_CreateWindow("Shootemup", 300, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == nullptr)
	{
		ELog::Print("SDL_Createwindow Error");
		SDL_Quit();
		return 0;
	}
	//Create renderer
	if ((gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)) == nullptr) //| SDL_RENDERER_PRESENTVSYNC
	{
		SDL_DestroyWindow(gWindow);
		ELog::Print("SDL_CreateRenderer Error");
		SDL_Quit();
		return 0;
	}

	//FPS Timer
	fpsTimer.Start();
	countedFrames = 0;

	//The Game
	game = new GGame(gWindow, gRenderer);
	
	return 1;
}

//Engine Loop
void OnUpdate()
{
	bool QUIT_FLAG = false;
	bool SHOW_FPS = false;

	while (!QUIT_FLAG)
	{
		//start our cap timer
		capTimer.Start();

		//Event Handler for the Window Form
		EEvent::WindowEventHandler(QUIT_FLAG);
		
		//Game State Event Handler
		game->Events(QUIT_FLAG);

		//Calculate update step
		float updateStep = updateTimer.GetTicks() / 1000.0f;

		//Calculate FPS
		if (SHOW_FPS)
		{
			fpsTime += updateStep;
			fpsTime /= 2.f;
			fps = 1.0f / fpsTime;
			ELog::ShowFPS(fps);
		}

		//Game State Logic
		game->Update(gWindow, gRenderer, (float)updateStep);
		
		//Restart update timer
		updateTimer.Start();

		//Game state Render
		game->Render(gRenderer);

		//Update frame counter
		countedFrames++;

		//If frame finished early
		int frameTicks = capTimer.GetTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}
}

//Free Engine
void OnCleanup()
{
	delete game;
	game = nullptr;

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = nullptr;
	gWindow = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* args[])
{
	OnInit();
	OnUpdate();
	OnCleanup();
	ELog::Print("SUCCESS!");
	return 0;
}