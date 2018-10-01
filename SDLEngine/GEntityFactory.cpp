#include "GEntityFactory.h"

#include "GPlayerController.h"
#include "GEnemy.h"
#include "GBullet.h"



GEntityFactory::GEntityFactory()
{
}


GEntityFactory::~GEntityFactory()
{
}

GEntity * GEntityFactory::Create(EntityType entityType, SDL_Window* window, SDL_Renderer* renderer)
{
	switch (entityType)
	{
	case ENTITY_PLAYER:
		return new GPlayerController(window, renderer);
		break;
	case ENTITY_WEAKENEMY:
		return new GEnemy(GEnemy::TYPE_WEAK, window, renderer);
		break;
	case ENTITY_STRONGENEMY:
		return new GEnemy(GEnemy::TYPE_STRONG, window, renderer);
		break;
	case ENTITY_ASTEROID:
		return new GEnemy(GEnemy::TYPE_ASTEROID, window, renderer);
		break;
	case ENTITY_BOSS:
		return new GEnemy(GEnemy::TYPE_BOSS, window, renderer);
		break;
	case ENTITY_BULLET:
		return new GBullet(GBullet::TYPE_WEAK, window, renderer);
		break;
	}
	return nullptr;
}
