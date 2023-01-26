#pragma once

#include <string>
#include <filesystem>

namespace minty
{
	/// <summary>
	/// Combines the two given paths together.
	/// </summary>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <returns></returns>
	std::string path_combine(std::string const& left, std::string const& right);
}