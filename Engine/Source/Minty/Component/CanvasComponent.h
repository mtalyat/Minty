#ifndef MINTY_COMPONENT_CANVASCOMPONENT_H
#define MINTY_COMPONENT_CANVASCOMPONENT_H

/**
 * @file CanvasComponent.h
 * @brief Header file defining the CanvasComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/UI/Canvas.h"

namespace Minty
{
	/**
	 * @brief Holds the Canvas data for an Entity.
	 */
	struct CanvasComponent
		: public Component
	{
		/**
		 * @brief The Canvas data.
		 */
		Canvas canvas;
	};

	template<>
	struct Serializer<CanvasComponent>
	{
		static void serialize(Writer& writer, CanvasComponent const& value);
		static Bool deserialize(Reader& reader, CanvasComponent& value);
	};
}

#endif // MINTY_COMPONENT_CANVASCOMPONENT_H