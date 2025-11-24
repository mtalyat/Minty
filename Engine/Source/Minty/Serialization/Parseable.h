#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"

namespace Minty
{
	class Parseable
	{
	public:
		virtual ~Parseable() = default;

		/// <summary>
		/// Reads the data for this object from a String.
		/// </summary>
		/// <param name="text">A String of this object.</param>
		/// <returns>True on success.</returns>
		virtual Bool parse(String const& text) = 0;

		/// <summary>
		/// Converts the data in this object to a String.
		/// </summary>
		/// <returns>A String of this object.</returns>
		virtual String to_string() const = 0;
	};
}