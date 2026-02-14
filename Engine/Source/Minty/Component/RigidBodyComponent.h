#ifndef MINTY_COMPONENT_RigidbodyCOMPONENT_H
#define MINTY_COMPONENT_RigidbodyCOMPONENT_H

/**
 * @file RigidbodyComponent.h
 * @brief Header file defining the RigidbodyComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Physics/Rigidbody.h"

namespace Minty
{
	/**
	 * @brief Holds a Rigidbody for an Entity.
	 */
	struct RigidbodyComponent
		: public Component
	{
		/**
		 * @brief The Rigidbody associated with this component.
		 */
		Shared<Rigidbody> rigidbody = nullptr;
	};

	template<>
	struct Serializer<RigidbodyComponent>
	{
		static void serialize(Writer& writer, RigidbodyComponent const& value);
		static Bool deserialize(Reader& reader, RigidbodyComponent& value);
	};
}

#endif // MINTY_COMPONENT_RigidbodyCOMPONENT_H