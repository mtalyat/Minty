#pragma once
#include "Minty/Entity/Entity.h"

namespace Minty
{
	class EntityManager;

	struct EntitySerializationData
	{
		Entity entity;

		EntityManager* entityManager;
	};
}