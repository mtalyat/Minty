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
		UInt value = 0;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_MASKEDCOMPONENT_H