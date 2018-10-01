#ifndef GPARTICLEHANDLER_H
	#define GPARTICLEHANDLER_H
#include <SDL.h>
#include "GParticle.h"
#include <vector>

//cant include gentity because a gentity is using particle-handler before the compiler reads it
class GParticleHandler
{
public:
	GParticleHandler(SDL_Window* window, SDL_Renderer* renderer);
	~GParticleHandler();

	void UpdateParticles(float updateStep);
	void RenderParticles(SDL_Renderer* renderer);

	void CreateExplosion(int startX, int startY, bool isBigExplosion = false, bool smallExplosion = false);

	//particles
	GParticle* explosion = nullptr;
	GParticle* bigExplosion = nullptr;
	GParticle* bulletExplosion = nullptr;
};

#endif
