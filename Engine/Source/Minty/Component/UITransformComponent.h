#ifndef MINTY_COMPONENT_UITRANSFORMCOMPONENT_H
#define MINTY_COMPONENT_UITRANSFORMCOMPONENT_H

/**
 * @file UITransformComponent.h
 * @brief Header file defining the UITransformComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/UITransform.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	/**
	 * @brief A component that holds the UI transform data.
	 */
	struct UITransformComponent
		: public Component
	{
		/**
		 * @brief The Entity with a Canvas component that this UITransformComponent belongs to.
		 */
		Entity canvas = INVALID_ENTITY;

		/**
		 * @brief The UITransform data.
		 */
		UITransform transform;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_UITRANSFORMCOMPONENT_H