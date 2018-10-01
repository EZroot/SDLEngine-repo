#ifndef GENTITYCONTAINER_H
#define GENTITYCONTAINER_H
#include <SDL.h>
#include <vector>
#include "GEntity.h"

//This class holds every element in our scene
class GEntityContainer
{
public:
	GEntityContainer();
	~GEntityContainer();

	//List Controls
	void Add(GEntity* entity);

	//Getter
	std::vector<GEntity*> GetElementList();
	std::vector<GEntity*> GetActiveElementList(); 
	std::vector<GEntity*> GetInactiveElementList();
	GEntity* GetSingleInactiveElement();
	GEntity* GetSingleActiveElement();

private:
	//Element list
	std::vector<GEntity*> elementList;
	std::vector<GEntity*>::iterator element;
};

#endif