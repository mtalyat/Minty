#pragma once

/**
 * @file TransformComponent.hpp
 * @brief Header file defining the TransformComponent structure.
 * @author Mitchell Talyat
 */

#include "Core/Data/Transform.hpp"

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
		Transform transform = {};
	};

	template<>
	struct Serializer<TransformComponent>
	{
		static void serialize(Writer& writer, TransformComponent const& value);
		static Bool deserialize(Reader& reader, TransformComponent& value);
	};
}
