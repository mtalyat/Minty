#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"

namespace Minty
{
#pragma region Base 64



#pragma endregion

#pragma region Base 16

	/// <summary>
	/// Converts the given data to a base16 encoded String.
	/// </summary>
	/// <param name="data">A pointer to the raw byte data.</param>
	/// <param name="size">The size in bytes.</param>
	/// <returns>A base 16 String.</returns>
	String encode_base16(void const* const data, Size const size);

	/// <summary>
	/// Converts the given base16 encoded String to raw byte data.
	/// </summary>
	/// <param name="string">The base 16 String.</param>
	/// <param name="data">A pointer to the raw byte data.</param>
	/// <param name="size">The size in bytes.</param>
	void decode_base16(String const& string, void* const data, Size const size);

#pragma endregion

}