#pragma once

#define NOMINMAX
#include "M_Main.h"
#include <string>
#include <format>

namespace minty
{
	/// <summary>
	/// The base class for all objects within the Minty game engine.
	/// </summary>
	class MINTY_API Object
	{
	public:
		virtual ~Object() {}

		/// <summary>
		/// Converts the Object to a string.
		/// </summary>
		/// <returns></returns>
		virtual std::string const toString() const;
	};
}