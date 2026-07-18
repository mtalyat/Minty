#pragma once

/**
 * @file MaskedComponent.h
 * @brief Header file defining the MaskedComponent structure.
 * @author Mitchell Talyat
 */

#include "Layer/LayerMask/LayerMask.hpp"
#include "Core/Serialize/Serializer.hpp"

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
		LayerMask value = MASK_ALL;
	};

	template<>
	struct Serializer<MaskedComponent>
	{
		static Bool serialize(Writer& writer, MaskedComponent const& value);
		static Bool deserialize(Reader& reader, MaskedComponent& value);
	};
}
