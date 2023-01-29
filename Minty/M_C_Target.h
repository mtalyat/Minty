#pragma once

#include "M_Main.h"
#include "entt.hpp"

namespace minty
{
	/// <summary>
	/// For entities that have another entity as a target.
	/// </summary>
	struct MINTY_API Target
	{
		entt::entity target;
	};
}