#include "pch.h"
#include "EntitySerializationData.h"
#include "Minty/Entity/EntityManager.h"

using namespace Minty;

Entity Minty::EntitySerializationData::get_entity(UUID const id)
{
	if (idMap)
	{
		// use the ID map, if found
		auto it = idMap->find(id);
		if (it != idMap->end())
		{
			return entityManager->get_entity(it->get_second());
		}
	}
	// get the entity normally
	return entityManager->get_entity(id);
}
