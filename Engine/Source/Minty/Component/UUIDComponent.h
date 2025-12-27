#ifndef MINTY_COMPONENT_UUIDCOMPONENT_H
#define MINTY_COMPONENT_UUIDCOMPONENT_H

/**
 * @file UUIDComponent.h
 * @brief Header file defining the UUIDComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
	/**
	 * @brief Holds an ID value for an Entity.
	 */
	struct UUIDComponent
		: public Component
	{
		UUID id = {};
	};

	template<>
	struct Serializer<UUIDComponent>
	{
		static void serialize(Writer& writer, UUIDComponent const& value);
		static void deserialize(Reader& reader, UUIDComponent& value);
	};
}

#endif // MINTY_COMPONENT_UUIDCOMPONENT_H