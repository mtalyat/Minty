#pragma once
#include "Minty/Entity/Entity.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
	class EntityManager;

	/// <summary>
	/// The data used to serialize an Entity and its Components.
	/// </summary>
	struct EntitySerializationData
	{
		/// <summary>
		/// The Entity being serialized.
		/// </summary>
		Entity entity;

		/// <summary>
		/// The EntityManager that owns this Entity.
		/// </summary>
		EntityManager* entityManager;

		/// <summary>
		/// Mapping of IDs for prefab Entities to scene Entities.
		/// </summary>
		Map<UUID, Entity> const* idMap = nullptr;

		/// <summary>
		/// Gets the Entity with the given ID. Uses the ID map if it is available.
		/// </summary>
		/// <param name="id"></param>
		/// <returns></returns>
		Entity get_entity(UUID const id);
	};
}