#ifndef MINTY_COMPONENT_PREFABCOMPONENT_H
#define MINTY_COMPONENT_PREFABCOMPONENT_H

/**
 * @file PrefabComponent.h
 * @brief Header file defining the PrefabComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
	/**
	 * @brief Holds the ID of the Prefab that the Entity was instantiated from.
	 */
	struct PrefabComponent
		: public Component
	{
		UUID id;
	};
}

#endif // MINTY_COMPONENT_PREFABCOMPONENT_H