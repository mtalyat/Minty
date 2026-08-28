#pragma once

/**
 * @file CollisionComponent.hpp
 * @brief Header file defining the CollisionComponent structure.
 * @author Mitchell Talyat
 */

#include "Collision/CollisionMask/CollisionMask.hpp"
#include "Core/Serialize/Serializer.hpp"
 
namespace Minty
{
	/**
	 * @brief Holds the collision value of an Entity.
	 */
	struct CollisionComponent	
	{
		/**
		 * @brief The collision value of the entity.
		 */
		Collision layer = {};
	};

	template<>
	struct Serializer<CollisionComponent>
	{
		static Bool serialize(Writer& writer, CollisionComponent const& value);
		static Bool deserialize(Reader& reader, CollisionComponent& value);
	};
}
