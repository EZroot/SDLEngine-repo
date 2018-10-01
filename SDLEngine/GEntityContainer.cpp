#include "GEntityContainer.h"
#include "ELog.h"

GEntityContainer::GEntityContainer()
{
}


GEntityContainer::~GEntityContainer()
{
}

void GEntityContainer::Add(GEntity* entity)
{
	elementList.push_back(entity);
}

std::vector<GEntity*> GEntityContainer::GetElementList()
{
	return elementList;
}

std::vector<GEntity*> GEntityContainer::GetActiveElementList()
{
	std::vector<GEntity*> activeElementList;

	for (element = elementList.begin();
		element != elementList.end();
		++element)
	{
		//if element is active
		if ((*element)->GetActiveStatus() == true)
		{
			//add to our list
			activeElementList.push_back((*element));
		}
	}
	if (activeElementList.empty())
	{
		//ELog::Print("GEntityContainer -> activeElementList could not be returned!!!");
	}
	return activeElementList;
}

std::vector<GEntity*> GEntityContainer::GetInactiveElementList()
{
	std::vector<GEntity*> inactiveElementList;
	for (element = elementList.begin();
		element != elementList.end();
		++element)
	{
		//if element is inactive
		if ((*element)->GetActiveStatus() == false)
		{
			//add to our list
			inactiveElementList.push_back((*element));
		}
	}
	if (inactiveElementList.empty())
	{
		ELog::Print("inactiveElementList could not be returned!!! NO REUSABLE ENTITIES!!!!!");
	}
	return inactiveElementList;
}

GEntity* GEntityContainer::GetSingleInactiveElement()
{
	for (element = elementList.begin();
		element != elementList.end();
		++element)
	{
		//if element is inactive
		if ((*element)->GetActiveStatus() == false)
		{
			return (*element);
		}
	}
	return nullptr;
}

GEntity * GEntityContainer::GetSingleActiveElement()
{
	for (element = elementList.begin();
		element != elementList.end();
		++element)
	{
		//if element is inactive
		if ((*element)->GetActiveStatus() == true)
		{
			return (*element);
		}
	}
	ELog::Print("Couldnt get SINGLE active element");
	return nullptr;
}
