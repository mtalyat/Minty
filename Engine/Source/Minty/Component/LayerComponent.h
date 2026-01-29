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
		/**
		 * @brief The layer of the entity.
		 */
		Layer layer = LAYER_DEFAULT;
	};

	template<>
	struct Serializer<LayerComponent>
	{
		static void serialize(Writer& writer, LayerComponent const& value);
		static Bool deserialize(Reader& reader, LayerComponent& value);
	};
}

#endif // MINTY_COMPONENT_LAYERCOMPONENT_H