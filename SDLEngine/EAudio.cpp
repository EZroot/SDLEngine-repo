#include "EAudio.h"

EAudio::~EAudio()
{
}

//OGG files
Mix_Chunk * EAudio::OnLoadFx(const char * filePath)
{
	return Mix_LoadWAV(filePath);
}

Mix_Music * EAudio::OnLoadMusic(const char * filePath)
{
	return Mix_LoadMUS(filePath);
}

void EAudio::OnFreeMusic(Mix_Music * music)
{
	Mix_FreeMusic(music);
}

void EAudio::OnFreeFx(Mix_Chunk* music)
{
	Mix_FreeChunk(music);
}
