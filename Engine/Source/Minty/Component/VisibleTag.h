#ifndef MINTY_COMPONENT_VISIBLECOMPONENT_H
#define MINTY_COMPONENT_VISIBLECOMPONENT_H

/**
 * @file VisibleTag.h
 * @brief Header file defining the VisibleTag structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief If an Entity has this component, it is visible.
	 */
	struct VisibleTag
		: public Component
	{
	};
}

#endif // MINTY_COMPONENT_VISIBLECOMPONENT_H