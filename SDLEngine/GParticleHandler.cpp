#include "GParticleHandler.h"
#include "ELog.h"
#include "GEntity.h"
#include "GParticle.h"
GParticleHandler::GParticleHandler(SDL_Window* window, SDL_Renderer* renderer)
{
	//Create particles
	//Explosions
	explosion = new GParticle(GParticle::TYPE_EXPLOSION, window, renderer);
	bigExplosion = new GParticle(GParticle::TYPE_BIGEXPLOSION, window, renderer);
	bulletExplosion = new GParticle(GParticle::TYPE_BULLETEXPLOSION, window, renderer);

	explosion->SetActiveStatus(false);
	bigExplosion->SetActiveStatus(false);
	bulletExplosion->SetActiveStatus(false);
}


GParticleHandler::~GParticleHandler()
{
	delete explosion;
	delete bigExplosion;
	delete bulletExplosion;

	explosion = nullptr;
	bigExplosion = nullptr;
	bulletExplosion = nullptr;
}

void GParticleHandler::UpdateParticles(float updateStep)
{
	//Each particle deals with logic if active
	
	//Explosions
	explosion->Update(updateStep);
	bigExplosion->Update(updateStep);
	bulletExplosion->Update(updateStep);
}

void GParticleHandler::RenderParticles(SDL_Renderer * renderer)
{
	//Explosions
	explosion->Render(renderer);
	bigExplosion->Render(renderer);
	bulletExplosion->Render(renderer);
}

void GParticleHandler::CreateExplosion(int startX, int startY, bool isBigExplosion, bool isSmallExplosion)
{
	if (isBigExplosion)
	{
		bigExplosion->SetActiveStatus(true);
		bigExplosion->currFrameCounter = 0;
		bigExplosion->SetPosition(startX+16, startY-32);
	}
	else if (isSmallExplosion)
	{
		bulletExplosion->SetActiveStatus(true);
		bulletExplosion->currFrameCounter = 0;
		bulletExplosion->SetPosition(startX+38, startY+28);
	}
	else
	{
		explosion->SetActiveStatus(true);
		explosion->currFrameCounter = 0;
		explosion->SetPosition(startX, startY);
	}
}