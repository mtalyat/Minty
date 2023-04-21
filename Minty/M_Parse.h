#pragma once

#include "M_Main.h"
#include "M_Types.h"
#include <string>
#include <map>

namespace minty
{
	/// <summary>
	/// Converts the string to a byte.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <returns>The value within the string.</returns>
	MINTY_API inline byte parse_byte(std::string const& str);

	/// <summary>
	/// Converts the string to a byte, if the string is in the correct format.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <param name="out">Takes value within the string, if parsed successfully.</param>
	/// <returns>True, if the value was correctly parsed.</returns>
	MINTY_API bool try_parse_byte(std::string const& str, byte& out);

	/// <summary>
	/// Converts the string to an sbyte.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <returns>The value within the string.</returns>
	MINTY_API inline sbyte parse_sbyte(std::string const& str);

	/// <summary>
	/// Converts the string to an sbyte, if the string is in the correct format.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <param name="out">Takes value within the string, if parsed successfully.</param>
	/// <returns>True, if the value was correctly parsed.</returns>
	MINTY_API bool try_parse_sbyte(std::string const& str, sbyte& out);

	/// <summary>
	/// Converts the string to a ushort.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <returns>The value within the string.</returns>
	MINTY_API inline ushort parse_ushort(std::string const& str);

	/// <summary>
	/// Converts the string to a ushort, if the string is in the correct format.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <param name="out">Takes value within the string, if parsed successfully.</param>
	/// <returns>True, if the value was correctly parsed.</returns>
	MINTY_API bool try_parse_ushort(std::string const& str, ushort& out);

	/// <summary>
	/// Converts the string to an int.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <returns>The value within the string.</returns>
	MINTY_API inline int parse_int(std::string const& str);

	/// <summary>
	/// Converts the string to an int, if the string is in the correct format.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <param name="out">Takes value within the string, if parsed successfully.</param>
	/// <returns>True, if the value was correctly parsed.</returns>
	MINTY_API bool try_parse_int(std::string const& str, int& out);

	/// <summary>
	/// Converts the string to a uint.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <returns>The value within the string.</returns>
	MINTY_API inline uint parse_uint(std::string const& str);

	/// <summary>
	/// Converts the string to a uint, if the string is in the correct format.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <param name="out">Takes value within the string, if parsed successfully.</param>
	/// <returns>True, if the value was correctly parsed.</returns>
	MINTY_API bool try_parse_uint(std::string const& str, uint& out);

	/// <summary>
	/// Converts the string to a long long.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <returns>The value within the string.</returns>
	MINTY_API inline long long parse_longLong(std::string const& str);

	/// <summary>
	/// Converts the string to a long long, if the string is in the correct format.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <param name="out">Takes value within the string, if parsed successfully.</param>
	/// <returns>True, if the value was correctly parsed.</returns>
	MINTY_API bool try_parse_longLong(std::string const& str, long long& out);

	/// <summary>
	/// Converts the string to an enum.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <returns>The value within the string.</returns>
	MINTY_API int parse_enum(std::string const& str, std::map<std::string, int> const& map);

	/// <summary>
	/// Converts the string with a binary number to a uint.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <returns>The value within the string.</returns>
	MINTY_API uint parse_binary(std::string const& str);

	/// <summary>
	/// Converts the string with a binary number to a uint, if the string is in the correct format.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <param name="out">Takes value within the string, if parsed successfully.</param>
	/// <returns>True, if the value was correctly parsed.</returns>
	MINTY_API bool try_parse_binary(std::string const& str, uint& out);

	/// <summary>
	/// Converts the string to a float.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <returns>The value within the string.</returns>
	MINTY_API float parse_float(std::string const& str);

	/// <summary>
	/// Converts the string to a float, if the string is in the correct format.
	/// </summary>
	/// <param name="str">The string to parse.</param>
	/// <param name="out">Takes value within the string, if parsed successfully.</param>
	/// <returns>True, if the value was correctly parsed.</returns>
	MINTY_API bool try_parse_float(std::string const& str, float& out);
}