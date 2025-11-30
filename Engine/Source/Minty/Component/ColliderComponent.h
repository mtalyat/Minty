#ifndef MINTY_COMPONENT_COLLIDERCOMPONENT_H
#define MINTY_COMPONENT_COLLIDERCOMPONENT_H

/**
 * @file ColliderComponent.h
 * @brief Header file defining the ColliderComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	class Collider;
	
	/**
	 * @brief Holds a Collider for an Entity.
	 */
	struct ColliderComponent
		: public Component
	{
		/**
		 * @brief The Collider.
		 */
		Shared<Collider> collider;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_COLLIDERCOMPONENT_H