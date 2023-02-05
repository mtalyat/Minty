#pragma once

#include "M_Main.h"
#include <string>
#include <map>

namespace minty
{
	MINTY_API inline unsigned char parse_byte(std::string const& str);

	MINTY_API bool try_parse_byte(std::string const& str, unsigned char& out);

	MINTY_API inline unsigned short parse_ushort(std::string const& str);

	MINTY_API bool try_parse_ushort(std::string const& str, unsigned char& out);

	MINTY_API inline int parse_int(std::string const& str);

	MINTY_API bool try_parse_int(std::string const& str, int& out);

	MINTY_API inline unsigned int parse_uint(std::string const& str);

	MINTY_API bool try_parse_uint(std::string const& str, unsigned int& out);

	MINTY_API inline long long parse_longLong(std::string const& str);

	MINTY_API bool try_parse_longLong(std::string const& str, long long& out);

	MINTY_API int parse_enum(std::string const& str, std::map<std::string, int> const& map);
}