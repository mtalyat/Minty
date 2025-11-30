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
		UInt value = 0;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_MASKCOMPONENT_H