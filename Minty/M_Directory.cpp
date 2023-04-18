#include "pch.h"
#include "M_Directory.h"
#include <boost/filesystem.hpp>

namespace minty
{
	bool directory_exists(std::string const& path)
	{
		return boost::filesystem::exists(path);
	}
	
	MINTY_API void directory_validate(std::string const& path)
	{
		boost::filesystem::create_directories(path);
	}
}
