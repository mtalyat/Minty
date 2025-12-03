#ifndef MINTY_COMPONENT_COMPONENT_H
#define MINTY_COMPONENT_COMPONENT_H

/**
 * @file Component.h
 * @brief Header file defining the Component structure.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	class EntityManager;
	struct ComponentData;

	/**
	 * @brief The base class for all components. Holds data for an Entity.
	 */
	struct Component
		: public SerializableObject
	{
		virtual ~Component() = default;

		/**
		 * @brief Write this Component's data to the writer.
		 * @param writer The Writer to write to.
		 */
		virtual void serialize(Writer& writer) const override {}

		/**
		 * @brief Read this Component's data from the reader.
		 * @param reader The Reader to read from.
		 * @return True on success.
		 */
		virtual Bool deserialize(Reader& reader) override { return true; }
	};
}

#endif // MINTY_COMPONENT_COMPONENT_H