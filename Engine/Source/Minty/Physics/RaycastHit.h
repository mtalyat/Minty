#ifndef MINTY_PHYSICS_RAYCASTHIT_H
#define MINTY_PHYSICS_RAYCASTHIT_H

/**
 * @file RaycastHit.h
 * @brief Header file defining the RaycastHit struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	/**
	 * @brief Represents a Raycast hit.
	 */
	struct RaycastHit
	{
		/**
		 * @brief The position of the hit.
		 */
		Float3 point = Math::ZERO;

		/**
		 * @brief The normal of the surface hit.
		 */
		Float3 normal = Math::UP;
		
		/**
		 * @brief The distance from the ray's origin to the hit point.
		 */
		Float distance = 0.0f;
		
		/**
		 * @brief The Entity that was hit.
		 */
		Entity entity = INVALID_ENTITY;
	};
}

#endif // MINTY_PHYSICS_RAYCASTHIT_H