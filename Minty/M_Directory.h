#pragma once

#include "M_Main.h"
#include <string>
#include <vector>
#include <map>

namespace minty
{
	/// <summary>
	/// Checks if the given directory path exists.
	/// </summary>
	/// <param name="path">The path to check.</param>
	/// <returns>True of the given path exists.</returns>
	MINTY_API bool directory_exists(std::string const& path);

	/// <summary>
	/// Ensures that all directories in the given path exist, creating missing directories if necessary.
	/// </summary>
	/// <param name="path">The path to validate.</param>
	MINTY_API void directory_validate(std::string const& path);
}