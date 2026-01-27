#ifndef MINTY_COMPONENT_COMPONENTDATA_H
#define MINTY_COMPONENT_COMPONENTDATA_H

/**
 * @file ComponentData.h
 * @brief Header file for the ComponentData struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	class EntityManager;
	class Reader;
	class Writer;
	struct Component;

	/**
	 * @brief Struct containing data and functions for managing Components.
	 */
	struct ComponentData
	{
		/**
		 * @brief The name of the Component.
		 */
		String name = "";

		/**
		 * @brief Function to create the Component on an Entity.
		 */
		Function<Component *(EntityManager &, Entity const)> create = nullptr;

		/**
		 * @brief Function to destroy the Component from an Entity.
		 */
		Function<void(EntityManager &, Entity const)> destroy = nullptr;

		/**
		 * @brief Function to get the Component from an Entity.
		 */
		Function<Component *(EntityManager &, Entity const)> get = nullptr;

		/**
		 * @brief Function to get the const Component from an Entity.
		 */
		Function<Component const *(EntityManager const &, Entity const)> get_const = nullptr;

		/**
		 * @brief Function to serialize the Component.
		 */
		Function<void(Writer &writer, Component const&)> serialize = nullptr;

		/**
		 * @brief Function to deserialize the Component.
		 */
		Function<void(Reader &reader, Component&)> deserialize = nullptr;
	};
}

#endif // MINTY_COMPONENT_COMPONENTDATA_H