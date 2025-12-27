#ifndef MINTY_COMPONENT_ENABLEDCOMPONENT_H
#define MINTY_COMPONENT_ENABLEDCOMPONENT_H

/**
 * @file EnabledComponent.h
 * @brief Header file defining the EnabledComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief If an Entity has this component, it is enabled.
	 */
	struct EnabledComponent
		: public Component
	{
	};

	template<>
	struct Serializer<EnabledComponent>
	{
		static void serialize(Writer& writer, EnabledComponent const& value){}
		static void deserialize(Reader& reader, EnabledComponent& value){}
	};
}

#endif // MINTY_COMPONENT_ENABLEDCOMPONENT_H