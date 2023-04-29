#include "pch.h"
#include "M_String.h"

namespace minty
{
	MINTY_API std::string minty::string_pad_left(std::string str, int const width, char const padding)
	{
		return str.insert(0, math_max(0, width - str.length()), padding);
	}

	MINTY_API std::string string_pad_right(std::string str, int const width, char const padding)
	{
		return str.append(math_max(0, width - str.length()), padding);
	}
	
	MINTY_API std::string string_to_binary(int const value, int const count)
	{
		char *binary = new char[count + 1];

		for (int i = 0; i < count; i++)
		{
			binary[count - 1 - i] = ((value >> i) & 1) ? '1' : '0';
		}

		binary[count] = '\0'; // end of string
		std::string str = std::string(binary);
		delete[] binary;
		return str;
	}
}
