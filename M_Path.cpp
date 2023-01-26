#include "pch.h"
#include "M_Path.h"

namespace minty
{
	std::string path_combine(std::string const& left, std::string const& right)
	{
		return (std::filesystem::path(left) / right).string();
	}
}
