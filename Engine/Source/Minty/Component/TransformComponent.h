#ifndef MINTY_COMPONENT_TRANSFORMCOMPONENT_H
#define MINTY_COMPONENT_TRANSFORMCOMPONENT_H

/**
 * @file TransformComponent.h
 * @brief Header file defining the TransformComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/Transform.h"

namespace Minty
{
	/**
	 * @brief Holds a Transform for an Entity.
	 */
	struct TransformComponent
		: public Component
	{
		Transform transform;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_TRANSFORMCOMPONENT_H