#ifndef GENEMY_H
#define GENEMY_H
#include <SDL.h>
#include "GEntity.h"
#include "GComboHandler.h"

class GEnemy :
	public GEntity
{
public:
	enum EnemyType {
		TYPE_WEAK,
		TYPE_STRONG,
		TYPE_ASTEROID,
		TYPE_BOSS
	};

	GEnemy(EnemyType enemyType, SDL_Window * window, SDL_Renderer * renderer);
	~GEnemy();

	void Events();
	void Collided(GEntityCollisionTypes::CollisionType collisionType);
	void Update(float updateStep);
	void Render(SDL_Renderer* renderer);

	void ParticleUpdate(float updateStep);
	void ParticleRender(SDL_Renderer* renderer);

private:

	void BossAI();

	EnemyType currentType;

	//States
	int bossMoveSpeed = 50;
	bool moveUp = true;
	bool moveDown = false;

	int stopTimer = 200; 

	int shootTimer = 15;
};

#endif