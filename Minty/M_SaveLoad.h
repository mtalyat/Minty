#pragma once

#include "M_Main.h"
#include "M_Saveable.h"
#include <SDL.h>

namespace minty
{
	MINTY_API void save_object_json(std::string const& path, Saveable* const obj);

	MINTY_API void load_object_json(std::string const& path, Saveable* const obj);
}