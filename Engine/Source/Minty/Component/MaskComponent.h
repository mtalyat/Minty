#ifndef MINTY_COMPONENT_MASKCOMPONENT_H
#define MINTY_COMPONENT_MASKCOMPONENT_H

/**
 * @file MaskComponent.h
 * @brief Header file defining the MaskComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief A component that holds a mask value.
	 */
	struct MaskComponent
		: public Component
	{
		/**
		 * @brief The mask value.
		 */
		UInt value = 0;
	};

	template<>
	struct Serializer<MaskComponent>
	{
		static void serialize(Writer& writer, MaskComponent const& value);
		static Bool deserialize(Reader& reader, MaskComponent& value);
	};
}

#endif // MINTY_COMPONENT_MASKCOMPONENT_H