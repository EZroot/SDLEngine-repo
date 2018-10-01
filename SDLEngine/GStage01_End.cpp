#include "GStage01_End.h"
#include "ELog.h"


GStage01_End::GStage01_End(SDL_Window* window, SDL_Renderer* renderer)
{
	//Start loading
	ELog::Print("Loading StageEnd.");

	//Load images
	background = ETexture::OnLoad(window, renderer, (char*)"Resources/endStageScreen.png");

	//Load Audio
	audioHandler.LoadSounds(EAudio::OnLoadMusic("Resources/sounds/Menu_Music_finished_2.ogg"), EAudio::OnLoadFx("Resources/sounds/Enemy_Ship_Gunshot.ogg"), EAudio::OnLoadFx("Resources/sounds/Enemy_Ship_Gunshot.ogg"));
	audioHandler.SetMusicVolume(MIX_MAX_VOLUME / 2);
	//audioHandler.SetChannelVolume(-1, 0);

	//Finished loading
	ELog::Print("Loading Finished.");
}


GStage01_End::~GStage01_End()
{
	ELog::Print("Freed StageEnd.");
	//Free memory
	ETexture::OnFree(background);
}

void GStage01_End::Events(bool & QUIT_FLAG)
{
	//God-level shit dawg
	if (EEvent::OnKeyDown(SDL_SCANCODE_SPACE))
	{
		//Change level
		SetStateQueue(STATE_STAGE01);
	}
}

void GStage01_End::Collisions()
{
}

void GStage01_End::Update(float updateStep)
{
	//Background
	if (Mix_PlayingMusic() == 0)
	{
		audioHandler.Play(audioHandler.FX_MUSIC, 0);
	}
}

void GStage01_End::Render(SDL_Renderer * renderer)
{
	ETexture::OnDraw(background, renderer, 0, 0);
}
