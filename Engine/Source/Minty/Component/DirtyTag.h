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
}

#endif // MINTY_COMPONENT_DIRTYCOMPONENT_H