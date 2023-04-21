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
		/// <summary>
		/// The target entity.
		/// </summary>
		entt::entity target;

		/// <summary>
		/// The amount to lerp by to get to the target entity.
		/// </summary>
		float lerp;
	};
}