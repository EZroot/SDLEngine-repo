#ifndef GENEMYSPAWNER_H
#define GENEMYSPAWNER_H
#include <SDL.h>
#include "GEntityHandler.h"
#include <vector>

class GEnemySpawner
{
public:
	GEnemySpawner();
	~GEnemySpawner();

	void SpawnLine(GEntityHandler * handlerToSpawnFrom,
		int amount,
		int xStart,
		int yStart,
		int xOffSet,
		int yOffSet,
		int xVelocity,
		int yVelocity,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

private:

	std::vector<GEntity*> entityList;
	std::vector<GEntity*>::iterator entityItr;

};
#endif