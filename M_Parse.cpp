#include "pch.h"
#include "M_Parse.h"

namespace minty
{
	MINTY_API int parse_int(std::string const& str)
	{
		return std::stoi(str);
	}

	MINTY_API bool try_parse_int(std::string const& str, int& out)
	{
		if (str.empty())
		{
			return false;
		}

		for (char c : str)
		{
			if (!isdigit(c))
			{
				return false;
			}
		}

		out = std::stoi(str);
		return true;
	}

	MINTY_API long long parse_longLong(std::string const& str)
	{
		return std::stoll(str);
	}

	MINTY_API bool try_parse_longLong(std::string const& str, long long& out)
	{
		if (str.empty())
		{
			return false;
		}

		for (char c : str)
		{
			if (!isdigit(c))
			{
				return false;
			}
		}

		out = std::stoll(str);
		return true;
	}
}
