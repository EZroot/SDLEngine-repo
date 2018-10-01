#ifndef GENTITYHANDLER_H
#define GENTITYHANDLER_H

#include <SDL.h>
#include <vector>
#include "GEntityFactory.h"
#include "GEntityContainer.h"
#include "GEntity.h"
#include "GEntityCollisionTypes.h"
#include "ECollider.h"
#include "GParticleHandler.h"
#include "GComboHandler.h"

//This class is responsible for each element on screen
class GEntityHandler
{
public:

	GEntityHandler(int amountOfEntities, GEntityFactory::EntityType entityType, SDL_Window* window, SDL_Renderer* renderer);
	~GEntityHandler();

	//Spawn elements from container
	void SpawnSingleElement(int xStart, int yStart, int xVelocity);

	//Call each elements function
	void HandleEvents();
	void HandleCollisions(GEntityHandler* otherHandler, GEntityCollisionTypes::CollisionType collisionType);
	void HandleCollisions(GEntity* otherEntity, GEntityCollisionTypes::CollisionType collisionType);
	void HandleUpdates(float updateStep);
	void HandleRendering(SDL_Renderer* renderer);

	void HandleParticleUpdates(float updateStep);
	void HandleParticleRendering(SDL_Renderer* renderer);

	//Getters
	std::vector<GEntity*> GetElementsInContainer();
	std::vector<GEntity*> GetActiveElementsInContainer();
	std::vector<GEntity*> GetInactiveElementsInContainer();
	GEntity* GetSingleInactiveElementInContainer();
	GEntity* GetSingleActiveElementInContainer();

	//Container
	GEntityContainer container;

	//Element data
	std::vector<GEntity*> entityList;
	std::vector<GEntity*>::iterator entity;
	std::vector<GEntity*> otherEntityList;
	std::vector<GEntity*>::iterator otherEntity;
};

#endif