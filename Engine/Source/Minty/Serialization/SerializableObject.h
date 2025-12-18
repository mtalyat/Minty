#ifndef MINTY_SERIALIZATION_SERIALIZABLEOBJECT_H
#define MINTY_SERIALIZATION_SERIALIZABLEOBJECT_H

/**
 * @file SerializableObject.h
 * @brief Header file defining the SerializableObject interface.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
	class Writer;
	class Reader;

	/**
	 * @brief Interface for objects that can be serialized and deserialized.
	 */
	class SerializableObject
	{
	public:
		virtual ~SerializableObject() = default;

		/**
		 * @brief Write this object's data to the writer.
		 * @param writer The Writer to write to.
		 */
		virtual void serialize(Writer& writer) const = 0;

		/**
		 * @brief Read this object's data from the reader.
		 * @param reader The Reader to read from.
		 * @return True on success.
		 */
		virtual Bool deserialize(Reader& reader) = 0;
	};
}

#endif // MINTY_SERIALIZATION_SERIALIZABLEOBJECT_H