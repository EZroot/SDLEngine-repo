#include "GAudioHandler.h"
#include "ELog.h"

GAudioHandler::~GAudioHandler()
{
	EAudio::OnFreeMusic(fxStageMusic);
	EAudio::OnFreeFx(fxShipExplosion);
	EAudio::OnFreeFx(fxBulletShoot);

	fxStageMusic = nullptr;
	fxShipExplosion = nullptr;
	fxBulletShoot = nullptr;
}

void GAudioHandler::LoadSounds(Mix_Music * stageMusic, Mix_Chunk * explosionSound, Mix_Chunk * bulletSound)
{
	if (stageMusic == nullptr || explosionSound == nullptr || bulletSound == nullptr)
	{
		ELog::Print("Sound file could not load!");
	}
	fxStageMusic = stageMusic;
	fxShipExplosion = explosionSound;
	fxBulletShoot = bulletSound;

	//CHANNEL ALLOCATION DONE IN EEngine.Cpp
	//Mix_AllocateChannels(16);
}

void GAudioHandler::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void GAudioHandler::SetChannelVolume(int channel, int volume)
{
	Mix_Volume(channel, volume);
}

void GAudioHandler::SetFxVolume(Mix_Chunk* fx, int volume)
{
	Mix_VolumeChunk(fx, volume);
}

void GAudioHandler::Play(MusicType sound, int repeat)
{
	switch (sound)
	{
	case FX_MUSIC:
		Mix_PlayMusic(fxStageMusic, repeat);
		break;
	case FX_EXPLOSION:
		Mix_HaltChannel(2);
		Mix_PlayChannel(2, fxShipExplosion, repeat);
		break;
	case FX_SHOOT:
		Mix_HaltChannel(4);
		Mix_PlayChannel(4,fxBulletShoot, repeat);
		break;
	}
}

void GAudioHandler::Pause()
{
}

void GAudioHandler::Resume()
{
}

Mix_Music* GAudioHandler::fxStageMusic = nullptr;
Mix_Chunk* GAudioHandler::fxShipExplosion = nullptr;
Mix_Chunk* GAudioHandler::fxBulletShoot = nullptr;
