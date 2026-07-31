#pragma once

/**
 * @file UITransformComponent.hpp
 * @brief Header file defining the UITransformComponent structure.
 * @author Mitchell Talyat
 */

#include "Core/Data/UITransform.hpp"
#include "World/Entity/Entity.hpp"

namespace Minty
{
	/**
	 * @brief A component that holds the UI transform data.
	 */
	struct UITransformComponent	
	{
		/**
		 * @brief The Entity with a Canvas component that this UITransformComponent belongs to.
		 */
		EntityHandle canvas = INVALID_ENTITY;

		/**
		 * @brief The UITransform data.
		 */
		UITransform transform;
	};

	template<>
	struct Serializer<UITransformComponent>
	{
		static void serialize(Writer& writer, UITransformComponent const& value);
		static Bool deserialize(Reader& reader, UITransformComponent& value);
	};
}
