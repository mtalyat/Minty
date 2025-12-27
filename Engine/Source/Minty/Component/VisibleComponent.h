#ifndef MINTY_COMPONENT_VISIBLECOMPONENT_H
#define MINTY_COMPONENT_VISIBLECOMPONENT_H

/**
 * @file VisibleComponent.h
 * @brief Header file defining the VisibleComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief If an Entity has this component, it is visible.
	 */
	struct VisibleComponent
		: public Component
	{
	};

	template<>
	struct Serializer<VisibleComponent>
	{
		static void serialize(Writer& writer, VisibleComponent const& value){}
		static void deserialize(Reader& reader, VisibleComponent& value){}
	};
}

#endif // MINTY_COMPONENT_VISIBLECOMPONENT_H