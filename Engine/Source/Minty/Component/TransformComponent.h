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
		/**
		 * @brief The Transform of this Entity.
		 */
		Transform transform;
	};

	template<>
	struct Serializer<TransformComponent>
	{
		static void serialize(Writer& writer, TransformComponent const& value);
		static Bool deserialize(Reader& reader, TransformComponent& value);
	};
}

#endif // MINTY_COMPONENT_TRANSFORMCOMPONENT_H