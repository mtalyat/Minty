#pragma once

/**
 * @file MaskedComponent.h
 * @brief Header file defining the MaskedComponent structure.
 * @author Mitchell Talyat
 */

#include "Layer/LayerMask/LayerMask.h"

namespace Minty
{
	/**
	 * @brief A component that is masked by another component.
	 */
	struct MaskedComponent	
	{
		/**
		 * @brief The mask value.
		 */
		Mask value = {};
	};

	template<>
	struct Serializer<MaskedComponent>
	{
		static Bool serialize(Writer& writer, MaskedComponent const& value);
		static Bool deserialize(Reader& reader, MaskedComponent& value);
	};
}
