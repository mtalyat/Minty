#pragma once

/**
 * @file NameComponent.h
 * @brief Header file defining the NameComponent structure.
 * @author Mitchell Talyat
 */

#include "Core/Data/String.h"
#include "Core/Serialize/Serializer.h"

namespace Minty
{
	/**
	 * @brief Holds the name of an Entity.
	 */
	struct NameComponent	
	{
		/**
		 * @brief The name of the entity.
		 */
		String name = "";
	};

	template<>
	struct Serializer<NameComponent>
	{
		static Bool serialize(Writer& writer, NameComponent const& value);
		static Bool deserialize(Reader& reader, NameComponent& value);
	};
}
