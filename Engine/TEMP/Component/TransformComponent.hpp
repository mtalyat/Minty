#pragma once

/**
 * @file TransformComponent.h
 * @brief Header file defining the TransformComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Transform.h"

namespace Minty
{
	/**
	 * @brief Holds a Transform for an Entity.
	 */
	struct TransformComponent	
	{
		/**
		 * @brief The Transform of this Entity.
		 */
		Transform transform;
	};

	template<>
	struct Serializer<TransformComponent>
	{
		static Bool serialize(Writer& writer, TransformComponent const& value);
		static Bool deserialize(Reader& reader, TransformComponent& value);
	};
}
