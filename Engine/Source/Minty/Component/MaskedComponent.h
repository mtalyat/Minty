#ifndef MINTY_COMPONENT_MASKEDCOMPONENT_H
#define MINTY_COMPONENT_MASKEDCOMPONENT_H

/**
 * @file MaskedComponent.h
 * @brief Header file defining the MaskedComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief A component that is masked by another component.
	 */
	struct MaskedComponent
		: public Component
	{
		/**
		 * @brief The mask value.
		 */
		UInt value = 0;
	};

	template<>
	struct Serializer<MaskedComponent>
	{
		static void serialize(Writer& writer, MaskedComponent const& value);
		static Bool deserialize(Reader& reader, MaskedComponent& value);
	};
}

#endif // MINTY_COMPONENT_MASKEDCOMPONENT_H