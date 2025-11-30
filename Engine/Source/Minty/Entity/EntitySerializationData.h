#ifndef MINTY_ENTITY_ENTITYSERIALIZATIONDATA_H
#define MINTY_ENTITY_ENTITYSERIALIZATIONDATA_H

/**
 * @file EntitySerializationData.h
 * @brief Header file defining the EntitySerializationData struct.
 * @author Mitchell Talyat
 */

#include "Minty/Entity/Entity.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
	class EntityManager;

	/**
	 * @brief The data used to serialize an Entity and its Components.
	 */
	struct EntitySerializationData
	{
		/**
		 * @brief The Entity being serialized.
		 */
		Entity entity;

		/**
		 * @brief The EntityManager that owns this Entity.
		 */
		EntityManager* entityManager;

		/**
		 * @brief Mapping of IDs for prefab Entities to scene Entities.
		 */
		Map<UUID, Entity> const* idMap = nullptr;

		/**
		 * @brief Gets the Entity with the given ID. Uses the ID map if it is available.
		 * @param id The ID to look up.
		 * @return The Entity with the given ID.
		 */
		Entity get_entity(UUID const id);
	};
}

#endif // MINTY_ENTITY_ENTITYSERIALIZATIONDATA_H