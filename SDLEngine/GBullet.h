#ifndef GBULLET_H
#define GBULLET_H
#include <SDL.h>
#include "GEntity.h"
class GBullet :
	public GEntity
{
public:
	enum BulletType
	{
		TYPE_WEAK,
		TYPE_STRONG
	};

	GBullet(BulletType bulletType, SDL_Window* window, SDL_Renderer* renderer);
	~GBullet();

	void Events();
	void Collided(GEntityCollisionTypes::CollisionType collisionType);
	void Update(float updateStep);
	void Render(SDL_Renderer* renderer);

	void ParticleUpdate(float updateStep);
	void ParticleRender(SDL_Renderer* renderer);


};
#endif
