#ifndef GAUDIOHANDLER_H
#define GAUDIOHANDLER_H
#include "EAudio.h"

//Create a handler per stage
//Load stage specific music using EAudio
//Static play button for any object
class GAudioHandler
{
public:
	enum MusicType
	{
		FX_MUSIC,
		FX_EXPLOSION,
		FX_SHOOT
	};

	~GAudioHandler();
	//EAudio::OnLoad(stagemusic.ogg), EAudio::OnLoad(explosionSound.ogg), EAudio::OnLoad(bulletSound.ogg)
	void LoadSounds(Mix_Music* stageMusic, Mix_Chunk* explosionSound, Mix_Chunk* bulletSound);
	void SetMusicVolume(int volume);
	void SetChannelVolume(int channel, int volume);
	void SetFxVolume(Mix_Chunk* fx, int volume);

	//Play a clip thats loaded
	static void Play(MusicType sound, int repeat);
	static void Pause();
	static void Resume();

private:
	//All the sounds required for each stage
	static Mix_Music* fxStageMusic;
	static Mix_Chunk* fxShipExplosion;
	static Mix_Chunk* fxBulletShoot;
};

#endif
