#ifndef GENTITYFACTORY_H
#define GENTITYFACTORY_H
#include <SDL.h>
#include "GEntity.h"
#include "GParticleHandler.h"
#include "GComboHandler.h"

//This class ONLY is responsible for creating entities
class GEntityFactory
{
public:
	GEntityFactory();
	~GEntityFactory();

	enum EntityType
	{
		ENTITY_PLAYER,
		ENTITY_WEAKENEMY,
		ENTITY_STRONGENEMY,
		ENTITY_ASTEROID,
		ENTITY_BOSS,
		ENTITY_BULLET
	};

	//Create Entity
	static GEntity* Create(EntityType entityType, SDL_Window* window, SDL_Renderer* renderer);
};

#endif