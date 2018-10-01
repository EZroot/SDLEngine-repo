#include "GMainMenu.h"
#include "ELog.h"

GMainMenu::GMainMenu(SDL_Window* window, SDL_Renderer* renderer)
{
	//Start loading
	ELog::Print("Loading Intro.");

	//Load images
	background = ETexture::OnLoad(window, renderer, (char*)"Resources/back.png");

	//Load Audio
	audioHandler.LoadSounds(EAudio::OnLoadMusic("Resources/sounds/Menu_Music_finished_2.ogg"), EAudio::OnLoadFx("Resources/sounds/Enemy_Ship_Gunshot.ogg"), EAudio::OnLoadFx("Resources/sounds/Enemy_Ship_Gunshot.ogg"));
	audioHandler.SetMusicVolume(MIX_MAX_VOLUME / 2);
	//audioHandler.SetChannelVolume(-1, 0);

	//Finished loading
	ELog::Print("Loading Finished.");
}


GMainMenu::~GMainMenu()
{
	ELog::Print("Freed Intro.");
	//Free memory
	ETexture::OnFree(background);
}

void GMainMenu::Events(bool& QUIT_FLAG)
{
	//God-level shit dawg
	if (EEvent::OnKeyDown(SDL_SCANCODE_W))
	{
		//Change level
		SetStateQueue(STATE_STAGE01);
	}
}

void GMainMenu::Collisions()
{
}

void GMainMenu::Update(float updateStep)
{
	//Background music
	if (Mix_PlayingMusic() == 0)
	{
		audioHandler.Play(audioHandler.FX_MUSIC, 0);
	}
}

void GMainMenu::Render(SDL_Renderer* renderer)
{
	ETexture::OnDraw(background, renderer, 0, 0);
}