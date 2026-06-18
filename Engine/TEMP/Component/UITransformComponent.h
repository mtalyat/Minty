#pragma once

/**
 * @file UITransformComponent.h
 * @brief Header file defining the UITransformComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Data/UITransform.h"
#include "Minty/Entity/Entity.h"

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
		Entity canvas = INVALID_ENTITY;

		/**
		 * @brief The UITransform data.
		 */
		UITransform transform;
	};

	template<>
	struct Serializer<UITransformComponent>
	{
		static Bool serialize(Writer& writer, UITransformComponent const& value);
		static Bool deserialize(Reader& reader, UITransformComponent& value);
	};
}
