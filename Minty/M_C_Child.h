#pragma once

#include "M_Main.h"
#include "entt.hpp"

namespace minty
{
	/// <summary>
	/// A component that holds data relating to being a child of a parent.
	/// </summary>
	struct MINTY_API Child
	{
		entt::entity parent;
	};
}