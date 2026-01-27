#ifndef MINTY_COMPONENT_RIGIDBODYCOMPONENT_H
#define MINTY_COMPONENT_RIGIDBODYCOMPONENT_H

/**
 * @file RigidBodyComponent.h
 * @brief Header file defining the RigidBodyComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Physics/RigidBody.h"

namespace Minty
{
	/**
	 * @brief Holds a RigidBody for an Entity.
	 */
	struct RigidBodyComponent
		: public Component
	{
		/**
		 * @brief The RigidBody associated with this component.
		 */
		Shared<RigidBody> rigidBody = nullptr;
	};

	template<>
	struct Serializer<RigidBodyComponent>
	{
		static void serialize(Writer& writer, RigidBodyComponent const& value);
		static Bool deserialize(Reader& reader, RigidBodyComponent& value);
	};
}

#endif // MINTY_COMPONENT_RIGIDBODYCOMPONENT_H