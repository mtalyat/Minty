#ifndef MINTY_SERIALIZATION_SERIALIZABLE_H
#define MINTY_SERIALIZATION_SERIALIZABLE_H

/**
 * @file Serializable.h
 * @brief Header file defining the Serializable interface.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
	class Writer;
	class Reader;
	class String;

	/**
	 * @brief Interface for objects that can be serialized and deserialized.
	 */
	class Serializable
	{
	public:
		virtual ~Serializable() = default;

		/**
		 * @brief Write this object's data to the writer.
		 * @param writer The Writer to write to.
		 * @param name The name of this object.
		 */
		virtual void serialize(Writer& writer, String const& name) const = 0;

		/**
		 * @brief Read this object's data from the reader.
		 * @param reader The Reader to read from.
		 * @param index The index of this object.
		 * @return True on success.
		 */
		virtual Bool deserialize(Reader& reader, Size const index) = 0;
	};
}

#endif // MINTY_SERIALIZATION_SERIALIZABLE_H