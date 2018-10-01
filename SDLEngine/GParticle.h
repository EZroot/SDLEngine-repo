#ifndef GPARTICLE_H
#define GPARTICLE_H

#include <SDL.h>
#include "EAnimation.h"
#include "ETexture.h"

class GParticle
{
public:

	enum ParticleType
	{
		TYPE_EXPLOSION,
		TYPE_BIGEXPLOSION,
		TYPE_BULLETEXPLOSION
	};

	GParticle(ParticleType type, SDL_Window* window, SDL_Renderer* renderer);
	~GParticle();

	//Called by stage particle handler
	 void Update(float updateStep);
	 void Render(SDL_Renderer* renderer);

	 //Status
	 int GetCurrentParticleType();
	 bool GetActiveStatus();
	 int GetPosX();
	 int GetPosY();
	 int GetXVel();
	 int GetYVel();

	 void SetParticleType(ParticleType type);
	 void SetActiveStatus(bool statusFlag);
	 void SetPosition(int x, int y);
	 void SetVelocity(int x, int y);
	 //Status
	 ParticleType currentType;
	 bool isActive = false;

	 //Position
	 int xPos = 0;
	 int yPos = 0;
	 
	 //Physics 
	 int xVel = 0;
	 int yVel = 0;

	 //Sprites
	 SDL_Texture* particleSprite = nullptr;
	 SDL_Rect* particleAnimationClips = nullptr;

	 //Animation
	 float currFrameCounter = 0.0f;

private:
	void XPMovement(float updateStep);
};

#endif