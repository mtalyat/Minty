#ifndef MINTY_COMPONENT_ENABLEDCOMPONENT_H
#define MINTY_COMPONENT_ENABLEDCOMPONENT_H

/**
 * @file EnabledTag.h
 * @brief Header file defining the EnabledTag structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief If an Entity has this component, it is enabled.
	 */
	struct EnabledTag
		: public Component
	{
	};
}

#endif // MINTY_COMPONENT_ENABLEDCOMPONENT_H