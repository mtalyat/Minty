#include "pch.h"
#include "M_Text.h"

namespace minty
{
	MINTY_API std::string minty::text_pad_left(std::string str, int const width, char const padding)
	{
		return str.insert(0, math_max(0, width - str.length()), padding);
	}

	MINTY_API std::string text_pad_right(std::string str, int const width, char const padding)
	{
		return str.append(math_max(0, width - str.length()), padding);
	}
}
