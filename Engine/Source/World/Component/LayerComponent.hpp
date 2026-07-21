#pragma once

/**
 * @file LayerComponent.hpp
 * @brief Header file defining the LayerComponent structure.
 * @author Mitchell Talyat
 */

#include "Layer/LayerMask/LayerMask.hpp"
#include "Core/Serialize/Serializer.hpp"
 
namespace Minty
{
	/**
	 * @brief Holds the layer of an Entity.
	 */
	struct LayerComponent	
	{
		/**
		 * @brief The layer of the entity.
		 */
		Layer layer = {};
	};

	template<>
	struct Serializer<LayerComponent>
	{
		static Bool serialize(Writer& writer, LayerComponent const& value);
		static Bool deserialize(Reader& reader, LayerComponent& value);
	};
}
