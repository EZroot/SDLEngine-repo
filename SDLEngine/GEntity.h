#ifndef GENTITY_H
	#define GENTITY_H

#include <SDL.h>
#include "ETexture.h"
#include "ECollider.h"
#include "GEntityCollisionTypes.h"
#include "GComboHandler.h"
#include "GParticleHandler.h"

//Audio
#include "GAudioHandler.h"

class GEntity
{
public:
	~GEntity();

	virtual void Events() = 0;
	virtual void Collided(GEntityCollisionTypes::CollisionType collisionType) = 0;
	virtual void Update(float updateStep) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

	virtual void ParticleUpdate(float updateStep) = 0;
	virtual void ParticleRender(SDL_Renderer* renderer) = 0;


	//Entity functions
	void Shoot(int xSpriteOffset, int ySpriteOffset, int xVel);
	void DecreaseHealth(int setHealthValue, bool useBigExplosion = false, bool useSmallExplosion = false);
	void OnDeath(int setHealthValue, bool addToKillCount, bool useBigExplosion, bool useSmallExplosion);

	//Getter 
	int GetHealth();
	ECollider* GetCollider();
	bool GetActiveStatus();
	int GetPosX();
	int GetPosY();
	int GetVelX();
	int GetVelY();

	//Setter
	void SetHealth(int number);
	void SetUseableBulletEntity(GEntity* bulletEntity); //must be inactive
	void SetActiveStatus(bool statusFlag);
	void SetPosition(int x, int y);
	void SetVelocity(int hSpeed, int vSpeed);

	//Stats
	int entityHealth = 3; //Ship Health

	//Position
	float xPos = 0;
	float yPos = 0;

	//Physics
	float xVel = 0;
	float yVel = 0;

	//Entity Status
	bool isActive = true;

	//Entity sprite
	SDL_Texture* sprite = nullptr;
	int SPRITE_WIDTH = 0;
	int SPRITE_HEIGHT = 0;

	//Entity Collider
	ECollider* collider = nullptr;

	//Entity Bullet
	GEntity* bullet = nullptr;

	//Entity Particles
	GParticleHandler* particleHandler = nullptr;
};

#endif
