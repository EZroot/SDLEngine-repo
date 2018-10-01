#ifndef EAUDIO_H
#define EAUDIO_H
#include <SDL_mixer.h>

class EAudio
{
public:
	~EAudio();
	static Mix_Chunk* OnLoadFx(const char* filePath);
	static Mix_Music* OnLoadMusic(const char* filePath);

	static void OnFreeFx(Mix_Chunk* music);
	static void OnFreeMusic(Mix_Music* music);
};

#endif