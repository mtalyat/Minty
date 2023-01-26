#pragma once

#include "M_Main.h"
#include "M_Math.h"
#include <string>

namespace minty
{
	MINTY_API inline std::string text_pad_left(std::string str, int const width, char const padding);

	MINTY_API inline std::string text_pad_right(std::string str, int const width, char const padding);
}