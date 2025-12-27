#ifndef MINTY_COMPONENT_DESTROYCOMPONENT_H
#define MINTY_COMPONENT_DESTROYCOMPONENT_H

/**
 * @file DestroyComponent.h
 * @brief Header file defining the DestroyComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief Marks an Entity for destruction.
	 */
	struct DestroyComponent
		: public Component
	{
	};

	template<>
	struct Serializer<DestroyComponent>
	{
		static void serialize(Writer& writer, DestroyComponent const& value){}
		static void deserialize(Reader& reader, DestroyComponent& value){}
	};
}

#endif // MINTY_COMPONENT_DESTROYCOMPONENT_H