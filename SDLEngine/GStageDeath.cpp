#include "GStageDeath.h"
#include "ELog.h"

GStageDeath::GStageDeath(SDL_Window* window, SDL_Renderer* renderer)
{
	//Start loading
	ELog::Print("Loading DeathStage.");

	//Load images
	background = ETexture::OnLoad(window, renderer, (char*)"Resources/deathscreen.png");

	//Load Audio
	audioHandler.LoadSounds(EAudio::OnLoadMusic("Resources/sounds/8_Bit_game_over.ogg"), EAudio::OnLoadFx("Resources/sounds/Enemy_Ship_Gunshot_Modify.ogg"), EAudio::OnLoadFx("Resources/sounds/Enemy_Ship_Gunshot_Modify.ogg"));
	audioHandler.SetMusicVolume(MIX_MAX_VOLUME / 2);
	//audioHandler.SetChannelVolume(-1, 0);

	//Finished loading
	ELog::Print("Loading Finished.");
}


GStageDeath::~GStageDeath()
{
	ELog::Print("Freed Deathscreen.");
	//Free memory
	ETexture::OnFree(background);
}

void GStageDeath::Events(bool & QUIT_FLAG)
{
	//God-level shit dawg
	if (EEvent::OnKeyDown(SDL_SCANCODE_SPACE))
	{
		//Change level
		SetStateQueue(STATE_STAGE01);
	}
}

void GStageDeath::Collisions()
{
}

void GStageDeath::Update(float updateStep)
{
	//Background music
	if (Mix_PlayingMusic() == 0)
	{
		audioHandler.Play(audioHandler.FX_MUSIC, 0);
	}
}

void GStageDeath::Render(SDL_Renderer * renderer)
{
	ETexture::OnDraw(background, renderer, 0, 0);
}
