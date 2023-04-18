#pragma once

#include "M_Main.h"
#include <string>

namespace minty
{
	/// <summary>
	/// Combines the two given paths together.
	/// </summary>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <returns></returns>
	MINTY_API std::string path_combine(std::string const& left, std::string const& right);
}