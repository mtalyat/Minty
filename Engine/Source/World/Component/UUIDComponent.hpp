#pragma once

/**
 * @file UUIDComponent.hpp
 * @brief Header file defining the UUIDComponent structure.
 * @author Mitchell Talyat
 */

#include "Core/Data/UUID.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
	/**
	 * @brief Holds an ID value for an Entity.
	 */
	struct UUIDComponent	
	{
		UUID id = {};
	};

	template<>
	struct Serializer<UUIDComponent>
	{
		static Bool serialize(Writer& writer, UUIDComponent const& value);
		static Bool deserialize(Reader& reader, UUIDComponent& value);
	};
}
