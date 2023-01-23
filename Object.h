#pragma once

#include "Minty.h"
#include <string>

namespace minty
{
	/// <summary>
	/// The base class for all objects within the Minty game engine.
	/// </summary>
	class MINTY_API Object
	{
	public:
		virtual ~Object() {}

		virtual std::string const toString() const;
	};
}