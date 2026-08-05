#pragma once

/**
 * @file CanvasComponent.hpp
 * @brief Header file defining the CanvasComponent structure.
 * @author Mitchell Talyat
 */

#include "Core/Type/UInt2.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
	/**
	 * @brief Holds the Canvas data for an Entity.
	 */
	struct CanvasComponent	
	{
		UInt2 resolution = UInt2(0, 0);
	};

	template<>
	struct Serializer<CanvasComponent>
	{
		static Bool serialize(Writer& writer, CanvasComponent const& value);
		static Bool deserialize(Reader& reader, CanvasComponent& value);
	};
}
