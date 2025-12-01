#ifndef MINTY_SERIALIZATION_PARSEABLE_H
#define MINTY_SERIALIZATION_PARSEABLE_H

/**
 * @file Parseable.h
 * @brief Header file defining the Parseable interface.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"

namespace Minty
{
	class Parseable
	{
	public:
		virtual ~Parseable() = default;

		/**
		 * @brief Reads the data for this object from a String.
		 * @param text A String of this object.
		 * @return True on success.
		 */
		virtual Bool parse(String const& text) = 0;

		/**
		 * @brief Converts the data in this object to a String.
		 * @return A String of this object.
		 */
		virtual String to_string() const = 0;
	};
}

#endif // MINTY_SERIALIZATION_PARSEABLE_H