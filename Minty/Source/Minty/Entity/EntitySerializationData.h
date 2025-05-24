#pragma once
#include "Minty/Entity/Entity.h"

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
	};
}