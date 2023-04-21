#pragma once

#include "M_Main.h"
#include "M_Saveable.h"
#include <SDL.h>

namespace minty
{
	/// <summary>
	/// Saves an object to the disk.
	/// </summary>
	/// <param name="path">The location to save the object.</param>
	/// <param name="obj">The object to be saved.</param>
	MINTY_API void save_object_json(std::string const& path, Saveable* const obj);

	/// <summary>
	/// Loads an object from the disk.
	/// </summary>
	/// <param name="path">The location to load the object from.</param>
	/// <param name="obj">The object to have values loaded into.</param>
	MINTY_API void load_object_json(std::string const& path, Saveable* const obj);
}