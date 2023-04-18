#include "pch.h"
#include "M_Path.h"
//#ifndef BOOST_ALL_DYN_LINK
//#define BOOST_ALL_DYN_LINK
//#endif 
#include <boost/filesystem.hpp>

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
		return (boost::filesystem::path(left) / boost::filesystem::path(right)).string();
	}
}
