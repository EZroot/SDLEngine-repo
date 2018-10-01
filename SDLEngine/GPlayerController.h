#ifndef GPLAYERCONTROLLER_H
#define GPLAYERCONTROLLER_H
#include "GEntity.h"
#include <random>
#include "GEntityHandler.h"
class GPlayerController :
	public GEntity
{
public:
	GPlayerController( int xStart, int yStart, SDL_Window* window, SDL_Renderer* renderer);
	GPlayerController(SDL_Window* window, SDL_Renderer* renderer);
	~GPlayerController();

	void Events();
	void Collided(GEntityCollisionTypes::CollisionType collisionType);
	void Update(float updateStep);
	void Render(SDL_Renderer* renderer);

	void ParticleUpdate(float updateStep) ;
	void ParticleRender(SDL_Renderer* renderer) ;

private:
	bool canMove = true;
	//Shoot timer
	int maxShootTimerValue = 5; //how long in between shots
	int shootTimer = 0; //timer

	//Controls
	void PlayerMovement(int speed);
	void PlayerShooting();
};
#endif