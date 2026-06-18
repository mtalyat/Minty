#pragma once

/**
 * @file CanvasComponent.h
 * @brief Header file defining the CanvasComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/UI/Canvas.h"

namespace Minty
{
	/**
	 * @brief Holds the Canvas data for an Entity.
	 */
	struct CanvasComponent	
	{
		/**
		 * @brief The Canvas data.
		 */
		Canvas canvas;
	};

	template<>
	struct Serializer<CanvasComponent>
	{
		static Bool serialize(Writer& writer, CanvasComponent const& value);
		static Bool deserialize(Reader& reader, CanvasComponent& value);
	};
}
