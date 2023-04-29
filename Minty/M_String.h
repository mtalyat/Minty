#pragma once

#include "M_Main.h"
#include "M_Math.h"
#include <string>

namespace minty
{
	/// <summary>
	/// Pads the string with a char in the beginning of the given string.
	/// </summary>
	/// <param name="str">The string to pad.</param>
	/// <param name="width">The minimum width of the entire string.</param>
	/// <param name="padding">The character to pad with.</param>
	/// <returns>The new string, with paddded characters.</returns>
	MINTY_API inline std::string string_pad_left(std::string str, int const width, char const padding);

	/// <summary>
	/// Pads the string with a char to the end of the given string.
	/// </summary>
	/// <param name="str">The string to pad.</param>
	/// <param name="width">The minimum width of the entire string.</param>
	/// <param name="padding">The character to pad with.</param>
	/// <returns>The new string, with padded characters.</returns>
	MINTY_API inline std::string string_pad_right(std::string str, int const width, char const padding);

	/// <summary>
	/// Converts the given integer to a binary string.
	/// </summary>
	/// <param name="value">The integer to convert.</param>
	/// <param name="count">The number of bits to show.</param>
	/// <returns>A string form of the number in binary representation.</returns>
	MINTY_API std::string string_to_binary(int const value, int const count = sizeof(int) * 8);
}