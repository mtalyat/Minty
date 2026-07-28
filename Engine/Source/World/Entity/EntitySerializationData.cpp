#include "pch.hpp"
#include "EntitySerializationData.hpp"
#include "World/Entity/EntityManager.hpp"

using namespace Minty;

EntityHandle Minty::EntitySerializationData::get_entity(UUID const id) const
{
	if (idMap)
	{
		// use the ID map, if found
		auto it = idMap->find(id);
		if (it != idMap->end())
		{
			return it->get_second();
		}
	}
	// get the entity normally
	return entityManager->find(id);
}
