#include "GIntro.h"
#include "ELog.h"

GIntro::GIntro(SDL_Window* window, SDL_Renderer* renderer)
{
	//Start loading
	ELog::Print("Loading Intro.");

	//Load images
	background = ETexture::OnLoad(window, renderer, (char*)"Resources/intro.png");
	background2 = ETexture::OnLoad(window, renderer, (char*)"Resources/bkgd_3.png");
	//Load Audio
	audioHandler.LoadSounds(EAudio::OnLoadMusic("Resources/sounds/OpenGameArt/AtmosphericSpace.ogg"), EAudio::OnLoadFx("Resources/sounds/Enemy_Ship_Gunshot.ogg"), EAudio::OnLoadFx("Resources/sounds/Enemy_Ship_Gunshot.ogg"));
	audioHandler.SetMusicVolume(MIX_MAX_VOLUME / 2);
	//audioHandler.SetChannelVolume(-1, 0);

	//Finished loading
	ELog::Print("Loading Finished.");
}


GIntro::~GIntro()
{
	ELog::Print("Freed Intro.");
	//Free memory
	ETexture::OnFree(background);
}

void GIntro::Events(bool& QUIT_FLAG)
{
	//God-level shit dawg
	if (EEvent::OnKeyDown(SDL_SCANCODE_SPACE))
	{
		//Change level
		SetStateQueue(STATE_STAGE01);
	}
}

void GIntro::Collisions()
{
}

void GIntro::Update(float updateStep)
{
	//Background music
	if (Mix_PlayingMusic() == 0)
	{
		audioHandler.Play(audioHandler.FX_MUSIC, 0);
	}

	xPos += -20.0f * updateStep;
	if (xPos < -2000)
	{
		xPos = 0;
	}
}

void GIntro::Render(SDL_Renderer* renderer)
{
	ETexture::OnDraw(background, renderer, 0, 0);
	ETexture::OnDraw(background2, renderer,(float)xPos+2000, 0);
	ETexture::OnDraw(background2, renderer,(float)xPos, 0);

}
