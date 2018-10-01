#include "GEnemySpawner.h"
#include "ELog.h"
#include <random>

GEnemySpawner::GEnemySpawner()
{
}


GEnemySpawner::~GEnemySpawner()
{
}

//THIS SPAWNS ALL 40 ENEMIES RIGHT AWAY!!!
void GEnemySpawner::SpawnLine(GEntityHandler * handlerToSpawnFrom,
	int amount,
	int xStart,
	int yStart,
	int xOffSet,
	int yOffSet,
	int xVelocity, 
	int yVelocity,
	SDL_RendererFlip flip)
{
	bool spawned = false;

	entityList = handlerToSpawnFrom->GetInactiveElementsInContainer();
	////Exit
	if (entityList.empty() || entityList.size() < amount)
	{
		return;
	}
	//Spawn and reset our inactive elements and their components
	int counter = 0;
	for (entityItr = entityList.begin();
		entityItr != entityList.end();
		++entityItr)
	{
		if (counter < amount)
		{
			(*entityItr)->SetActiveStatus(true);
			(*entityItr)->SetPosition(xStart + xOffSet + (rand() % 100), yStart + counter * yOffSet + (rand() % 100));
			(*entityItr)->GetCollider()->SetPosition(xStart, yStart);
			(*entityItr)->SetVelocity(xVelocity, yVelocity);
			counter++;
		}
	}
}
