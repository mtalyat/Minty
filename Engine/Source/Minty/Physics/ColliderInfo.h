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

namespace Minty
{
    class Mesh;

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
		Ref<Mesh> mesh = nullptr;

		/**
		 * @brief The size of the collider.
		 */
		Float3 size = Math::ONE;

		/**
		 * @brief If the Collider is static or not. 
		 * If static, it cannot move, rotate, deform, or have a RigidBody.
		 */
		Bool isStatic = false;
	};
}

#endif // MINTY_PHYSICS_COLLIDERINFO_H