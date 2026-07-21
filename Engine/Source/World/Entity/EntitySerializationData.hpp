#pragma once

/**
 * @file EntitySerializationData.hpp
 * @brief Header file defining the EntitySerializationData struct.
 * @author Mitchell Talyat
 */

#include "Entity.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Data/UUID.hpp"

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
