#include "GEntityHandler.h"
#include "ECollider.h"
#include "ELog.h"

//Handles all Entities within a container
GEntityHandler::GEntityHandler(int amountOfEntities, GEntityFactory::EntityType entityType, SDL_Window* window, SDL_Renderer* renderer)
{
	for (int i = 0; i < amountOfEntities; i++)
	{
		container.Add(GEntityFactory::Create(entityType, window, renderer));
	}
}

GEntityHandler::~GEntityHandler()
{
	
}

void GEntityHandler::SpawnSingleElement(int xStart, int yStart, int xVelocity)
{
	//Get active+inactive elements
	entityList = container.GetInactiveElementList();
	////Exit
	if (entityList.empty())
	{
		ELog::Print("SpawnLine: Inactive elements doesnt exist!");
		return;
	}

	//Spawn and reset our inactive elements and their components
	for (entity = entityList.begin();
		entity != entityList.end();
		++entity)
	{
		(*entity)->SetActiveStatus(true);
		(*entity)->SetPosition(xStart, yStart);
		(*entity)->GetCollider()->SetPosition(xStart, yStart);
		(*entity)->SetVelocity(xVelocity, 0);
	}
}

void GEntityHandler::HandleEvents()
{
	//might not need this
}

//Collisions
void GEntityHandler::HandleCollisions(GEntityHandler* otherHandler, GEntityCollisionTypes::CollisionType collisionType)
{
	//Set our entityLists
	entityList = GetActiveElementsInContainer();
	otherEntityList = otherHandler->GetActiveElementsInContainer();
	////Exit
	if (entityList.empty() || otherEntityList.empty())
	{
		return;
	}

	//For each entity in other handler container
	for (otherEntity = otherEntityList.begin();
		otherEntity != otherEntityList.end();
		++otherEntity)
	{

		//For each entity in our container
		for (entity = entityList.begin();
			entity != entityList.end();
			++entity)
		{
			SDL_Rect a = (*entity)->GetCollider()->GetColliderRect();
			SDL_Rect b = (*otherEntity)->GetCollider()->GetColliderRect();

			//if EntityA collided with EntityB
			if (ECollider::CheckCollision(a, b))
			{
				//Call entity collisions
				(*entity)->Collided(collisionType);
				(*otherEntity)->Collided(collisionType);
			}
		}
	}
}

//Single entity collisions
void GEntityHandler::HandleCollisions(GEntity * otherEntity, GEntityCollisionTypes::CollisionType collisionType)
{
	//Set our entityLists
	entityList = GetActiveElementsInContainer();

	////Exit
	if (otherEntity == nullptr)
	{
		return;
	}

	//For each entity in our container
	for (entity = entityList.begin();
		entity != entityList.end();
		++entity)
	{
		SDL_Rect a = (*entity)->GetCollider()->GetColliderRect();
		SDL_Rect b = otherEntity->GetCollider()->GetColliderRect();
		if (ECollider::CheckCollision(a, b))
		{
			//Call entity collisions
			(*entity)->Collided(collisionType);
			otherEntity->Collided(collisionType);
		}
	}
}

void GEntityHandler::HandleUpdates(float updateStep)
{
	entityList = GetActiveElementsInContainer();
	////Exit
	if (entityList.empty())
	{
		//ELog::Print("Failed to handle updates. No elements!");
		return;
	}
	for (entity = entityList.begin();
		entity != entityList.end();
		++entity)
	{
		(*entity)->Update(updateStep);
	}
}

void GEntityHandler::HandleRendering(SDL_Renderer * renderer)
{
	entityList = GetActiveElementsInContainer();
	////Exit
	if (entityList.empty())
	{
		//ELog::Print("Failed to Render!");
		return;
	}
	//Render
	for (entity = entityList.begin();
		entity != entityList.end();
		++entity)
	{
		(*entity)->Render(renderer);
	}
}

//for ALL elements
void GEntityHandler::HandleParticleUpdates(float updateStep)
{
	entityList = GetElementsInContainer();
	////Exit
	if (entityList.empty())
	{
		//ELog::Print("Failed to handle updates. No elements!");
		return;
	}
	for (entity = entityList.begin();
		entity != entityList.end();
		++entity)
	{
		(*entity)->ParticleUpdate(updateStep);
	}
}

//for ALL elements
void GEntityHandler::HandleParticleRendering(SDL_Renderer * renderer)
{
	entityList = GetElementsInContainer();
	////Exit
	if (entityList.empty())
	{
		//ELog::Print("Failed to handle updates. No elements!");
		return;
	}
	for (entity = entityList.begin();
		entity != entityList.end();
		++entity)
	{
		(*entity)->ParticleRender(renderer);
	}
}

std::vector<GEntity*> GEntityHandler::GetElementsInContainer()
{
	return container.GetElementList();
}

std::vector<GEntity*> GEntityHandler::GetActiveElementsInContainer()
{
	return container.GetActiveElementList();
}

std::vector<GEntity*> GEntityHandler::GetInactiveElementsInContainer()
{
	return container.GetInactiveElementList();
}

GEntity * GEntityHandler::GetSingleInactiveElementInContainer()
{
	return container.GetSingleInactiveElement();
}

GEntity * GEntityHandler::GetSingleActiveElementInContainer()
{
	return container.GetSingleActiveElement();
}
