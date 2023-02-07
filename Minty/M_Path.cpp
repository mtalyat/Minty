#include "pch.h"
#include "M_Path.h"

namespace minty
{
	std::string path_combine(std::string const& left, std::string const& right)
	{
		if (right.starts_with(left))
		{
			return right;
		}
		else if (left.starts_with(right))
		{
			return left;
		}

		// neither start with one another, so combine
		return (std::filesystem::path(left) / right).string();
	}
}
