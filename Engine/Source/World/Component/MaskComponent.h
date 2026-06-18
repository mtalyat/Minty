#pragma once

/**
 * @file MaskComponent.h
 * @brief Header file defining the MaskComponent structure.
 * @author Mitchell Talyat
 */

#include "Layer/LayerMask/LayerMask.h"
#include "Core/Serialize/Serializer.h"

namespace Minty
{
	/**
	 * @brief A component that holds a mask value.
	 */
	struct MaskComponent	
	{
		/**
		 * @brief The mask value.
		 */
		Mask mask = {};
	};

	template<>
	struct Serializer<MaskComponent>
	{
		static Bool serialize(Writer& writer, MaskComponent const& value);
		static Bool deserialize(Reader& reader, MaskComponent& value);
	};
}
