#ifndef MINTY_COMPONENT_DESTROYCOMPONENT_H
#define MINTY_COMPONENT_DESTROYCOMPONENT_H

/**
 * @file DestroyTag.h
 * @brief Header file defining the DestroyTag structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"

namespace Minty
{
	/**
	 * @brief Marks an Entity for destruction.
	 */
	struct DestroyTag
		: public Component
	{
	};
}

#endif // MINTY_COMPONENT_DESTROYCOMPONENT_H