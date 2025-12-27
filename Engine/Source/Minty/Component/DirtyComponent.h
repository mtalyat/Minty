#ifndef MINTY_COMPONENT_DIRTYCOMPONENT_H
#define MINTY_COMPONENT_DIRTYCOMPONENT_H

/**
 * @file DirtyComponent.h
 * @brief Header file defining the DirtyComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief If an Entity has this component, it is dirty.
	 */
	struct DirtyComponent
		: public Component
	{
	};

	template<>
	struct Serializer<DirtyComponent>
	{
		static void serialize(Writer& writer, DirtyComponent const& value){}
		static void deserialize(Reader& reader, DirtyComponent& value){}
	};
}

#endif // MINTY_COMPONENT_DIRTYCOMPONENT_H