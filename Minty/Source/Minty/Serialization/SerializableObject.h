#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	class Writer;
	class Reader;

	/// <summary>
	/// An interface for multiple-attribute objects to be written and read from.
	/// </summary>
	class SerializableObject
	{
	public:
		virtual ~SerializableObject() = default;

		/// <summary>
		/// Write this object's data to the writer.
		/// </summary>
		/// <param name="writer">The Writer to write to.</param>
		virtual void serialize(Writer& writer) const = 0;

		/// <summary>
		/// Read this object's data from the reader.
		/// </summary>
		/// <param name="reader">The Reader to read from.</param>
		/// <returns>True on success.</returns>
		virtual Bool deserialize(Reader& reader) = 0;
	};
}