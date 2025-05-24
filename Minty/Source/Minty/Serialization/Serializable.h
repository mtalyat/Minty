#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"

namespace Minty
{
	class Writer;
	class Reader;

	/// <summary>
	/// An interface for single-attribute objects to be written and read from.
	/// </summary>
	class Serializable
	{
	public:
		virtual ~Serializable() = default;

		/// <summary>
		/// Write this object's data to the writer.
		/// </summary>
		/// <param name="writer">The Writer to write to.</param>
		/// <param name="name">The name of this object.</param>
		virtual void serialize(Writer& writer, String const& name) const = 0;

		/// <summary>
		/// Read this object's data from the reader.
		/// </summary>
		/// <param name="reader">The Reader to read from.</param>
		/// <param name="index">The index of this object.</param>
		/// <returns>True on success.</returns>
		virtual Bool deserialize(Reader& reader, Size const index) = 0;
	};
}