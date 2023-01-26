#pragma once

#include "M_Main.h"
#include <string>

namespace minty
{
	MINTY_API inline int parse_int(std::string const& str);

	MINTY_API bool try_parse_int(std::string const& str, int& out);

	MINTY_API inline long long parse_longLong(std::string const& str);

	MINTY_API bool try_parse_longLong(std::string const& str, long long& out);
}