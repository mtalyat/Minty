#pragma once

/**
 * @file RigidbodyComponent.h
 * @brief Header file defining the RigidbodyComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Physics/Rigidbody.h"

namespace Minty
{
	/**
	 * @brief Holds a Rigidbody for an Entity.
	 */
	struct RigidbodyComponent	
	{
		/**
		 * @brief The Rigidbody associated with this component.
		 */
		Shared<Rigidbody> rigidbody = nullptr;
	};

	template<>
	struct Serializer<RigidbodyComponent>
	{
		static Bool serialize(Writer& writer, RigidbodyComponent const& value);
		static Bool deserialize(Reader& reader, RigidbodyComponent& value);
	};
}
