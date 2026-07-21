#pragma once

/**
 * @file ColliderComponent.hpp
 * @brief Header file defining the ColliderComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Pointer.h"
#include "Minty/Physics/Collider.h"

namespace Minty
{	
	/**
	 * @brief Holds a Collider for an Entity.
	 */
	struct ColliderComponent	
	{
		/**
		 * @brief The Collider.
		 */
		Shared<Collider> collider = nullptr;
	};

	template<>
	struct Serializer<ColliderComponent>
	{
		static Bool serialize(Writer& writer, ColliderComponent const& value);
		static Bool deserialize(Reader& reader, ColliderComponent& value);
	};
}
