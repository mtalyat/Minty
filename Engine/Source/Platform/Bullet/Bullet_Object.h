#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Library/Bullet.h"

namespace Minty
{
	// forward declarations
	class Collider;
	class Rigidbody;

	// holds data for an object within the Bullet physics simulation
	struct Bullet_Object
	{
		// the entity the object represents
		Entity entity = INVALID_ENTITY;

		// the collider associated with the object (if any)
		Collider* collider = nullptr;

		// the rigidbody associated with the object (if any)
		Rigidbody* rigidbody = nullptr;

		// the layer this object is on
		Layer layerBit = 0;

		// the layer mask (which layers this object can collide with)
		Layer layerMask = 0;
	};
}