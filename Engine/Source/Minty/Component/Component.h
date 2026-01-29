#ifndef MINTY_COMPONENT_COMPONENT_H
#define MINTY_COMPONENT_COMPONENT_H

/**
 * @file Component.h
 * @brief Header file defining the Component structure.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	class EntityManager;
	struct ComponentData;

	/**
	 * @brief The base class for all components. Holds data for an Entity.
	 */
	struct Component 
	{
	};
}

#endif // MINTY_COMPONENT_COMPONENT_H