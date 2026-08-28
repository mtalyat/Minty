#pragma once

/**
 * @file MaskComponent.hpp
 * @brief Header file defining the MaskComponent structure.
 * @author Mitchell Talyat
 */

#include "Collision/CollisionMask/CollisionMask.hpp"
#include "Core/Serialize/Serializer.hpp"

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
		CollisionMask mask = MASK_ALL;
	};

	template<>
	struct Serializer<MaskComponent>
	{
		static Bool serialize(Writer& writer, MaskComponent const& value);
		static Bool deserialize(Reader& reader, MaskComponent& value);
	};
}
