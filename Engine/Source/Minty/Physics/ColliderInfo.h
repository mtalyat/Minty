#ifndef MINTY_PHYSICS_COLLIDERINFO_H
#define MINTY_PHYSICS_COLLIDERINFO_H

/**
 * @file ColliderInfo.h
 * @brief Header file defining the ColliderInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Shape.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
    /**
	 * @brief The arguments for a Collider.
	 */
	struct ColliderInfo
	{
		/**
		 * @brief The shape of the collider.
		 */
		Shape shape = Shape::Empty;

		/**
		 * @brief The data for a custom Shape.
		 */
		Shared<Mesh> mesh = nullptr;

		/**
		 * @brief The offset of the collider.
		 */
		Float3 offset = Math::ZERO;

		/**
		 * @brief The size of the collider.
		 */
		Float3 size = Math::ONE;

		/**
		 * @brief If the Collider is static or not. 
		 * If static, it cannot move, rotate, deform, or have a RigidBody.
		 */
		Bool isStatic = false;

		/**
		 * @brief If the Collider is a trigger or not.
		 * If a trigger, it will not physically interact with other Colliders.
		 */
		Bool isTrigger = false;
	};
}

#endif // MINTY_PHYSICS_COLLIDERINFO_H