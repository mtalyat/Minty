#include "pch.h"
#include "M_Parse.h"

namespace minty
{
	MINTY_API unsigned char parse_byte(std::string const& str)
	{
		return static_cast<unsigned char>(std::stoul(str));
	}

	MINTY_API bool try_parse_byte(std::string const& str, unsigned char& out)
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

		out = parse_byte(str);
		return true;
	}

	MINTY_API unsigned short parse_ushort(std::string const& str)
	{
		return static_cast<unsigned short>(std::stoul(str));
	}

	MINTY_API bool try_parse_ushort(std::string const& str, unsigned char& out)
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

		out = parse_ushort(str);
		return true;
	}

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

		out = parse_int(str);
		return true;
	}

	MINTY_API unsigned int parse_uint(std::string const& str)
	{
		return static_cast<unsigned int>(std::stoul(str));
	}

	MINTY_API bool try_parse_uint(std::string const& str, unsigned int& out)
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

		out = parse_uint(str);
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

		out = parse_longLong(str);
		return true;
	}
	
	MINTY_API int parse_enum(std::string const& str, std::map<std::string, int> const& map)
	{
		// check if within dictionary
		auto found = map.find(str);

		if (found != map.end())
		{
			return found->second;
		}

		return -1;
	}
	
	MINTY_API unsigned int parse_binary(std::string const& str)
	{
		size_t size = str.size();
		unsigned int out = 0;

		for (size_t i = 0; i < size; i++)
		{
			if (str.at(i) == '1')
			{
				out |= 1u << (size - 1u - i);
			}
		}

		return out;
	}
	
	MINTY_API bool try_parse_binary(std::string const& str, unsigned int& out)
	{
		if (str.empty())
		{
			return false;
		}

		for (char c : str)
		{
			if (c != '0' && c != '1')
			{
				// not binary
				return false;
			}
		}

		out = parse_binary(str);
		return true;
	}
}
