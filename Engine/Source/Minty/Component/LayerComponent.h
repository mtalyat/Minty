#ifndef MINTY_COMPONENT_LAYERCOMPONENT_H
#define MINTY_COMPONENT_LAYERCOMPONENT_H

/**
 * @file LayerComponent.h
 * @brief Header file defining the LayerComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Core/Types.h"
#include "Minty/Core/Constant.h"

namespace Minty
{
	/**
	 * @brief Holds the layer of an Entity.
	 */
	struct LayerComponent
		: public Component
	{
		Layer layer = LAYER_DEFAULT;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_LAYERCOMPONENT_H