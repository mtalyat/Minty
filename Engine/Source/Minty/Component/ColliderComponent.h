#ifndef MINTY_COMPONENT_COLLIDERCOMPONENT_H
#define MINTY_COMPONENT_COLLIDERCOMPONENT_H

/**
 * @file ColliderComponent.h
 * @brief Header file defining the ColliderComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Physics/Collider.h"

namespace Minty
{	
	/**
	 * @brief Holds a Collider for an Entity.
	 */
	struct ColliderComponent
		: public Component
	{
		/**
		 * @brief The Collider.
		 */
		Shared<Collider> collider = nullptr;
	};

	template<>
	struct Serializer<ColliderComponent>
	{
		static void serialize(Writer& writer, ColliderComponent const& value);
		static Bool deserialize(Reader& reader, ColliderComponent& value);
	};
}

#endif // MINTY_COMPONENT_COLLIDERCOMPONENT_H