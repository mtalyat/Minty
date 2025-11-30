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

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_CANVASCOMPONENT_H