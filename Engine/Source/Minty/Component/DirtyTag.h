#ifndef MINTY_COMPONENT_DIRTYCOMPONENT_H
#define MINTY_COMPONENT_DIRTYCOMPONENT_H

/**
 * @file DirtyTag.h
 * @brief Header file defining the DirtyTag structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief If an Entity has this component, it is dirty.
	 */
	struct DirtyTag
		: public Component
	{
	};

	template<>
	struct Serializer<DirtyTag>
	{
		static void serialize(Writer& writer, DirtyTag const& value){}
		static void deserialize(Reader& reader, DirtyTag& value){}
	};
}

#endif // MINTY_COMPONENT_DIRTYCOMPONENT_H