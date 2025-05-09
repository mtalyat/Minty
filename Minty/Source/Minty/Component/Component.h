#pragma once
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	struct Component
		: public SerializableObject
	{
		virtual ~Component() = default;

		/// <summary>
		/// Write this Component's data to the writer.
		/// </summary>
		/// <param name="writer">The Writer to write to.</param>
		virtual void serialize(Writer& writer) const {}

		/// <summary>
		/// Read this Component's data from the reader.
		/// </summary>
		/// <param name="reader">The Reader to read from.</param>
		/// <returns>True on success.</returns>
		virtual Bool deserialize(Reader& reader) { return true; }
	};
}