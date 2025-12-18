#pragma once
#include "Minty/Entity/Entity.h"
#include "Minty/Library/Bullet.h"

namespace Minty
{
	// holds data for an object within the Bullet physics simulation
	struct Bullet_Object
	{
		// the entity the object represents
		Entity entity = INVALID_ENTITY;

		// the collider associated with the object (if any)
		Collider* collider = nullptr;
	};
}