#pragma once

/**
 * @file EntitySerializationData.h
 * @brief Header file defining the EntitySerializationData struct.
 * @author Mitchell Talyat
 */

#include "Entity.h"
#include "Core/Data/Map.h"
#include "Core/Data/UUID.h"

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
		EntityHandle entity = INVALID_ENTITY;

		/**
		 * @brief The EntityManager that owns this Entity.
		 */
		EntityManager* entityManager = nullptr;

		/**
		 * @brief Mapping of IDs for prefab Entities to scene Entities.
		 */
		Map<UUID, EntityHandle> const* idMap = nullptr;

		/**
		 * @brief Gets the Entity with the given ID. Uses the ID map if it is available.
		 * @param id The ID to look up.
		 * @return The Entity with the given ID.
		 */
		EntityHandle get_entity(UUID const id) const;
	};
}
