#ifndef MINTY_COMPONENT_COMPONENTDATA_H
#define MINTY_COMPONENT_COMPONENTDATA_H

/**
 * @file ComponentData.h
 * @brief Header file for the ComponentData struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	class EntityManager;
	struct Component;

	struct ComponentData
	{
		String name;

		Function<Component &(EntityManager &, Entity const)> create;

		Function<Component *(EntityManager &, Entity const)> get;

		Function<Component const *(EntityManager const &, Entity const)> get_const;

		Function<void(EntityManager &, Entity const)> destroy;
	};
}

#endif // MINTY_COMPONENT_COMPONENTDATA_H