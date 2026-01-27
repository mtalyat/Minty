#ifndef MINTY_COMPONENT_NAMECOMPONENT_H
#define MINTY_COMPONENT_NAMECOMPONENT_H

/**
 * @file NameComponent.h
 * @brief Header file defining the NameComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/String.h"

namespace Minty
{
	/**
	 * @brief Holds the name of an Entity.
	 */
	struct NameComponent
		: public Component
	{
		/**
		 * @brief The name of the entity.
		 */
		String name = "";
	};

	template<>
	struct Serializer<NameComponent>
	{
		static void serialize(Writer& writer, NameComponent const& value);
		static Bool deserialize(Reader& reader, NameComponent& value);
	};
}

#endif // MINTY_COMPONENT_NAMECOMPONENT_H